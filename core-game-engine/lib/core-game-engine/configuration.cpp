#include <tuple>
#include <string>
#include <cpp-tree-sitter.h>

#include "configuration.h"

Configuration::Configuration(const ts::Node& node) :
    node(node)
{
    //TODO: Intialization (populate gameName, players, hasAudience, settings with values from node)


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