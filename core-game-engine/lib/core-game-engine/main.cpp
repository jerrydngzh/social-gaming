#include <cassert>
#include <cstdio>
#include <memory>
#include <string>
#include <iostream>
#include <cpp-tree-sitter.h>
#include <map>
#include <any>

#include "configuration.h"
#include "constants.h"
#include "perAudience.h"
#include "perPlayer.h"
#include "rules.h"
#include "treeParser.h"
#include "util.h"
#include "variables.h"


extern "C" {
  TSLanguage* tree_sitter_socialgaming();
}


auto recursiveParse(const ts::Node& node, const std::string &fileContents, auto &contents){
    if(node.getNumChildren() == 0) {
      std::map<std::string_view, std::string_view> valueMap;
      valueMap.insert(std::make_pair("type", node.getType()));
      valueMap.insert(std::make_pair("contents", node.getSourceRange(fileContents)));
      contents.push_back(valueMap);
      return node.getSourceRange(fileContents);
    } else {
      for(int i = 0; i < node.getNumChildren(); i++){
        recursiveParse(node.getChild(i), fileContents, contents);
        std::map<std::string_view, std::string_view> valueMap;
        valueMap.insert(std::make_pair("type", node.getType()));
        valueMap.insert(std::make_pair("contents", node.getSourceRange(fileContents)));
        contents.push_back(valueMap);
      }
    }
}


struct CustomMapping {
    int index;
    std::string_view key;
    std::string_view value;
    int parent;
    std::vector<int> children;
    std::string_view type;
};

void extractMap(const ts::Node& node, const std::string &fileContents, std::vector<auto> &entry, CustomMapping &mapping){
    // DEBUG
    std::string_view type = node.getType();
    std::string_view contents = node.getSourceRange(fileContents);
    std::cout << std::endl;
    std::cout << "[DEBUG] " << contents << std::endl;
    std::cout << "[DEBUG] type: " << type << std::endl;
    std::cout << "NumChildren:" << node.getNumChildren() << std::endl;

    //         // 1. number; 2. boolean; 3. quoted_string; 4. number_range; 5. identifiers; 6. expression_list; 7. list_literal
    //         // 8. map_entry; 9. value_map; 10. qualified_identifier; 11. player_set; 12. body; 13. comment
    if(type == "identifier") {
      mapping.key = contents;
    } else if (type == "number") {
      // TODO
    } else if (type == "boolean") {
      // TODO
    } else if (type == "quoted_string") {
      mapping.value = contents;
      mapping.index = entry.size();
      mapping.type = type;
      entry.at(mapping.parent).children.push_back(mapping.index);
      entry.push_back(mapping);
      mapping.key = "";
      mapping.value = "";
    } else if (type == "number_range") {
      // TODO
    } else if (type == "expression") {
      extractMap(node.getChild(0), fileContents, entry, mapping);
    } else if (type == "expression_list") {
      int parent = mapping.parent;
      for(int i = 0; i < node.getNumChildren(); i++){
        if(node.getChild(i).getType() != ",") {
          CustomMapping tempMapping{};
          tempMapping.index = entry.size();
          tempMapping.type = type;
          tempMapping.parent = mapping.parent;
          if(entry.size() > 0) {
            entry.at(mapping.parent).children.push_back(tempMapping.index);
          }
          entry.push_back(tempMapping);
          mapping.parent = tempMapping.index;
          extractMap(node.getChild(i), fileContents, entry, mapping);
        }
        mapping.parent = parent;
      }
    } else if (type == "list_literal") {
      CustomMapping tempMapping{};
      tempMapping.key = mapping.key;
      tempMapping.index = entry.size();
      tempMapping.type = type;
      tempMapping.parent = mapping.parent;
      if(entry.size() > 0) {
        entry.at(mapping.parent).children.push_back(tempMapping.index);
      }
      entry.push_back(tempMapping);
      mapping.parent = tempMapping.index;
      for(int i = 0; i < node.getNumChildren(); i++){
        extractMap(node.getChild(i), fileContents, entry, mapping);
      }
    } else if (type == "map_entry") {
      for(int i = 0; i < node.getNumChildren(); i++){
        extractMap(node.getChild(i), fileContents, entry, mapping);
      }
    } else if (type == "value_map") {
      for(int i = 0; i < node.getNumChildren(); i++){
        extractMap(node.getChild(i), fileContents, entry, mapping);
      }
    } else if (type == "qualified_identifier") {
      // TODO
    } else if (type == "player_set") {
      // TODO
    } else if (type == "body") {
      // TODO
    } else if (type == "comment") {
      // TODO
    }


    //   if(type == "{" || type == "[" || type == ",") {  
    //     return;
    //   } else if(type == "identifier") {
    //     // std::cout << "found identifier" << std::endl;
    //     std::string_view key = contents;
    //     // std::cout << "key = " << key << std::endl;
    //     mapping.index = entry.size();
    //     mapping.type = "identifier";
    //     mapping.key = contents;
    //     return;
    //   } else if(!mapping.key.empty() && type == "quoted_string"){
    //   // } else if(type == "quoted_string") {
    //     // std::cout << "found quoted_string" << std::endl;
    //     std::string_view value = contents;
    //     // std::cout << "value = " << value << std::endl;
    //     mapping.index = entry.size();
    //     mapping.type = type;
    //     mapping.value = value;
    //     entry.push_back(mapping);
    //     mapping.key = "";
    //     mapping.value = "";
    //     mapping.type = "";
    //     return;
    // } else {
    //       for(int i = 0; i < node.getNumChildren(); i++) {
    //         // 1. number; 2. boolean; 3. quoted_string; 4. number_range; 5. identifiers; 6. expression_list; 7. list_literal
    //         // 8. map_entry; 9. value_map; 10. qualified_identifier; 11. player_set; 12. body; 13. comment
    //         if(type == "value_map") {
    //           // std::cout << "found value_map" << std::endl;
    //           extractMap(node.getChild(i), fileContents, entry, mapping);
    //         } else if(type == "map_entry") {
    //           // std::cout << "found map_entry" << std::endl;
    //           extractMap(node.getChild(i), fileContents, entry, mapping);
    //         } else if(type == "list_literal") {
    //           // std::cout << "found list_literal" << std::endl;
    //           extractMap(node.getChild(i), fileContents, entry, mapping);
    //         } else if(type == "expression") {
    //           // std::cout << "found expression" << std::endl;
    //           extractMap(node.getChild(i), fileContents, entry, mapping);
    //         } else if(type == "expression_list") {
    //           // std::cout << "found expression_list" << std::endl;
    //           extractMap(node.getChild(i), fileContents, entry, mapping);
    //         } else {
    //           std::cout << "N/A" << std::endl;
    //         }
    //       }
    // }
}


