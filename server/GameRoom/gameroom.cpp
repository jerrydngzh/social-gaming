#include "gameroom.h"
#include <iostream>
#include <unordered_map>
#include <string_view>
#include <ctime>
#include <algorithm>

GameRoom::GameRoom(int clientIdOfOwner1) : clientIdOfOwner(clientIdOfOwner1)
{
    this->numOfClients = 1;
    this->gameRoomNumber = randomNumber();
    this->clientsInGameRoom.push_back(clientIdOfOwner1);
}

int randomNumber()
{
    std::srand(std::time(0));
    int randomGameCode = (std::rand() % 10);
    return randomGameCode;
}

// TODO: improve to be enums of request commands
int messageToCase(std::string_view clientIdMessage)
{
    if (clientIdMessage.find("Join game room") != std::string::npos)
    {
        return 0;
    }
    else if (clientIdMessage.find("Leave game room") != std::string::npos)
    {
        return 1;
    }
    else if (clientIdMessage.find("Change gameroom owner") != std::string::npos)
    {
        return 2;
    }
    else if (clientIdMessage.find("Process") != std::string::npos)
    {
        return 3;
    }
}

std::unordered_map<int, std::string> GameRoom::runGame(std::unordered_map<int, std::string_view> clientInputs)
{

    // loop through map
    for (const auto &pair : clientInputs)
    {
        int clientId = pair.first;
        std::string_view clientIdMessage = pair.second;
        if (clientIdMessage == "")
        {
            mapOfReplies[clientId] = "None";
            continue;
        }
        int code = messageToCase(clientIdMessage);
        switch (code)
        {
            // Example: "Join game room 5"
        case 0:
        {
            handleJoinGame(clientIdMessage, clientId);
            break;
        }
        case 1:
        {
            handleLeaveGame(clientIdMessage, clientId);
            break;
        }
        case 2:
        {
            changeGameRoomOwner(clientIdMessage, clientId);
            break;
        }
        case 3:
        {
            processPlayerMoves(clientId);
        }
        default:
        {
            mapOfReplies[clientId] = "Message not understood/not for this game room";
            break; // Add break here
        }
        }
    }
    // check if all clients have processed their moves
    checkProcessed();
    return mapOfReplies;
}

// NOTE: redo
void GameRoom::checkProcessed()
{
    bool allProcessed = std::all_of(isProcessedMap.begin(), isProcessedMap.end(),
                                    [](const std::pair<int, bool> &pair)
                                    {
                                        return pair.second == true;
                                    });
    if (allProcessed)
    {
        broadcastMessages("Winner is player 1");
    }
    else
    {
        broadcastMessages("Waiting for player 3. He is a slowpoke");
    }
}

void GameRoom::setOwner(int clientId)
{
    this->clientIdOfOwner = clientId;
}

void GameRoom::addClient(int clientId)
{
    this->numOfClients++;
    this->clientsInGameRoom.push_back(clientId);
}

void GameRoom::removeClient(int clientId)
{
    this->numOfClients--;
    auto it = std::remove(this->clientsInGameRoom.begin(), this->clientsInGameRoom.end(), clientsInGameRoom);
    this->clientsInGameRoom.erase(it, this->clientsInGameRoom.end());
}

// NOTE: redo
void GameRoom::processPlayerMoves(int clientId)
{
    mapOfReplies[clientId] = "Processed";
    isProcessedMap[clientId] = true;
}

// NOTE: redo?
void GameRoom::broadcastMessages(std::string_view message)
{
    for (const auto &pair : this->mapOfReplies)
    {
        int client = pair.first;
        this->sendMessageToClient(client, message);
    }
}

void GameRoom::sendMessageToClient(int clientId, std::string_view message)
{
    this->mapOfReplies[clientId] = std::string(message);
}

void GameRoom::handleJoinGame(std::string_view clientIdMessage, int clientId)
{
    int lastIndex = clientIdMessage.rfind(" ");
    std::string_view roomNumber = clientIdMessage.substr(lastIndex + 1);
    std::cout << roomNumber << std::endl;
    if (std::stoi(std::string(roomNumber)) == gameRoomNumber)
    {
        this->addClient(clientId);
        std::string clientReply = "joined game room #" + std::string(roomNumber);
        mapOfReplies[clientId] = clientReply;
    }
}

void GameRoom::handleLeaveGame(std::string_view clientIdMessage, int clientId)
{
    int lastIndex = clientIdMessage.rfind(" ");
    std::string_view roomNumber = clientIdMessage.substr(lastIndex + 1);
    std::cout << roomNumber << std::endl;
    if (std::stoi(std::string(roomNumber)) == gameRoomNumber)
    {
        this->removeClient(clientId);
        std::string clientReply = "removed client from game room #" + std::string(roomNumber);
        mapOfReplies[clientId] = clientReply;
    }
}

void GameRoom::changeGameRoomOwner(std::string_view clientIdMessage, int clientId) {
    this->setOwner(clientId);
            std::string clientReply = "Client is now the owner of game room #" + std::to_string(gameRoomNumber);
            mapOfReplies[clientId] = clientReply;
}