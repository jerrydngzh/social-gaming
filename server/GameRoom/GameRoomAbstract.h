#pragma once
#include <unordered_map>

class GameRoomAbstract {
public:
    virtual std::unordered_map<int, std::string> runGame(std::unordered_map<int, std::string> clientInputs) = 0;
};
