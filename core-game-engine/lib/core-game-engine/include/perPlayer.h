#pragma once

#include <string>
#include <cpp-tree-sitter.h>


// Handles the per_player section of the Game file
class PerPlayer {
    private:
        ts::Node node;
    public:
        PerPlayer(const ts::Node& node);
        ~PerPlayer();
        ts::Node getNode() const;
        std::string_view getContents(const std::string_view& gameFile) const;
};