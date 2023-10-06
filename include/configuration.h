#pragma once
#include <string>
#include <tuple>
#include <cpp-tree-sitter.h>

class Configuration {
    private:
        std::string gameName;
        std::tuple<int, int> players;
        bool hasAudience;
    public:
        Configuration(const ts::Node& root);
        std::string getGameName() const;
        std::tuple<int, int> getPlayer() const;
        bool getHasAudience() const;
        bool isPlayerCountInRanger() const;

};