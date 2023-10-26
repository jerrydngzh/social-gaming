#pragma once

#include <string>
#include <vector>

#include "mapping.h"
#include "gameLibrary.h"

// Handles the constants section of the Game file
// class Constants {
//     private:
//         std::vector<Mapping> contents;
//     public:
//         Constants(const std::vector<Mapping> &data);
//         ~Constants();
//         void print() const;
// };

class Constants : public GameLibrary {
    public:
        Constants(const std::vector<Mapping> &data) : GameLibrary(data) {}
};