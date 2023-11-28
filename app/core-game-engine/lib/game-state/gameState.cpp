#include "gameState.h"

// Constructor / Destructor

GameState::~GameState() {
    for (auto setting : settings) {
        delete setting.second;
    }
    for (auto player : players) {
        delete player.second;
    }
    for (auto audienceMember : audience) {
        delete audienceMember.second;
    }
    for (auto value : values) {
        delete value.second;
    }
    delete rulesState;
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
    players[player->id] = player;
}
void GameState::addAudience(MemberState* audienceMember) {
    audience[audienceMember->id] = audienceMember;
}