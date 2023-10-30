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

// Holds all sections of the game and initializes game logic
class Game {
private:
    Extractor extractor;
    Configuration configurationLibrary;
    Constants constantsLibrary;
    PerAudience perAudienceLibrary;
    PerPlayer perPlayerLibrary;
    Rules rulesLibrary;
    Variables variablesLibrary;
    const ts::Tree& tree;
    
public:
    Game(const ts::Tree& tree, std::string_view fileContents);
    ~Game();
    void startGame();
    void recurse(const ts::Node& node);
};
