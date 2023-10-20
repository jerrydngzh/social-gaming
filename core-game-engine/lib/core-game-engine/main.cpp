#include <cassert>
#include <cstdio>
#include <memory>
#include <string>
#include <iostream>
#include <cpp-tree-sitter.h>

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


// auto recursiveParse(const ts::Node& node, const std::string &fileContents, auto &contents){
//     if(node.getNumChildren() == 0) {
//       std::map<std::string_view, std::string_view> valueMap;
//       valueMap.insert(std::make_pair("type", node.getType()));
//       valueMap.insert(std::make_pair("contents", node.getSourceRange(fileContents)));
//       contents.push_back(valueMap);
//       return node.getSourceRange(fileContents);
//     } else {
//       for(int i = 0; i < node.getNumChildren(); i++){
//         recursiveParse(node.getChild(i), fileContents, contents);
//         std::map<std::string_view, std::string_view> valueMap;
//         valueMap.insert(std::make_pair("type", node.getType()));
//         valueMap.insert(std::make_pair("contents", node.getSourceRange(fileContents)));
//         contents.push_back(valueMap);
//       }
//     }
// }


// void printVector(const std::vector<auto> &toPrint){
//   std::cout << "{";
//   for(int i = 0; i < toPrint.size(); i++){
//     std::cout << "type = " << toPrint.at(i).at("type") << "; ";
//     std::cout << "contents = " << toPrint.at(i).at("contents") << std::endl;
//     if(i != toPrint.size() - 1) {
//       std::cout << ", ";
//     }
//   }
//   std::cout << "}" << std::endl;
// }


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

  // std::string_view contents = constantsLibrary.getContents(fileContents);
  // std::cout << contents << std::endl;

  // ts::Node constants = constantsNode;
  // std::cout << std::endl << constants.getType() << std::endl;
  // printf("Syntax tree: %s\n", constants.getSExpr().get());

  // std::vector<std::map<std::string_view, std::string_view>> constantsParsedResults = {};
  // recursiveParse(constants, fileContents, constantsParsedResults);

  // printVector(constantsParsedResults);

  // std::cout << "******************** MAP EXTRACTOR *****************" << std::endl;
  // std::vector<CustomMapping> tempVector = {};
  // CustomMapping tempMapping = {};
  
  // extractMap(constants.getChild(1), fileContents, tempVector, tempMapping);
  // std::cout << tempVector[0].key << std::endl;
  // std::cout << tempVector.size() << std::endl;

  Extractor extractor(fileContents);
  std::cout << perPlayerNode.getNumChildren() << std::endl;
  std::vector<Mapping> contents = extractor.format(perPlayerNode);
  std::cout << "[DEBUG] contents.size(): " << contents.size() << std::endl;

  for(const Mapping& entry : contents){
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


  // std::cout << tempMapping.key << std::endl;
  // std::cout << tempMapping.value << std::endl;


  //rulesLibrary.runGame()?
}