#include <cassert>
#include <cstdio>
#include <memory>
#include <string>
#include <regex>
#include <sstream>
#include <iostream>
#include <cpp-tree-sitter.h>

#include "game.h"
#include "configuration.h"
#include "constants.h"
#include "mapping.h"
#include "perAudience.h"
#include "perPlayer.h"
#include "rules.h"
#include "treeParser.h"
#include "util.h"
#include "variables.h"


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

  // extract header nodes from the tree
  ts::Node rulesNode = root.getChildByFieldName("rules");

  //rulesLibrary.runGame()?
  // Create game by initializing objects for each of the game sections
  // Game game = Game(tree, fileContents, configurationData, constantsData, variablesData, perPlayerData, perAudienceData);

  // game.startGame();
}