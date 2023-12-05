// TODO: Remove dead code, aka commented out code.
#include "gamesDataManager.h"


GameContainer::GameContainer(int gameContainerID) {}

int GameContainer::getGameContainerID() const
{
    return gameContainerID;
}

bool GameContainer::isClientAlreadyPlayer(const int clientID) const {
    auto it = std::find(playerIDs.begin(), playerIDs.end(), clientID);
    bool clientAlreadyPlayer = (it != playerIDs.end());
    return clientAlreadyPlayer;
};

// TODO: return a pair of bool and string to indicate status of adding player to game.
std::string GameContainer::addPlayer(const int clientID) {
    std::string response = "";

    if(isClientAlreadyPlayer(clientID)) {
        response = "Player: " + std::to_string(clientID) + " already Player.";
    } else {
        response = "client id " + std::to_string(clientID) + " added to game " + std::to_string(gameContainerID) + "\n";
    }

    return response;
}

const std::vector<int>& GameContainer::getPlayers() const {
        return playerIDs;
}

// GameContainerManager Implementation
GameContainerManager::GameContainerManager() {}

/* TODO: FEEDBACK/OPINION: it seems like the ID corresponds to the number of game container.
     another things is, as far as I can observe from this code snippet, the variable
    numberOfGameContainers directly corresponds to the gameContainerVector.size()
    there is a couplig between the two variables. How about having a function
    that returns the number of containers stored in the vector?
    In terms of design, I am curous what happens when containers are deleted.
    it doesn't seem to be implmented but there could be some conflict between the ID of the
    deleted containers and the IDs of containers that are being created.
 * */

int GameContainerManager::constructNewGameContainerID() {
    int newGameContainerID = gameContainerIdIndex;
    gameContainerIdIndex += 1;
    return newGameContainerID;
}

int GameContainerManager::createGameContainer()
{
    int gameContainerID = constructNewGameContainerID();
    gameContainerMap[gameContainerID] = std::make_unique<GameContainer>(gameContainerID);

    return gameContainerID;
}


bool GameContainerManager::doesGameContainerExist(const int gameContainerID) const
{
    auto it = gameContainerMap.find(gameContainerID);
    bool doesGameContainerExist = (it != gameContainerMap.end());
    return doesGameContainerExist;
}

GameContainer* GameContainerManager::getGameContainer(int gameContainerID) {
        auto it = gameContainerMap.find(gameContainerID);
        if (it != gameContainerMap.end()) {
            return it->second.get();
        } else {
            return nullptr; // Game container with the specified ID not found
        }
}

// TODO: This does not currently do what it is supposed to do.
// It should send message to GC to add player to game, and get response dto of success or failure from GC.
// Potentially, it may fail due to logical fault, in which case what is response?
// This is tightly coupled with ClientManager at the end of the day.


std::string GameContainerManager::addPlayerToGame(const int clientID, const int gameContainerID)
{
    // assert(doesGameContainerExist(gameContainerID))

    if (!doesGameContainerExist(gameContainerID)) {
        return "game " + std::to_string(gameContainerID) + "does not exist";
    }
    
    auto it = gameContainerMap.find(gameContainerID);
    GameContainer& gameContainer = *(it->second);

    std::string response = gameContainer.addPlayer(clientID);
    
    return response;
}

std::string GameContainerManager::giveGameContainerPlayerInput(int gameContainerID, int clientID, std::string data)
{
    std::string response =
        "gameContainer " + std::to_string(gameContainerID) + " received player " + std::to_string(clientID) +
        " input: " + data + "\n";
    return response;
}

bool ClientsManager::isClientAlreadyPlayer(const int clientID) const
{
    bool foundClientInplayerIDtoGameIDMap = playerIDtoGameIDMap.find(clientID) != playerIDtoGameIDMap.end();
    return foundClientInplayerIDtoGameIDMap;
}

bool ClientsManager::addPlayerToGame(const int clientID, const int clientGameCode)
{
    // Guard Clause 
    if (isClientAlreadyPlayer(clientID)) {
        return false;
    } 

    // Main Logic
    playerIDtoGameIDMap[clientID] = clientGameCode;

    // Successful Execution
    return true; 
}

int ClientsManager::getGameContainerIDofPlayer(const int clientID)
{
    return playerIDtoGameIDMap[clientID];
}

// Possible Error? 
bool ClientsManager::doesGameContainerIDHaveOwner(const int gameContainerID) {
    std::cout << "DEBUG LOG: ownerIDtoGameIDMap.count(gameContainerID)" << ownerIDtoGameIDMap.count(gameContainerID) << "\n";

    // bool gameContainerIDHasOwner = ownerIDtoGameIDMap.count(gameContainerID) > 0;
    for (auto item : ownerIDtoGameIDMap) {
        if (item.second == gameContainerID) {
            return true;
        }
    }

    return false;
}

bool ClientsManager::setOwnerOfGameContainer(const int clientID, const int gameContainerID)
{
    // Guard Clause 
    if (doesGameContainerIDHaveOwner(gameContainerID)) {
        return false;
    }

    ownerIDtoGameIDMap[clientID] = gameContainerID;

    return true;
}


void ClientsManager::displayPlayerGameMap() const {
    std::cout << "Player ID to Game ID Map:" << std::endl;
    for (const auto& entry : playerIDtoGameIDMap) {
        std::cout << "Player ID: " << entry.first << ", Game ID: " << entry.second << std::endl;
    }
    std::cout << std::endl;
}

void ClientsManager::displayOwnerGameMap() const {
    std::cout << "Owner ID to Game ID Map:" << std::endl;
    for (const auto& entry : ownerIDtoGameIDMap) {
        std::cout << "Owner ID: " << entry.first << ", Game ID: " << entry.second << std::endl;
    }
    std::cout << std::endl;
}
