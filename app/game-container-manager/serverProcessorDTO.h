#pragma once

#include <string>
#include <vector>

struct C2SDTO
{
    int clientID;
    std::string command;
    std::string data;
};

struct S2CDTO
{
    std::vector<int> clientIDs;
    std::string command;
    std::string data;
};
