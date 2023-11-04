#pragma once

#include <string_view>
#include <memory>
#include <unordered_map>
#include <vector>
#include "GameRoomAbstract.h"



class User;
class Game;

/*

*/
class GameRoom : public GameRoomAbstract {
public:
    GameRoom(int clientIdOfOwner1);
    std::unordered_map<int, std::string> runGame(std::unordered_map<int, std::string_view> clientInputs);
    void setOwner(int clientId);
    void addClient(int clienId);
    void removeClient(int clientId);
    
private:
    int gameRoomNumber;
    int numOfClients; // for the game room, set in the constructor to zero
    int clientIdOfOwner;
    std::vector<int> clientsInGameRoom; 

    // A GameRoom has-a Game (composition)
    std::unique_ptr<Game> game;

    // User has fields to determine if is player, audience, or owner
    // maybe explore better way than that in defining it  

};