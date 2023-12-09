// GameState is a wrapper class holding all the classes associated with the game state
#pragma once

#include <map>

#include "configurationState.h"
#include "memberState.h"
#include "rulesState.h"
#include "valuesState.h"

class GameState {
   public:
    GameState() = default;
    ~GameState();

    // Fields holding the state
    std::map<std::string, Setting*> settings;
    std::map<int, MemberState*> audience;
    std::map<int, MemberState*> players;
    std::map<std::string, Value*> values;
    RulesState rulesState;

    // Methods for initialization

    std::map<std::string, Value*> perPlayerValues;
    std::map<std::string, Value*> perAudienceValues;

    void addConstant(Value* value);
    void addVariable(Value* value);
    void addPerPlayer(Value* value);
    void addPerAudience(Value* value);

    void setGameFile(std::string path);

    // Methods used in the game lobby

    //   Configuration
    void addSetting(Setting* setting);
    std::vector<Setting*> getSettings() const;
    //   Players
    void addPlayer(MemberState* player);
    void addAudience(MemberState* audience);

    // Methods used in execution of the game

    void resolveRequest(int client, std::string response);
    void resolveRequest(int client, int response);
    void resolveRequest(int client, bool response);

    bool shouldResume();
};