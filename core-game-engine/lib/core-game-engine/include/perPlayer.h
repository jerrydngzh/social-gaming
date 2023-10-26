#pragma once

#include <string>
#include <cpp-tree-sitter.h>
#include <vector>

#include "mapping.h"
#include "gameLibrary.h"

class PerPlayer : public GameLibrary {
    public:
        PerPlayer(const std::vector<Mapping> &data) : GameLibrary(data) {}
};

// Handles the per_player section of the Game file
// class PerPlayer {
//     private:
//         ts::Node node;
//     public:
//         PerPlayer(const ts::Node& node);
//         ~PerPlayer();
//         ts::Node getNode() const;
//         std::string_view getContents(const std::string_view& gameFile) const;
// };