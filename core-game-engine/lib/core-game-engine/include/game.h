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
    Configuration configurationLibrary;
    Constants constantsLibrary;
    PerAudience perAudienceLibrary;
    PerPlayer perPlayerLibrary;
    Rules rulesLibrary;
    Variables variablesLibrary;
public:
    Game(
        const Configuration& configurationLibrary,
        const Constants& constantsLibrary,
        const PerAudience& perAudienceLibrary,
        const PerPlayer& perPlayerLibrary,
        const Rules& rulesLibrary,
        const Variables& variablesLibrary);
    ~Game();
    void startGame();
    void recurse(const ts::Node& node);
};
