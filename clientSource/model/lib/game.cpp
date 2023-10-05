#include "../include/game.h"

GameType Game::getTypeOfGame() { 
    return GameType::RockPaperScissors;
}

std::ifstream Game::createJsonFile() {
    // Stub: Replace with actual implementation
    std::ifstream dummyFile("dummy.json");
    return dummyFile; 
}

std::tuple<int, int> Game::getPlayerRange() {
    return std::make_tuple(0, 0); 
}