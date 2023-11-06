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

    // takes in player request
    std::unordered_map<int, std::string> runGame(std::unordered_map<int, std::string_view> clientInputs);
    void setOwner(int clientId);
    void addClient(int clienId);
    void removeClient(int clientId);
    void processPlayerMoves(int clientId);
    void broadcastMessages(std::string_view);
    void sendMessageToClient(int clientId, std::string_view message);
    void checkProcessed();
    void handleJoinGame(std::string_view clientIdMessage, int clientId);
    void handleLeaveGame(std::string_view clientIdMessage, int clientId);
    void changeGameRoomOwner(std::string_view clientIdMessage, int clientId);
    
private:
    int gameRoomNumber;
    int numOfClients; // for the game room, set in the constructor to zero
    int clientIdOfOwner;
    std::vector<int> clientsInGameRoom;
    std::unordered_map<int, std::string> mapOfReplies;
    std::unordered_map<int, bool> isProcessedMap;

    
    // A GameRoom has-a Game-Engine
    // std::unique_ptr<Game> game;

    // User has fields to determine if is player, audience, or owner
    // maybe explore better way than that in defining it  
};