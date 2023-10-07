#pragma once

#include <string_view>
#include <memory>
#include <unordered_map>
// #include "user.h"
// #include "game.h"

class User;
class Game;

/*
Contains all the information regarding players and pre-game setup
*/
class GameRoom{
public: 
    void createGameRoom();
    // GameRoom() : gameCode(0) {};
private:
    const int gameCode;

    // A GameRoom has-a Game (composition)
    std::unique_ptr<Game> game;

    // User has fields to determine if is player, audience, or owner
    // maybe explore better way than that in defining it  
    std::unordered_map<std::string_view, std::unique_ptr<User>> perPlayer;
    std::unordered_map<std::string_view, std::unique_ptr<User>> perAudience;
};