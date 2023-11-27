#include "gameState.h"

//Constructors
GameState::GameState() = default;

GameState::~GameState() {
    for (auto setting : settings) {
        delete setting.second;
    }
}

//Configuration
Setting* GameState::getSetting(std::string name) const  {
    return settings.at(name);
}

std::map<std::string, Setting*> GameState::getSettings() const {
    return settings;
}

void GameState::addSetting(Setting* setting) {
    settings[setting->getName()] = setting;
}

//Players

//Values

//Rules