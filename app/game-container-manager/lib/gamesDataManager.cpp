// TODO: Remove dead code, aka commented out code.
#include "gamesDataManager.h"

GameContainer::GameContainer(int gameContainerID)
{
}

int GameContainer::getGameContainerID() const
{
    return gameContainerID;
}

// GameContainerManager Implementation
GameContainerManager::GameContainerManager()
{
    // Constructor implementation
}

/* TODO: FEEDBACK/OPINION: it seems like the ID corresponds to the number of game container.
     another things is, as far as I can observe from this code snippet, the variable
    numberOfGameContainers directly corresponds to the gameContainerVector.size()
    there is a couplig between the two variables. How about having a function
    that returns the number of containers stored in the vector?
    In terms of design, I am curous what happens when containers are deleted.
    it doesn't seem to be implmented but there could be some conflict between the ID of the
    deleted containers and the IDs of containers that are being created.
 * */

int GameContainerManager::createGameContainer()
{
    int gameContainerID = numberOfGameContainers;

    // This does not actually create a Game Container and Store it!!!
    // gameContainerVector.push_back(gameContainerID);

    // Future Code
    // GameContainer newGame = gameContainer(gameContainerID);
    // gameContainerVector.push_back(gameContainer);
    // map gameContainerID to gameContainer

    gameContainerVector.push_back(std::make_unique<GameContainer>(gameContainerID));
    gameContainerMap[gameContainerID] = gameContainerVector.back().get();

    numberOfGameContainers++;
    return gameContainerID;
}

bool GameContainerManager::doesGameContainerIDExist(int gameContainerID)
{
    // auto gameContainerVector_iter = std::find(gameContainerVector.begin(), gameContainerVector.end(), gameContainerID);
    // return (gameContainerVector_iter != gameContainerVector.end());

    auto gameContainerVector_iter = std::find_if(gameContainerVector.begin(), gameContainerVector.end(),
                                                 [gameContainerID](const std::unique_ptr<GameContainer> &gc)
                                                 {
                                                     return gc->getGameContainerID() == gameContainerID;
                                                 });
    return (gameContainerVector_iter != gameContainerVector.end());
}

// TODO: This does not currently do what it is supposed to do.
// It should send message to GC to add player to game, and get response dto of success or failure from GC.
// Potentially, it may fail due to logical fault, in which case what is response?
// This is tightly coupled with ClientManager at the end of the day.
std::string GameContainerManager::addPlayerToGame(int clientID, int gameContainerID)
{
    return "client id " + std::to_string(clientID) + " added to game " + std::to_string(gameContainerID) + "\n";
}

std::string GameContainerManager::giveGameContainerPlayerInput(int gameContainerID, int clientID, std::string data)
{
    std::string response =
        "gameContainer " + std::to_string(gameContainerID) + " received player " + std::to_string(clientID) +
        " input: " + data + "\n";
    return response;
}

// ClientsManager Implementation
// TODO: Function name is unclear - not sure what it does specifically.
// TODO: Unclear how this function is used, why it is used, and by who.
bool ClientsManager::isClientPlayer(int clientID)
{
    bool foundClientInplayerIDtoGameIDMap = playerIDtoGameIDMap.find(clientID) != playerIDtoGameIDMap.end();
    return foundClientInplayerIDtoGameIDMap;
}

void ClientsManager::addPlayerToGame(int clientID, int clientGameCode)
{
    playerIDtoGameIDMap[clientID] = clientGameCode;
}

int ClientsManager::getGameContainerIDofPlayer(int clientID)
{
    return playerIDtoGameIDMap[clientID];
}

void ClientsManager::setOwnerOfGameContainer(int clientID, int gameContainerID)
{
    ownerIDtoGameIDMap[clientID] = gameContainerID;
}
