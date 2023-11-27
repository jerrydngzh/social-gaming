#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "mapping.h"
#include "gameLibrary.h"


class Constants : public GameLibrary {
    public:
        Constants(const std::vector<Mapping> &data);
        ~Constants();
};