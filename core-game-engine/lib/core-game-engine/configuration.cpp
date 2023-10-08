#include <tuple>
#include <string>
#include <cpp-tree-sitter.h>

#include "configuration.h"

Configuration::Configuration(const ts::Node& node):
    node(node)
    {}

Configuration::~Configuration() {}


ts::Node Configuration::getNode() const {
    return node;
}

std::string_view Configuration::getContents(const std::string_view& gameFile) const {
    return node.getSourceRange(gameFile);
}

std::string Configuration::getGameName() const{
    return gameName;
}

std::tuple<int, int> Configuration::getPlayer() const{
    return players;
}

bool Configuration::getHasAudience() const{
    return hasAudience;
}

bool Configuration::isPlayerCountInRanger(const int playerCount) const {
    return playerCount >= std::get<0>(players) && playerCount <= std::get<1>(players);
}