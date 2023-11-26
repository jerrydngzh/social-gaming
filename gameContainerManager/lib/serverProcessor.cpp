#include "serverProcessor.h"


  // Class GameContainer
        // Constructor 
        // 1 public function

GameContainer::GameContainer(int gameContainerID){

}

int GameContainer::getGameContainerID() const {
    return gameContainerID;
}

// GameContainerManager Implementation
GameContainerManager::GameContainerManager()
{
    // Constructor implementation
    
}

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
                                                  [gameContainerID](const std::unique_ptr<GameContainer> &gc) {
                                                      return gc->getGameContainerID() == gameContainerID;
                                                  });
    return (gameContainerVector_iter != gameContainerVector.end());

}

std::string GameContainerManager::addPlayerToGame(int clientID, int gameContainerID)
{
    return "client id " + std::to_string(clientID) + " added to game " + std::to_string(gameContainerID) + "\n";
}

std::string GameContainerManager::giveGameContainerPlayerInput(int gameContainerID, int clientID, std::string data)
{
    std::string response = "gameContainer " + std::to_string(gameContainerID) + " received player " + std::to_string(clientID) + " input: " + data + "\n";
    return response;
}

// ClientsManager Implementation
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

// CreateProcessor Implementation
CreateProcessor::CreateProcessor(GameContainerManager &gameContainerManager, ClientsManager &clientsManager)
    : gameContainerManager(gameContainerManager), clientsManager(clientsManager)
{
    // Constructor implementation
}

S2CDTO CreateProcessor::processCreateCommand(const C2SDTO &requestDTO)
{
    S2CDTO responseDTO;

    if (isCreateCommandValid(requestDTO))
    {
        responseDTO = createGame(requestDTO);
    }
    else
    {
        responseDTO = invalidCreateCommandResponder(requestDTO);
    }

    return responseDTO;
}

bool CreateProcessor::isCreateCommandValid(const C2SDTO &requestDTO)
{
    // Stub Function
    return true;
}

S2CDTO CreateProcessor::createGame(const C2SDTO &requestDTO)
{
    int gameContainerID = gameContainerManager.createGameContainer();
    clientsManager.setOwnerOfGameContainer(requestDTO.clientID, gameContainerID);
    std::string responseData = "create pipeline called. invite code: " + std::to_string(gameContainerID);

    S2CDTO responseDTO;
    responseDTO.clientIDs = {requestDTO.clientID};
    responseDTO.command = "CREATE ROOM COMMAND SUCCESS";
    responseDTO.data = responseData;
    return responseDTO;
}

S2CDTO CreateProcessor::invalidCreateCommandResponder(const C2SDTO &requestDTO)
{
    // Stub Function
    S2CDTO responseDTO;
    responseDTO.clientIDs = {requestDTO.clientID};
    responseDTO.command = "INVALID CREATE COMMAND";
    responseDTO.data = "Create Command is Invalid";
    return responseDTO;
}

// JoinProcessor Implementation
JoinProcessor::JoinProcessor(GameContainerManager &gameContainerManager, ClientsManager &clientsManager)
    : gameContainerManager(gameContainerManager), clientsManager(clientsManager)
{
    // Constructor implementation
}

S2CDTO JoinProcessor::processJoinCommand(const C2SDTO &requestDTO)
{
    S2CDTO responseDTO;

    if (isJoinCommandValid(requestDTO))
    {
        responseDTO = joinGame(requestDTO);
    }
    else
    {
        responseDTO = invalidJoinCommandResponder(requestDTO);
    }

    return responseDTO;
}

bool JoinProcessor::gameContainerExists(int gameContainerID)
{
    return gameContainerManager.doesGameContainerIDExist(gameContainerID);
}

bool JoinProcessor::isClientAlreadyPlayer(int clientID)
{
    return clientsManager.isClientPlayer(clientID);
}

bool JoinProcessor::isJoinCommandValid(const C2SDTO &requestDTO)
{
    int gameContainerID = std::stoi(requestDTO.data);
    return (gameContainerExists(gameContainerID) && !isClientAlreadyPlayer(requestDTO.clientID));
}

