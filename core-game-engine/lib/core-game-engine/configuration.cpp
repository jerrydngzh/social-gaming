#include <tuple>
#include <string>
#include <cpp-tree-sitter.h>
#include <iostream>
#include <algorithm>
#include <regex>

#include "configuration.h"

const std::string Configuration::GAME_NAME_FIELD = std::string("name");
const std::string Configuration::PLAYERS_FIELD = std::string("player_range");
const std::string Configuration::AUDIENCE_FIELD = std::string("has_audience");
const std::string Configuration::SETUP_FIELD = std::string("setup");

Configuration::Configuration(const ts::Node& node, const std::string_view& gameFile) :
    node(node), gameFile(gameFile)
{
    //TODO: Intialization (populate gameName, players, hasAudience, settings with values from node)
    gameName = node.getChildByFieldName(GAME_NAME_FIELD).getSourceRange(this->getGameFile());
    std::string_view playersString = node.getChildByFieldName(PLAYERS_FIELD).getSourceRange(this->getGameFile());
    parsePlayers(playersString);
    hasAudience = node.getChildByFieldName(AUDIENCE_FIELD).getSourceRange(this->getGameFile()) == "true";

    std::string settingsString(node.getNamedChild(3).getSourceRange(this->getGameFile()));

    std::istringstream iss(settingsString);
    std::string line;
    std::string kind, prompt, range;
    settings = std::vector<Setting>();

    while (std::getline(iss, line)) {
        if (line.find("kind") != std::string::npos) {
            kind = line.substr(line.find(":") + 1);
        }

        if(line.find("prompt") != std::string::npos) {
            prompt = line.substr(line.find(":") + 1);
            if (kind == "boolean") {
                settings.push_back(BooleanSetting(prompt));
                break;
            } 
        }
            
        if(line.find("range") != std::string::npos) {
            line.erase(std::remove_if(line.begin(), line.end(), [](unsigned char c) {
                return std::isspace(c);
            }), line.end());
            range = line.substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
            std::istringstream stream(range);
            std::string token, min, max;
            std::getline(stream, token, ',');
            min = std::stoi(token);
            std::getline(stream, token, ',');
            max = std::stoi(token);
            std::cout << "min: " << min << "max: " << max << std::endl;
        }           
    }
}

void Configuration::parsePlayers(const std::string_view& playersString){
    std::string_view parsedStr = playersString.substr(1, playersString.size() - 2);
    char minString = parsedStr[0];
    char maxString = parsedStr[parsedStr.size() - 1];
    std::get<0>(players) = minString;
    std::get<1>(players) = maxString;
}

Configuration::~Configuration() {}

Configuration::Setting::Setting(Kind kind, std::string prompt, const bool hasDefaultValue) :
    kind(kind),
    prompt(prompt),
    hasDefaultValue(hasDefaultValue)
{}

std::string Configuration::Setting::getPrompt() const {
    return prompt;
}

Configuration::Setting::Kind Configuration::Setting::getKind() const {
    return kind;
}

bool Configuration::Setting::getHasDefaultValue() const {
    return hasDefaultValue;
}

Configuration::BooleanSetting::BooleanSetting(std::string prompt, const bool defaultValue) :
    Setting(Kind::BOOLEAN, prompt, true),
    defaultValue(defaultValue),
    value(defaultValue)
{}

Configuration::BooleanSetting::BooleanSetting(std::string prompt) :
    Setting(Kind::BOOLEAN, prompt, false)
{}

Configuration::BooleanSetting::~BooleanSetting() {}

bool Configuration::BooleanSetting::getValue() const {
    return value;
}

void Configuration::BooleanSetting::setValue(const bool value) {
    this->value = value;
}

bool Configuration::BooleanSetting::getDefaultValue() const {
    return defaultValue;
}

Configuration::IntegerSetting::IntegerSetting(std::string prompt, const int defaultValue, const int min, const int max) :
    Setting(Kind::INTEGER, prompt, true),
    defaultValue(defaultValue),
    value(defaultValue),
    range(std::make_tuple(min, max))
{}

Configuration::IntegerSetting::IntegerSetting(std::string prompt, const int min, const int max) :
    Setting(Kind::INTEGER, prompt, false),
    range(std::make_tuple(min, max))
{}

Configuration::IntegerSetting::~IntegerSetting() {}

int Configuration::IntegerSetting::getValue() const {
    return value;
}

void Configuration::IntegerSetting::setValue(const int value) {
    this->value = value;
}

int Configuration::IntegerSetting::getDefaultValue() const {
    return defaultValue;
}

ts::Node Configuration::getNode() const {
    return node;
}

std::string_view Configuration::getGameFile() const {
    return gameFile;
}

std::string_view Configuration::getContents(const std::string_view& gameFile) const {
    return node.getSourceRange(gameFile);
}

std::string Configuration::getGameName() const {
    return gameName;
}

std::tuple<int, int> Configuration::getPlayer() const {
    return players;
}

bool Configuration::getHasAudience() const {
    return hasAudience;
}

bool Configuration::isPlayerCountInRanger(const int playerCount) const {
    return playerCount >= std::get<0>(players) && playerCount <= std::get<1>(players);
}