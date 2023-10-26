#pragma once

#include <string>
#include <cpp-tree-sitter.h>
#include <vector>

#include "mapping.h"
#include "gameLibrary.h"

class Variables : public GameLibrary {
    public:
        Variables(const std::vector<Mapping> &data) : GameLibrary(data) {}
};

// Handles the variables section of the Game file
// class Variables {
//     private:
//         ts::Node node;
//     public:
//         Variables(const ts::Node& node);
//         ~Variables();
//         ts::Node getNode() const;
//         std::string_view getContents(const std::string_view& gameFile) const;
// };