#pragma once

#include <string>
#include <vector>

#include "mapping.h"
#include "gameLibrary.h"

class Variables : public GameLibrary {
    public:
        Variables(const std::vector<Mapping> &data);
        ~Variables();
};