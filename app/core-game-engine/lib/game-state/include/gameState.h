// GameState is a wrapper class holding all the classes associated with the game state
#pragma once

#include <map>

#include "configurationState.h"
#include "memberState.h"
#include "rulesState.h"
#include "valuesState.h"

class GameState {
   public:
    ~GameState();

    std::map<std::string, Setting*> settings;
    std::map<int, MemberState*> audience;
    std::map<int, MemberState*> players;
    std::map<std::string, Value*> values;
    RulesState* rulesState;

    // Methods for interacting with Game Container

    //   Configuration
    void addSetting(Setting* setting);
    std::vector<Setting*> getSettings() const;
    //   Players
    void addPlayer(MemberState* player);
    void addAudience(MemberState* audience);
};