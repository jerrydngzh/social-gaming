#pragma once

#include <string>
#include <vector>
#include <cassert>
#include <iostream>
#include <map>

#include "mapping.h"

class GameLibrary {
    protected:
        std::vector<Mapping> contents;
        std::map<std::string, Mapping*> lookupMap;
        void setLookups();
    public:
        GameLibrary(const std::vector<Mapping> &data);
        ~GameLibrary();
        void print() const;
};
