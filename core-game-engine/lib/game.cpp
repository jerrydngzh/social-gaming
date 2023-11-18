#include "game.h"
#include "interpreter.h"

Game::Game(const ts::Tree& tree, std::string_view fileContents, 
        std::vector<Mapping> &configurationData,
        std::vector<Mapping> &constantsData,
        std::vector<Mapping> &variablesData,
        std::vector<Mapping> &perPlayerData,
        std::vector<Mapping> &perAudienceData):
    configurationLibrary(Configuration(configurationData)),
    constantsLibrary(Constants(constantsData)),
    variablesLibrary(Variables(variablesData)),
    perPlayerLibrary(PerPlayer(perPlayerData)),
    perAudienceLibrary(PerAudience(perAudienceData)),
    rulesLibrary(Rules(tree.getRootNode().getChildByFieldName("rules"), 10)),
    tree(tree)
    {}

Game::~Game() {}

void Game::startGame() {
    Interpreter gameRunner(this, this->tree);
    gameRunner.run(rulesLibrary.getNode());
}