S2CDTO JoinProcessor::joinGame(const C2SDTO &requestDTO)
{
    int gameContainerID = std::stoi(requestDTO.data);

    clientsManager.addPlayerToGame(requestDTO.clientID, gameContainerID);
    std::string gameContainerResponse = gameContainerManager.addPlayerToGame(requestDTO.clientID, gameContainerID);

    S2CDTO responseDTO;
    responseDTO.clientIDs = {requestDTO.clientID};
    responseDTO.command = "JOIN ROOM COMMAND SUCCESS";
    responseDTO.data = gameContainerResponse;
    return responseDTO;
}

S2CDTO JoinProcessor::invalidJoinCommandResponder(const C2SDTO &requestDTO)
{
    std::string response_data = "";
    int gameContainerID = std::stoi(requestDTO.data);

    if (!gameContainerExists(gameContainerID))
    {
        response_data += "Game Container " + std::to_string(gameContainerID) + " doesn't exist. ";
    }

    if (isClientAlreadyPlayer(requestDTO.clientID))
    {
        response_data += "Client " + std::to_string(requestDTO.clientID) + " is already a Player. ";
    }

    S2CDTO responseDTO;
    responseDTO.clientIDs = {requestDTO.clientID};
    responseDTO.command = "INVALID JOIN COMMAND";
    responseDTO.data = response_data;
    return responseDTO;
}

// InputProcessor Implementation
InputProcessor::InputProcessor(GameContainerManager &gameContainerManager, ClientsManager &clientsManager)
    : gameContainerManager(gameContainerManager), clientsManager(clientsManager)
{
    // Constructor implementation
}

S2CDTO InputProcessor::processInputCommand(const C2SDTO &requestDTO)
{
    S2CDTO responseDTO;

    if (isInputCommandValid(requestDTO))
    {
        responseDTO = stubGameRoomManagerProcessor(requestDTO);
    }
    else
    {
        responseDTO = invalidInputCommandResponder(requestDTO);
    }

    return responseDTO;
}

bool InputProcessor::isClientPlayer(int clientID)
{
    return clientsManager.isClientPlayer(clientID);
}

bool InputProcessor::isInputCommandValid(const C2SDTO &requestDTO)
{
    return isClientPlayer(requestDTO.clientID);
}

S2CDTO InputProcessor::stubGameRoomManagerProcessor(const C2SDTO &requestDTO)
{
    // This should be refactored alongside GameRoomManager
    int gameContainerIDofPlayer = clientsManager.getGameContainerIDofPlayer(requestDTO.clientID);
    std::string gameContainerResponse = gameContainerManager.giveGameContainerPlayerInput(gameContainerIDofPlayer, requestDTO.clientID, requestDTO.data);

    S2CDTO responseDTO;
    responseDTO.clientIDs = {requestDTO.clientID};
    responseDTO.command = "STUB_GAMEROOM RESPONSE COMMAND";
    responseDTO.data = gameContainerResponse;
    return responseDTO;
}

S2CDTO InputProcessor::invalidInputCommandResponder(const C2SDTO &requestDTO)
{
    S2CDTO responseDTO;
    responseDTO.clientIDs = {requestDTO.clientID};
    responseDTO.command = "INVALID INPUT COMMAND";

    if (isClientPlayer(requestDTO.clientID) == false)
    {
        responseDTO.data = "client " + std::to_string(requestDTO.clientID) + " is not a player!";
    }

    return responseDTO;
}

// InvalidCommandProcessor Implementation
S2CDTO InvalidCommandProcessor::processInvalidCommand(const C2SDTO &requestDTO)
{
    S2CDTO responseDTO;
    responseDTO.clientIDs = {requestDTO.clientID};
    responseDTO.command = "RECIEVED_INVALID_COMMAND";
    responseDTO.data = "command not recognized: " + requestDTO.command + "\n";
    return responseDTO;
}