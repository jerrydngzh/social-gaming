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

  // extract nodes from the tree
  ts::Node configurationNode = root.getChildByFieldName("configuration");
  ts::Node constantsNode = root.getChildByFieldName("constants");
  ts::Node variablesNode = root.getChildByFieldName("variables");
  ts::Node perPlayerNode = root.getChildByFieldName("per_player");
  ts::Node perAudienceNode = root.getChildByFieldName("per_audience");
  ts::Node rulesNode = root.getChildByFieldName("rules");


  //MISHAS DEBUG INFO HERE. DELETE LATER! Maybe can help you to understand ********************************

  // auto treestring = root.getSExpr();
  // printf("Syntax tree: %s\n", treestring.get());

  // //printf("root type: %s rule type: %s\n", root.getType(), rulesNode.getType());

  // std::cout << tree.getLanguage().getNumSymbols() << " <- num symb | version -> " << tree.getLanguage().getVersion() << std::endl;


  // ts::Node n = rulesNode;
  // std::cout << std::endl << n.getType() << std::endl;
  // printf("Syntax tree: %s\n", n.getSExpr().get());

  // std::cout << "num children: " << n.getNumChildren() << std::endl;
  // for (int i = 0; i < n.getNumChildren(); i++) {
  //   std::cout << "child " << i << " symbol: " << tree.getLanguage().getSymbolName((n.getChild(i)).getSymbol()) << std::endl;
  // }

  // n = n.getChild(1);
  // std::cout << std::endl << n.getType() << std::endl;
  // printf("Syntax tree: %s\n", n.getSExpr().get());

  // std::cout << "num children: " << n.getNumChildren() << std::endl;
  // for (int i = 0; i < n.getNumChildren(); i++) {
  //   std::cout << "child " << i << " symbol: " << tree.getLanguage().getSymbolName((n.getChild(i)).getSymbol()) << std::endl;
  // }

  // n = n.getChild(2);
  // std::cout << std::endl << n.getType() << std::endl;
  // printf("Syntax tree: %s\n", n.getSExpr().get());

  // std::cout << "num children: " << n.getNumChildren() << std::endl;
  // for (int i = 0; i < n.getNumChildren(); i++) {
  //   std::cout << "child " << i << " symbol: " << tree.getLanguage().getSymbolName((n.getChild(i)).getSymbol()) << std::endl;
  // }

  // n = n.getChild(0);
  // std::cout << std::endl << n.getType() << std::endl;
  // printf("Syntax tree: %s\n", n.getSExpr().get());

  // std::cout << "num children: " << n.getNumChildren() << std::endl;
  // for (int i = 0; i < n.getNumChildren(); i++) {
  //   std::cout << "child " << i << " symbol: " << tree.getLanguage().getSymbolName((n.getChild(i)).getSymbol()) << std::endl;
  // }

  // //print all symbols
  // for (int i = 0; i < tree.getLanguage().getNumSymbols(); i++) {
  //   std::cout << i << " " << tree.getLanguage().getSymbolName(i) << std::endl;
  // }

  //END OF MISHAS DEBUG INFO *****************************************************************************

  // Create game by initializing objects for each of the game sections
  Game game = Game(
    Configuration(configurationNode, fileContents),
    Constants(constantsNode),
    PerAudience(perAudienceNode),
    PerPlayer(perPlayerNode),
    Rules(rulesNode, 10),
    Variables(variablesNode)
  );

  //rulesLibrary.runGame()?
}