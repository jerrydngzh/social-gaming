#include <string>
#include <cpp-tree-sitter.h>

#include "game.h"


Game::Game(
    const Configuration& configurationLibrary,
    const Constants& constantsLibrary,
    const PerAudience& perAudienceLibrary,
    const PerPlayer& perPlayerLibrary,
    const Rules& rulesLibrary,
    const Variables& variablesLibrary) :

    configurationLibrary(configurationLibrary),
    constantsLibrary(constantsLibrary),
    perAudienceLibrary(perAudienceLibrary),
    perPlayerLibrary(perPlayerLibrary),
    rulesLibrary(rulesLibrary),
    variablesLibrary(variablesLibrary)
{}

Game::~Game() {}

void Game::startGame(ts::Tree tree) {
    Interpreter gameRunner(this, tree);
    gameRunner.recurse(rulesLibrary.getNode());
}