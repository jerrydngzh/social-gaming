#include <string>
#include <iostream>

#include "constants.h"
#include "mapping.h"

Constants::Constants(const std::vector<Mapping> &data):
    GameLibrary(data)
    {}

Constants::~Constants() {}