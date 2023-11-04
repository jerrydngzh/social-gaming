#pragma once

#include <string>
#include <vector>
#include <mapping.h>
#include <cassert>

class GameLibrary {
    protected:
        std::vector<Mapping> contents;
    public:
        GameLibrary(const std::vector<Mapping> &data);
        ~GameLibrary();
        void print() const;
};
