#include "gameState.h"
#include <iostream>

// Destructor

GameState::~GameState() {
    for (auto setting : settings) {
        delete setting.second;
    }
    for (auto audienceMember : audience) {
        delete audienceMember.second;
    }
    for (auto player : players) {
        delete player.second;
    }
    for (auto value : values) {
        delete value.second;
    }
    for (auto value : perPlayerValues) {
        delete value.second;
    }
    for (auto value : perAudienceValues) {
        delete value.second;
    }
}

// Methods for initialization

void GameState::addConstant(Value* value) {
    value->isConst = true;
    values.insert(std::make_pair(value->name, value));
    // values [value->name] = value;
}

void GameState::addVariable(Value* value) {
    values.insert(std::make_pair(value->name, value));
    //values[value->name] = value;
}

void GameState::addPerPlayer(Value* value) {
    perPlayerValues[value->name] = value;
}

void GameState::addPerAudience(Value* value) {
    perAudienceValues[value->name] = value;
}

// Configuration
std::vector<Setting*> GameState::getSettings() const {
    std::vector<Setting*> settingsVector;
    for (auto setting : settings) {
        settingsVector.push_back(setting.second);
    }
    return settingsVector;
}

void GameState::addSetting(Setting* setting) {
    settings[setting->name] = setting;
}

// Players
void GameState::addPlayer(MemberState* player) {
    player->elements.insert(perPlayerValues.begin(), perPlayerValues.end());
    players[player->id] = player;
}
void GameState::addAudience(MemberState* audienceMember) {
    audienceMember->elements.insert(perAudienceValues.begin(), perAudienceValues.end());
    audience[audienceMember->id] = audienceMember;
}