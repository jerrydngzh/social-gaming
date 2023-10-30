#include <cassert>
#include <cstdio>
#include <memory>
#include <iostream>

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


Extractor::Extractor(const std::string &fileContents):
  fileContents(fileContents), 
  parent(0)
  {}


Extractor::~Extractor() {}


void Extractor::append(std::vector<Mapping> &data, const std::string_view &key, const std::string_view &value, const uint32_t &parent, const std::string_view &type) {
  uint32_t index = data.size();
  
  // initialize a new Mapping struct  
  Mapping entry{index, key, value, parent, {},type};

  // update parent with this entry the entry is not the root node
  if(type != "root") {
    data.at(entry.parent).children.push_back(entry.index);    
  }

  // add the new entry to data
  data.push_back(entry);
}// append()


bool Extractor::isValidType(const std::string_view &type, const std::vector<std::string_view> &validList) {
  auto iter = std::find_if(validList.begin(), validList.end(), [type](const std::string_view &entry) {
    return entry == type;
  });

  // when iterator is not equal to end of vector, a valid type is found
  if(iter != validList.end()){
    return true;
  }
  return false; 
}// isValidType()


void Extractor::checkUnrecognizedType(const std::string_view &type){
    bool root = isValidType(type, rootTypes);
    bool key = isValidType(type, keyTypes);
    bool values = isValidType(type, valueTypes);
    bool ignored = isValidType(type, ignoredTypes);
    bool invalid = isValidType(type, invalidTypes);

    try {
      if(!root && !key && !values && !ignored && !invalid){
        throw std::invalid_argument("Type not recognized by Extractor...");
      }
    } catch(const std::invalid_argument& e) {
        std::cout << "[ERROR] Type: '" << type << "' type is not recognized by Extractor..." << std::endl;
        exit(1); 
    }
}// checkUnrecognizedType()


void Extractor::recurse(const ts::Node &node, std::vector<Mapping> &data) {
  uint32_t currentParent = parent;   // when function is ready to pop-off stack, reset the parent with this value
  std::string_view type = node.getType();
  std::string_view value = node.getSourceRange(fileContents);

  std::cout << "[TYPE]: '" << type << "'" << std::endl;

  if(isValidType(type, rootTypes) && (data.size() == 0)){
      append(data, type, "", 0, "root");                   // key and type (root node)
  } else if (isValidType(type, keyTypes)) {
    key = value;                                           // set the global key value
  } else if (isValidType(type, valueTypes)) {
    append(data, key, value, parent, type);                // key, value, parent, and type
    parent = data.size() - 1;
  } else if (type == "expression_list" || type == "expression") {
    append(data, "", "", parent, type);                    // no key or value (acts as a container for children)
    parent = data.size() - 1;
  } else if (type == "list_literal" || type == "number_range") {
    append(data, key, "", parent, type);                   // key only
    key = "";
    parent = data.size() - 1;
  } else if (type == "setup_rule") {
    key = node.getChild(0).getSourceRange(fileContents);  // get key from first child
    append(data, key, "", parent, type);                  // add Mapping with key only
    parent = data.size() - 1;
  } else {
    checkUnrecognizedType(type);                          // throw error if type is unrecognized
  }

  // recurse through the node's children
  for(int i = 0; i < node.getNumChildren(); i++) {
    recurse(node.getChild(i), data);
  }

  // set the parent value to original argument before popping off stack
  parent = currentParent;    
}// recurse()


// Create a Mapping Vector and extract data by recursing tree from argument node
std::vector<Mapping> Extractor::format(const ts::Node &node) {
  std::vector<Mapping> data;
  recurse(node, data);

  return data;
}// format()
