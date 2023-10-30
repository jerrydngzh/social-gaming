#pragma once

#include <string>
#include <cpp-tree-sitter.h>
#include <vector>

#include "mapping.h"
#include "gameLibrary.h"

class PerPlayer : public GameLibrary {
    public:
        PerPlayer(const std::vector<Mapping> &data);
        ~PerPlayer();
};