void printVector(const std::vector<auto> &toPrint){
  std::cout << "{";
  for(int i = 0; i < toPrint.size(); i++){
    std::cout << "type = " << toPrint.at(i).at("type") << "; ";
    std::cout << "contents = " << toPrint.at(i).at("contents") << std::endl;
    if(i != toPrint.size() - 1) {
      std::cout << ", ";
    }
  }
  std::cout << "}" << std::endl;
}


int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Please provide a file to parse" << std::endl;
    return 1;
  }

  std::string filename = argv[1];
  std::string fileContents = parseGAMEFromFile(filename);
  ts::Tree tree = parseTree(fileContents);
  ts::Node root = tree.getRootNode();

  // extract nodes from the tree
  ts::Node configurationNode = root.getChildByFieldName("configuration");
  ts::Node constantsNode = root.getChildByFieldName("constants");
  ts::Node variablesNode = root.getChildByFieldName("variables");
  ts::Node perPlayerNode = root.getChildByFieldName("per_player");
  ts::Node perAudienceNode = root.getChildByFieldName("per_audience");
  ts::Node rulesNode = root.getChildByFieldName("rules");

  // Create and Initialize Objects for each of the game sections
  Configuration configurationLibrary(configurationNode, fileContents);
  Constants constantsLibrary(constantsNode);
  PerAudience perAudienceLibrary(perAudienceNode);
  PerPlayer perPlayerLibrary(perPlayerNode);
  Rules rulesLibrary(rulesNode, 10);
  Variables variablesLibrary(variablesNode);

  std::string_view contents = constantsLibrary.getContents(fileContents);
  std::cout << contents << std::endl;

  ts::Node constants = constantsNode;
  std::cout << std::endl << constants.getType() << std::endl;
  printf("Syntax tree: %s\n", constants.getSExpr().get());

  // *********** MANUAL RECURSE CONSTANTS TREE *****************
  // std::cout << constants.getNumChildren() << std::endl;
  // std::cout << constants.getChild(1).getSourceRange(fileContents) << std::endl;
  // std::cout << constants.getChild(1).getType() << std::endl;      // value_map
  // std::cout << constants.getChild(1).getChild(1).getChild(0).getType() << std::endl;  // identifier
  // std::cout << constants.getChild(1).getChild(1).getChild(0).getSourceRange(fileContents) << std::endl; // weapons
  // std::cout << constants.getChild(1).getChild(1).getChild(2).getType() << std::endl; // expression
  // std::cout << constants.getChild(1).getChild(1).getChild(2).getSourceRange(fileContents) << std::endl;
  // std::cout << constants.getChild(1).getChild(1).getChild(2).getChild(0).getType() << std::endl; // list_literal
  // std::cout << constants.getChild(1).getChild(1).getChild(2).getChild(0).getSourceRange(fileContents) << std::endl;
  // std::cout << constants.getChild(1).getChild(1).getChild(2).getChild(0).getChild(1).getType() << std::endl;  // expression_list
  // std::cout << constants.getChild(1).getChild(1).getChild(2).getChild(0).getChild(1).getSourceRange(fileContents) << std::endl;
  // std::cout << constants.getChild(1).getChild(1).getChild(2).getChild(0).getChild(1).getChild(0).getType() << std::endl; // expression
  // std::cout << constants.getChild(1).getChild(1).getChild(2).getChild(0).getChild(1).getChild(0).getSourceRange(fileContents) << std::endl; // { name: "Rock",     beats: "Scissors" }
  // std::cout << constants.getChild(1).getChild(1).getChild(2).getChild(0).getChild(1).getChild(0).getChild(0).getType() << std::endl;  //value map
  // std::cout << constants.getChild(1).getChild(1).getChild(2).getChild(0).getChild(1).getChild(0).getChild(0).getSourceRange(fileContents) << std::endl;  // { name: "Rock",     beats: "Scissors" }
  // std::cout << constants.getChild(1).getChild(1).getChild(2).getChild(0).getChild(1).getChild(0).getChild(0).getChild(0).getType() << std::endl; // {
  // std::cout << constants.getChild(1).getChild(1).getChild(2).getChild(0).getChild(1).getChild(0).getChild(0).getChild(0).getSourceRange(fileContents) << std::endl; // {
  // std::cout << constants.getChild(1).getChild(1).getChild(2).getChild(0).getChild(1).getChild(0).getChild(0).getChild(1).getType() << std::endl; // map_entry
  // std::cout << constants.getChild(1).getChild(1).getChild(2).getChild(0).getChild(1).getChild(0).getChild(0).getChild(1).getSourceRange(fileContents) << std::endl; // name: "Rock"
  // std::cout << constants.getChild(1).getChild(1).getChild(2).getChild(0).getChild(1).getChild(0).getChild(0).getChild(1).getChild(0).getType() << std::endl; // identifier
  // std::cout << constants.getChild(1).getChild(1).getChild(2).getChild(0).getChild(1).getChild(0).getChild(0).getChild(1).getChild(0).getSourceRange(fileContents) << std::endl; // name
  // std::cout << constants.getChild(1).getChild(1).getChild(2).getChild(0).getChild(1).getChild(0).getChild(0).getChild(1).getChild(1).getType() << std::endl; // :
  // std::cout << constants.getChild(1).getChild(1).getChild(2).getChild(0).getChild(1).getChild(0).getChild(0).getChild(1).getChild(1).getSourceRange(fileContents) << std::endl; // :
  // std::cout << constants.getChild(1).getChild(1).getChild(2).getChild(0).getChild(1).getChild(0).getChild(0).getChild(1).getChild(2).getType() << std::endl; // expression
  // std::cout << constants.getChild(1).getChild(1).getChild(2).getChild(0).getChild(1).getChild(0).getChild(0).getChild(1).getChild(2).getSourceRange(fileContents) << std::endl; // "Rock"
  // std::cout << constants.getChild(1).getChild(1).getChild(2).getChild(0).getChild(1).getChild(0).getChild(0).getChild(1).getChild(2).getChild(0).getType() << std::endl; // quoted_string
  // std::cout << constants.getChild(1).getChild(1).getChild(2).getChild(0).getChild(1).getChild(0).getChild(0).getChild(1).getChild(2).getChild(0).getSourceRange(fileContents) << std::endl; // "Rock"
  // std::cout << constants.getChild(1).getChild(1).getChild(2).getChild(0).getChild(1).getChild(0).getChild(0).getChild(1).getChild(2).getChild(0).getNumChildren() << std::endl; // 0

  std::vector<std::map<std::string_view, std::string_view>> constantsParsedResults = {};
  recursiveParse(constants, fileContents, constantsParsedResults);

  printVector(constantsParsedResults);

  std::cout << "******************** MAP EXTRACTOR *****************" << std::endl;
  std::vector<CustomMapping> tempVector = {};
  CustomMapping tempMapping = {};
  
  extractMap(constants.getChild(1), fileContents, tempVector, tempMapping);
  std::cout << tempVector[0].key << std::endl;
  std::cout << tempVector.size() << std::endl;

  for(const CustomMapping& entry : tempVector){
    std::cout << "Index   : " << entry.index << std::endl;
    std::cout << "Key     : " << entry.key << std::endl;
    std::cout << "Value   : " << entry.value << std::endl;
    std::cout << "Type    : " << entry.type << std::endl;
    std::cout << "Parent  : " << entry.parent << std::endl;
    std::cout << "Children: [";
    for(const int &child : entry.children){
      std::cout << child << ", ";
    }
    std::cout << "]" << std::endl << std::endl;
  }


  std::cout << tempMapping.key << std::endl;
  std::cout << tempMapping.value << std::endl;

  //rulesLibrary.runGame()?
}


// types
// 1. number
// 2. boolean 
// 3. quoted_string 
// 4. number_range
// 5. identifiers
// 6. expression_list
// 7. list_literal
// 8. map_entry
// 9. value_map
// 10. qualified_identifier
// 11. player_set
// 12. body
// 13. comment