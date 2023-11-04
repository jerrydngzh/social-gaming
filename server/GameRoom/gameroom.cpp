#include "gameroom.h"
#include <iostream>
#include <unordered_map>
#include <string_view>

GameRoom::GameRoom(int clientIdOfOwner1) : clientIdOfOwner(clientIdOfOwner1){}

int messageToCase(std::string_view clientIdMessage) {
    if (clientIdMessage.find("Join game room") != std::string::npos) {
        return 0;
    } else if (clientIdMessage.find("Leave game room") != std::string::npos) {
        return 1;
    } else if (clientIdMessage.find("Change gameroom owner") != std::string::npos){
        return 2;
    }
}

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
        int code = messageToCase(clientIdMessage);
        switch (code) {
        // Example: "Join game room 5"
            case 0: {
                int lastIndex = clientIdMessage.rfind(" ");
                std::string_view roomNumber = clientIdMessage.substr(lastIndex + 1);
                std::cout << roomNumber << std::endl;
                if (std::stoi(std::string(roomNumber)) == gameRoomNumber) {
                    this->addClient(clientId);
                    std::string clientReply = "joined game room #" + std::string(roomNumber);
                    mapOfReplies[clientId] = clientReply;
                }
                break; // Add break here
            }
            case 1: {
                int lastIndex = clientIdMessage.rfind(" ");
                std::string_view roomNumber = clientIdMessage.substr(lastIndex + 1);
                std::cout << roomNumber << std::endl;
                if (std::stoi(std::string(roomNumber)) == gameRoomNumber) {
                    this->removeClient(clientId);
                    std::string clientReply = "removed client from game room #" + std::string(roomNumber);
                    mapOfReplies[clientId] = clientReply;
                }
                break; // Add break here
            }
            case 2: {
                this->setOwner(clientId);
                std::string clientReply = "Client is now the owner of game room #" + std::to_string(gameRoomNumber);
                mapOfReplies[clientId] = clientReply;
                break; // Add break here
            }
            default: {
                mapOfReplies[clientId] = "Message not understood/not for this game room";
                break; // Add break here
            }
        }
    }
        
    return mapOfReplies;
}


void GameRoom::setOwner(int clientId) {
    this->clientIdOfOwner = clientId;
}

void GameRoom::addClient(int clientId) {
    this->numOfClients++;
    this->clientsInGameRoom.push_back(clientId);
}

void GameRoom::removeClient(int clientId) {
    this->numOfClients--;
    auto it = std::remove(this->clientsInGameRoom.begin(), this->clientsInGameRoom.end(), clientsInGameRoom);
    this->clientsInGameRoom.erase(it, this->clientsInGameRoom.end());
}