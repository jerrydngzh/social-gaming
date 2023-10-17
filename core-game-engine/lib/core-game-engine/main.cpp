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

// constants {      # VECTOR = value_map
//   weapons: [     # VECTOR = 
//     { name: "Rock",     beats: "Scissors" },   # VECTOR of structs
//     { name: "Paper",    beats: "Rock"     },
//     { name: "Scissors", beats: "Paper"    },
//   ]
// }

void extractMap(const ts::Node& node, const std::string &fileContents, std::vector<auto> &entry){
    // DEBUG
    std::string_view type = node.getType();
    std::cout << std::endl << "[DEBUG] " << "Type: " << type << std::endl;
    std::string_view contents = node.getSourceRange(fileContents);
    std::cout << "[DEBUG] " << contents << std::endl;
    std::cout << "NumChildren:" << node.getNumChildren() << std::endl;

    if(node.getNumChildren() == 0) {
      if(type == "identifier") {
        // add to key
        std::cout << "found identifier" << std::endl;
        std::string_view key = contents;
        std::cout << "key = " << key << std::endl;
      } else if(type == "quoted_string") {
        // add to value
        std::cout << "found quoted_string" << std::endl;
      } else if(type == "{" || type == ":" || type == "}" || type == "[" || type == "]") {
        std::cout << "N/A" << std::endl;
      }
    } else {
      
          for(int i = 0; i < node.getNumChildren(); i++) {

            // 1. number; 2. boolean; 3. quoted_string; 4. number_range; 5. identifiers; 6. expression_list; 7. list_literal
            // 8. map_entry; 9. value_map; 10. qualified_identifier; 11. player_set; 12. body; 13. comment

            // TODO, need expression
            if(type == "value_map") {
              // create new map (will be list of maps)
              // std::cout << "found value_map" << std::endl;
              // std::map<std::string_view, std::any> tempMap;

              extractMap(node.getChild(i), fileContents, entry);
            } else if(type == "map_entry") {
              // TBD
              // std::cout << "found map_entry" << std::endl;

              extractMap(node.getChild(i), fileContents, entry);

              // entry.insert(std::make_pair(localKey, localValue));
            } else if(type == "list_literal") {
              // for loop through children
              // std::cout << "found list_literal" << std::endl;
              // extractMap(node.getChild(i), fileContents, entry, key, value);
            } else if(type == "expression") {
              // for loop through children
              // std::cout << "found expression" << std::endl;
              // extractMap(node.getChild(i), fileContents, entry, key, value);
            } else if(type == "expression_list") {
              // for loop through children
              // std::cout << "found expression_list" << std::endl;
              // extractMap(node.getChild(i), fileContents, entry, key, value);
            } else {
              std::cout << "N/A" << std::endl;
            }
          }
    }
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
  std::vector<std::string_view> tempVector = {};
  
  extractMap(constants.getChild(1), fileContents, tempVector);


  // auto newMap = convertStringToMap(constantsParsedResults, 5);

  // std::cout << newMap.size() << std::endl;
  // std::cout << newMap.at("name") << std::endl;
  // std::cout << newMap.at("beats") << std::endl;

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