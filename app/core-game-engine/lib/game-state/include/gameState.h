//GameState is a wrapper class holding all the classes associated with the game state
#pragma once

#include <map>
#include "configurationState.h"
#include "memberState.h"
#include "rulesState.h"
#include "valuesState.h"

class GameState {
private:
    std::map<std::string, Setting*> settings;
    std::map<int, MemberState*> audience;
    std::map<int, MemberState*> players;
    ValuesState* values;
    RulesState* rulesState;

public:
    //ConfigurationState
    void addSetting(Setting* setting);
    Setting* getSetting(std::string name) const;
    std::map<std::string, Setting*> getSettings() const;
    //players

    //values

    //rules
};