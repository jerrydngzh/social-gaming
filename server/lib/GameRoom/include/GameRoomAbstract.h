#pragma once
#include <unordered_map>
#include <string>

class GameRoomAbstract {
public:
    virtual std::unordered_map<int, std::string> runGame(std::unordered_map<int, std::string_view> clientInputs) = 0;
};
