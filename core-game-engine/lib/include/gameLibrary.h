#pragma once

#include <string>
#include <vector>
#include <cassert>
#include <iostream>

#include "mapping.h"

class GameLibrary {
    protected:
        std::vector<Mapping> contents;
    public:
        GameLibrary(const std::vector<Mapping> &data);
        ~GameLibrary();
        void print() const;
};
