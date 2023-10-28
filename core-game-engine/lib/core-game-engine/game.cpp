#include <string>
#include <cpp-tree-sitter.h>

#include "game.h"
#include "interpreter.h"

Game::Game(const ts::Tree& tree, std::string_view fileContents):
    configurationLibrary(tree.getRootNode().getChildByFieldName("configuration"), fileContents),
    constantsLibrary(tree.getRootNode().getChildByFieldName("constants")),
    perAudienceLibrary(tree.getRootNode().getChildByFieldName("per_audience")),
    perPlayerLibrary(tree.getRootNode().getChildByFieldName("per_player")),
    rulesLibrary(tree.getRootNode().getChildByFieldName("rules"), 10),
    variablesLibrary(tree.getRootNode().getChildByFieldName("variables")),
    tree(tree)
{}

Game::~Game() {}

void Game::startGame() {
    Interpreter gameRunner(this, this->tree);
    gameRunner.run(rulesLibrary.getNode());
}