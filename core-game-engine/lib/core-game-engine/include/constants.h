#pragma once

#include <string>
#include <vector>
#include <mapping.h>

// Handles the constants section of the Game file
class Constants {
    private:
        std::vector<Mapping> contents;
    public:
        Constants(const std::vector<Mapping> &data);
        ~Constants();
        void print() const;
};