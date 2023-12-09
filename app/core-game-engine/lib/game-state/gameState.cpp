#include "gameState.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

std::string fileToString(const std::string& filepath);

extern "C" {
TSLanguage* tree_sitter_socialgaming();
}

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
    values[value->name] = value;
}
void GameState::addVariable(Value* value) {
    values[value->name] = value;
}

void GameState::addPerPlayer(Value* value) {
    perPlayerValues[value->name] = value;
}
void GameState::addPerAudience(Value* value) {
    perAudienceValues[value->name] = value;
}

void GameState::setGameFile(std::string path) {
    // Rule Tree
    ts::Language language = tree_sitter_socialgaming();
    ts::Parser parser{language};
    std::string fileContents = fileToString(path);
    ts::Tree* tree = new ts::Tree(parser.parseString(fileContents));

    rulesState.rawGameFile = fileContents;
    rulesState.tree = tree;
    rulesState.currentNode = tree->getRootNode().getChildByFieldName("rules");
    rulesState.nextNode = rulesState.currentNode;
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

// Execution
void GameState::resolveRequest(int client, std::string response) {
    Value* target = rulesState.requests[client];
    assert(target->kind == Value::Kind::STRING && "Response recieved doesn't match target type.");
    static_cast<StringValue*>(target)->value = response;
    rulesState.requests.erase(client);
}
void GameState::resolveRequest(int client, int response) {
    Value* target = rulesState.requests[client];
    assert(target->kind == Value::Kind::INTEGER && "Response recieved doesn't match target type.");
    static_cast<IntegerValue*>(target)->value = response;
    rulesState.requests.erase(client);
}
void GameState::resolveRequest(int client, bool response) {
    Value* target = rulesState.requests[client];
    assert(target->kind == Value::Kind::BOOLEAN && "Response recieved doesn't match target type.");
    static_cast<BooleanValue*>(target)->value = response;
    rulesState.requests.erase(client);
}

bool GameState::shouldResume() {
    return rulesState.isParallel || rulesState.requests.size() == 0;
}

std::string fileToString(const std::string& filepath) {
    std::ifstream file;
    file.open(filepath);

    if (!file.is_open()) {
        throw std::invalid_argument("Error opening file. Check if file path is correct");
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string fileContents = buffer.str();

    return fileContents;
}