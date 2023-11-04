#include "gameroom.h"
#include <iostream>
#include <unordered_map>
#include <string_view>

GameRoom::GameRoom(int clientIdOfOwner1) : clientIdOfOwner(clientIdOfOwner1){}


std::unordered_map<int, std::string> GameRoom::runGame(std::unordered_map<int, std::string_view> clientInputs) {
    std::unordered_map<int, std::string> mapOfReplies;
    // loop through map
    for (const auto& pair : clientInputs) {
        int clientId = pair.first;
        std::string_view clientIdMessage = pair.second;
        if(clientIdMessage == ""){
            mapOfReplies[clientId] = "None";
            continue;
        }
        switch (clientIdMessage)
        {
        // Example: "Join game room 5"
        case clientIdMessage.find("Join game room") != std::string::npos:
            int lastIndex = clientIdMessage.rfind(" ");
            std::string_view roomNumber =  clientIdMessage.substr(lastIndex + 1);
            std::cout << roomNumber << std::endl;
            if (roomNumber == gameRoomNumber) {
                this->addNewClient(clientId);
                std::string clientReply = "joined game room #" + roomNumber;
                mapOfReplies[clientId] = clientReply;
                break;
            } 
        case clientIdMessage.find("Leave game room") != std::string::npos:
            int lastIndex = clientIdMessage.rfind(" ");
            std::string_view roomNumber =  clientIdMessage.substr(lastIndex + 1);
            std::cout << roomNumber << std::endl;
            if (roomNumber == gameRoomNumber) {
                this->removeClient(clientId);
                 std::string clientReply = "removed client from game room #" + roomNumber;
                mapOfReplies[clientId] = clientReply;
            }
            break;
        case clientIdMessage.find("Change gameroom owner") != std::string::npos:
            this->setOwner(clientId);
            std::string clientReply = "Client is now owner of game room #" + roomNumber;
            mapOfReplies[clientId] = clientReply;
        default:
            mapOfReplies[clientId] = "Message not understood/not for this game room";
            break;
        }
    
    }
    return mapOfReplies;
}

void GameRoom::setOwner(int clientId) {
    this->clientIdOfOwner = clientId;
}

void GameRoom::addClient(int clientId) {
    this->numOfClients++;
    this->clientsInGameRoom.push_back()
}

void GameRoom::removeClient(int clientId) {
    this->numOfClients--;
    auto it = std::remove(this->clientsInGameRoom.begin(), this->clientsInGameRoom.end(), clientsInGameRoom);
    this->clientsInGameRoom.erase(it, this->clientsInGameRoom.end());
}