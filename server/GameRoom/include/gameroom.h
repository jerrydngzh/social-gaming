#pragma once

#include <string_view>
#include <memory>
#include <unordered_map>
#include "AbstractGameRoom.h"



class User;
class Game;

/*

*/
class GameRoom : public GameRoomAbstract {
public:
    GameRoom();
    std::unordered_map<int, std::string> GameRoom::runGame(std::unordered_map<int, std::string> clientInputs);
    void handleJoinGame(int clientId);

private:
    int gameRoomNumber;
    int numOfClients;
    int clientIdOfOwner;
    std::unordered_map<std::pair<int, string>>;
    std::vector<int> clientsInGameRoom; //

    // A GameRoom has-a Game (composition)
    std::unique_ptr<Game> game;

    // User has fields to determine if is player, audience, or owner
    // maybe explore better way than that in defining it  

};