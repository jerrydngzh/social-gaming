#pragma once

#include <string>
#include <vector>
#include <mapping.h>

class GameLibrary {
    private:
        std::vector<Mapping> contents;
    public:
        GameLibrary(const std::vector<Mapping> &data);
        ~GameLibrary();
        void print() const;
};
