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

// game room number is random for now
int randomNumber()
{
    std::srand(std::time(0));
    int randomGameCode = (std::rand() % 10);
    return randomGameCode;
}

// TODO: improve to be enums of request commands
// int messageToCase(std::string_view clientIdMessage)
// {
//     if (clientIdMessage.find("Join game room") != std::string::npos)
//     {
//         return 0;
//     }
//     else if (clientIdMessage.find("Leave game room") != std::string::npos)
//     {
//         return 1;
//     }
//     else if (clientIdMessage.find("Change gameroom owner") != std::string::npos)
//     {
//         return 2;
//     }
//     else if (clientIdMessage.find("Process") != std::string::npos)
//     {
//         return 3;
//     }
// }

// change clientInputs to enum?

Command messageToCommand(std::string_view clientIdMessage) {
    if (clientIdMessage.find("join game room") != std::string::npos) {
        return JOIN;
    } else if (clientIdMessage.find("leave game room") != std::string::npos) {
        return LEAVE;
    } else if (clientIdMessage.find("change gameroom owner") != std::string::npos) {
        return CHANGE_OWNER;
    } else if (clientIdMessage.find("process") != std::string::npos) {
        return PROCESS;
    } else {
        return INVALID_COMMAND; // Add an enum value for invalid commands
    }
}

std::unordered_map<int, std::string> GameRoom::runGame(std::unordered_map<int, enum> clientCommands)
{
    for (const auto &pair : clientCommands)
    {
        int clientId = pair.first;
        Command command = pair.second;
        switch (command) {
            case JOIN:
                handleJoinGame(clientId);
                break;
            case LEAVE:
                handleLeaveGame(clientId);
                break;
            case CHANGEOWNER:
                changeGameRoomOwner(clientId); 
                break;
            case PROCESS:
                processPlayerMoves(clientId);
                break;
            default:
                mapOfReplies[clientId] = "Invalid command";
                break;
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

void GameRoom::addPlayer(int clientId)
{
    this->numOfClients++;
    this->clientsInGameRoom.push_back(clientId);
}

void GameRoom::removePlayer(int clientId)
{
    this->numOfClients--;
    auto it = std::remove(this->clientsInGameRoom.begin(), this->clientsInGameRoom.end(), clientsInGameRoom);
    this->clientsInGameRoom.erase(it, this->clientsInGameRoom.end());
}

// NOTE: redo
void GameRoom::processPlayerMoves(int clientId)
{
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

void GameRoom::handleJoinGame(int clientId)
{
        this->addPlayer(clientId);
        std::string clientReply = "joined game room";
        mapOfReplies[clientId] = clientReply;
}

void GameRoom::handleLeaveGame(int clientId)
{
        this->removePlayer(clientId);
        std::string clientReply = "removed client from game room";
        mapOfReplies[clientId] = clientReply;
}

void GameRoom::changeGameRoomOwner(int clientId) {
    this->setOwner(clientId);
            std::string clientReply = "Client is now the owner of game room #" + std::to_string(gameRoomNumber);
            mapOfReplies[clientId] = clientReply;
}