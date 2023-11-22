//GameState is a wrapper class holding all the classes associated with the game state
#pragma once

#include "configurationState.h"
#include "memberState.h"
#include "rulesState.h"
#include "valuesState.h"

class GameState {
private:
    ConfigurationState* configurationState;
    std::vector<MemberState*> audience; //Maybe should be a map of id to member?
    std::vector<MemberState*> players; //or have a wrapper like ValuesState?
    RulesState* rulesState;
    ValuesState* values;
};