#include "configuration.h"
#include <tuple>
#include <string>

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