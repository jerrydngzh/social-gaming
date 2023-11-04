#include <cassert>
#include <cstdio>
#include <memory>
#include <string>
#include <regex>
#include <sstream>
#include <iostream>
#include <cpp-tree-sitter.h>

#include "configuration.h"
#include "constants.h"
#include "mapping.h"
#include "perAudience.h"
#include "perPlayer.h"
#include "rules.h"
#include "treeParser.h"
#include "util.h"
#include "variables.h"
#include "game.h"


extern "C" {
  TSLanguage* tree_sitter_socialgaming();
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

  // initialize the extractor object
  Extractor extractor(fileContents);

  // extract header nodes from the tree
  ts::Node configurationNode = root.getChildByFieldName("configuration");
  ts::Node constantsNode = root.getChildByFieldName("constants");
  ts::Node variablesNode = root.getChildByFieldName("variables");
  ts::Node perPlayerNode = root.getChildByFieldName("per_player");
  ts::Node perAudienceNode = root.getChildByFieldName("per_audience");
  ts::Node rulesNode = root.getChildByFieldName("rules");

  // Use Extractor object to get a data structure for the contents of the node
  std::vector<Mapping> configurationData = extractor.format(configurationNode);
  std::vector<Mapping> constantsData = extractor.format(constantsNode);
  std::vector<Mapping> variablesData = extractor.format(variablesNode);
  std::vector<Mapping> perPlayerData = extractor.format(perPlayerNode);
  std::vector<Mapping> perAudienceData = extractor.format(perAudienceNode);

  // Create and Initialize Objects for each of the game sections
  Configuration configurationLibrary(configurationData);
  Constants constantsLibrary(constantsData);
  Variables variablesLibrary(variablesData);
  PerPlayer perPlayerLibrary(perPlayerData);
  PerAudience perAudienceLibrary(perAudienceData);

  // Uncomment to print the data structure contents
  configurationLibrary.print();  
  // constantsLibrary.print();
  // variablesLibrary.print();
  // perPlayerLibrary.print();
  // perAudienceLibrary.print();


  // [NOTE]: this will not work for the rules, will need a different parser
  // Rules rulesLibrary(rulesNode, 10);

  //rulesLibrary.runGame()?
  // Create game by initializing objects for each of the game sections
  // Game game = Game(tree, fileContents, configurationData, constantsData, variablesData, perPlayerData, perAudienceData);

  // game.startGame();
}