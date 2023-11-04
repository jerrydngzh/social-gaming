#pragma once

#include <string>
#include <cpp-tree-sitter.h>
#include <vector>

#include "mapping.h"
#include "gameLibrary.h"

class Variables : public GameLibrary {
    public:
        Variables(const std::vector<Mapping> &data);
        ~Variables();
};