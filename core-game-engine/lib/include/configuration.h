#pragma once

#include <string>
#include <tuple>
#include <vector>
#include <iostream>
#include <algorithm>

#include "mapping.h"
#include "gameLibrary.h"

class Configuration : public GameLibrary {
    private:
        std::string gameName;
        bool hasAudience;
        std::tuple<int, int> playerRange;

        void setGameName();
        void setAudience();
        void setPlayerRange();
    public:
        Configuration(const std::vector<Mapping> &data);
        ~Configuration();

        std::string getGameName() const;
        bool getHasAudience() const;
        std::tuple<int, int> getPlayerRange() const;
        bool isPlayerCountInRanger(const int &playerCount) const;
};
