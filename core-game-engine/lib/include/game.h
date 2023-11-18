#pragma once

#include <string>
#include <cpp-tree-sitter.h>

#include "configuration.h"
#include "constants.h"
#include "perAudience.h"
#include "perPlayer.h"
#include "rules.h"
#include "treeParser.h"
#include "util.h"
#include "variables.h"
#include "include/interpreter.h"
#include "../../game-container/DTO.h"

// Holds all sections of the game and initializes game logic
class Game {
private:
    Configuration configurationLibrary;
    Constants constantsLibrary;
    PerAudience perAudienceLibrary;
    PerPlayer perPlayerLibrary;
    Rules rulesLibrary;
    Variables variablesLibrary;
    const ts::Tree& tree;
    Interpreter runner;
    
public:
    Game(const ts::Tree& tree, std::string_view fileContents, 
        std::vector<Mapping> &configurationData,
        std::vector<Mapping> &constantsData,
        std::vector<Mapping> &variablesData,
        std::vector<Mapping> &perPlayerData,
        std::vector<Mapping> &perAudienceData);
    Game(std::string_view filename);
    ~Game();
    void startGame();
    void recurse(const ts::Node& node);

    Configuration* Game::getConfiguration();
    DTO Game::run();
};