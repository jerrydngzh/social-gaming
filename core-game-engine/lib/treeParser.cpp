#include "treeParser.h"

extern "C" {
  TSLanguage* tree_sitter_socialgaming();
}


ts::Tree parseTree(const std::string& source){
    ts::Language language = tree_sitter_socialgaming();
    ts::Parser parser{ language };
    ts::Tree tree = parser.parseString(source);
    return tree;
}


//********************************
//          EXTRACTOR
//********************************

Extractor::Extractor(const std::string &fileContents):
  fileContents(fileContents) 
  // parent(0)
  {}


Extractor::~Extractor() {}


int Extractor::append(std::vector<Mapping> &data, const Mapping &entry) {
  // only adjust parents children when entry is not root 
  if(entry.type != "root") {
    data.at(entry.parent).children.push_back(entry.index);
  }

  // add Mapping to data structure
  data.push_back(entry);
  return entry.index;
}// append()


std::string Extractor::changeStringContent(std::string toFix) {
  std::string modified = toFix;

  // erase colons from string
  modified.erase(remove(modified.begin(), modified.end(), ':'), modified.end()); // remove colons

  // replace spaces with underscores
  std::replace(modified.begin(), modified.end(), ' ', '_');

  return modified;
}// changeStringContent()


void Extractor::checkUnrecognizedType(const std::string_view &type){
    bool root = isTypeInList(type, rootKeys);
    bool wrapper = isTypeInList(type, wrapperTypes);
    bool key = isTypeInList(type, keyTypes);
    bool valueWithKey = isTypeInList(type, valueTypesWithKey);
    bool valueNoKey = isTypeInList(type, valueTypesNoKey);
    bool list = isTypeInList(type, listTypes);
    bool keyOnly = isTypeInList(type, keyOnlyTypes);
    bool ignored = isTypeInList(type, ignoredTypes);
    bool invalid = isTypeInList(type, invalidTypes);

    try {
      if(!root && !wrapper && !key && !valueWithKey && !valueNoKey && !list && !keyOnly && !ignored && !invalid){
        throw std::invalid_argument("Type not recognized by Extractor...");
      }
    } catch(const std::invalid_argument& e) {
        std::cout << "[ERROR] Type: '" << type << "' type is not recognized by Extractor..." << std::endl;
        exit(1); 
    }
}// checkUnrecognizedType()


std::string Extractor::createKey(const std::string currentKey, const std::string_view toAdd) {
  std::string current = std::string(currentKey);
  std::string end = std::string(toAdd);

  if(!toAdd.empty()) {
    return current + "." + end;
  } 

  return current;
}// createKey()


Mapping Extractor::createMapping(std::vector<Mapping> &data, const std::string &key, const std::string_view &value, int &parent, const std::string_view &type) {
  int insertIndex = data.size(); 
  std::string path = createUniquePath(data, key, parent, type);

  if(isTypeInList(type, rootKeys) && data.size() == 0) {        // roots
    std::string path = std::string(type);
    return {insertIndex, path, "", 0, {}, "root"};

  } else if(isTypeInList(type, wrapperTypes)) {                // wrappers
    return {insertIndex, "", "", parent, {}, type};  

  } else if (isTypeInList(type, valueTypesWithKey)) {          // key-value pairs  
    return {insertIndex, path, value, parent, {}, type};
  
  } else if (isTypeInList(type, valueTypesNoKey)) {            // no keys, values only
    return {insertIndex, "", value, parent, {}, type};  
  
  } else if (isTypeInList(type, keyOnlyTypes)) {               // keys only, no values
    return {insertIndex, path, "", parent, {}, type};  
    
  } else if (type == "setup_rule") {                           // setup_rule (unique)
    return {insertIndex, path, "", parent, {}, type};  

  } else if (type == "setup:" || type == "choices:") {         // setup: (unique), choices: (unique)
    std::string typeAsStr = changeStringContent(std::string(type));
    std::string path = createKey(data.at(parent).key, typeAsStr); 

    return {insertIndex, path, "", parent, {}, type};
  
  } else {
    checkUnrecognizedType(type);
  }

  return {};
}// createMapping()


std::string Extractor::createUniquePath(const std::vector<Mapping> &data, const std::string &key, const int &parent, const std::string_view &type) {
  std::string path;
  std::string copyOfKey = key;
  std::string formatedKey = changeStringContent(copyOfKey);

  // if list is empty, no need for a path
  if(data.size() == 0) {
    return path;
  }

  int branchParser = parent;

  // if entry does not have key set, it is not the head of the branch
  while(isTypeInList(data.at(branchParser).type, wrapperTypes) && branchParser != 0){     
    branchParser = data.at(branchParser).parent;
  }

  // extract data at head of branch
  std::string branchKey = data.at(branchParser).key;
  std::string_view branchType = data.at(branchParser).type;
  int branchChildrenCount = data.at(branchParser).children.size();

  if(type == "number" && branchType == "number_range") {
    path = branchKey + '[' + std::to_string(branchChildrenCount) + ']';

  } else if(isTypeInList(branchType, listTypes)) {
    std::string prepend = branchKey;

    // direct parent previously added as a child to in the branch 
    if(!isTypeInList(data.at(parent).type, listTypes)) { 
      prepend =  prepend + '[' + std::to_string(branchChildrenCount - 1) + ']';
    } else {
      prepend = prepend + '[' + std::to_string(branchChildrenCount) + ']';
    }

    path = createKey(prepend, key);

  } else if(!isTypeInList(type, wrapperTypes)) {
    path = createKey(branchKey, formatedKey);
  }

  return path;
}// createUniquePath()


bool Extractor::isTypeInList(const std::string_view &type, const std::vector<std::string_view> &validList) {
  auto iter = std::find_if(validList.begin(), validList.end(), [type](const std::string_view &entry) {
    return entry == type;
  });

  // when iterator is not equal to end of vector, a valid type is found
  if(iter != validList.end()){
    return true;
  }
  return false; 
}// isTypeInList()


void Extractor::recurse(const ts::Node &node, std::vector<Mapping> &data, std::string &key, int &parent) {
  int currentParent = parent;   // when function is ready to pop-off stack, reset the parent with this value
  std::string_view type = node.getType();
  std::string_view value = node.getSourceRange(fileContents);
  std::string currentKey = key;

  // set a key (if applicable)
  if(isTypeInList(type, keyTypes)) {
    key = value;
  } else if (type == "setup_rule") {
    key = node.getChild(0).getSourceRange(fileContents);  // get key from first child
  }

  // Create new mapping object if conditions are met
  Mapping entry = createMapping(data, key, value, parent, type);
  if(entry != Mapping{}){
    parent = append(data, entry);
  }

  // recurse through the node's children
  for(int i = 0; i < node.getNumChildren(); i++) {
    recurse(node.getChild(i), data, key, parent);
  }

  // set the parent value to original argument before popping off stack
  // dont reset parent if type is setup (setup does not have any children
  // according to tree structure so it will not enter loop above -- this 
  // may be a bug), setup can have children attached if we use this strategy
  if(type != "setup:" && type != "choices:"){
    parent = currentParent;    
  }
}// recurse()


// Create a Mapping Vector and extract data by recursing tree from argument node
std::vector<Mapping> Extractor::format(const ts::Node &node) {
  std::vector<Mapping> data;

  std::string key;
  int parent = 0;

  recurse(node, data, key, parent);

  return data;
}// format()
