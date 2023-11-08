#pragma once

#include <string>
#include <vector>

#include "mapping.h"
#include "gameLibrary.h"

class PerAudience : public GameLibrary {
    public:
        PerAudience(const std::vector<Mapping> &data);
        ~PerAudience();
};
