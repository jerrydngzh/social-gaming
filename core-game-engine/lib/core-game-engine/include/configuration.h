#pragma once

#include <string>
#include <tuple>
#include <cpp-tree-sitter.h>


// Handles the configuration section of the Game file
class Configuration {
    private:
        ts::Node node;
        std::string gameName;
        std::tuple<int, int> players;
        bool hasAudience;
    public:
        Configuration(const ts::Node& node);
        ~Configuration();
        ts::Node getNode() const;
        std::string_view getContents(const std::string_view& gameFile) const;
        std::string getGameName() const;
        std::tuple<int, int> getPlayer() const;
        bool getHasAudience() const;
        bool isPlayerCountInRanger(const int playerCount) const;
};