// TODO: Remove dead code, aka commented out code.
#include "gameContainerManager.h"

GameContainer::GameContainer(int gameContainerID) {

}

int GameContainer::getGameContainerID() const {
    return gameContainerID;
}

// GameContainerManager Implementation
GameContainerManager::GameContainerManager() {
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

int GameContainerManager::createGameContainer() {
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

bool GameContainerManager::doesGameContainerIDExist(int gameContainerID) {
    // auto gameContainerVector_iter = std::find(gameContainerVector.begin(), gameContainerVector.end(), gameContainerID);
    // return (gameContainerVector_iter != gameContainerVector.end());

    auto gameContainerVector_iter = std::find_if(gameContainerVector.begin(), gameContainerVector.end(),
                                                 [gameContainerID](const std::unique_ptr<GameContainer> &gc) {
                                                     return gc->getGameContainerID() == gameContainerID;
                                                 });
    return (gameContainerVector_iter != gameContainerVector.end());
}

// TODO: This does not currently do what it is supposed to do.
// It should send message to GC to add player to game, and get response dto of success or failure from GC.
// Potentially, it may fail due to logical fault, in which case what is response?
// This is tightly coupled with ClientManager at the end of the day.
std::string GameContainerManager::addPlayerToGame(int clientID, int gameContainerID) {
    return "client id " + std::to_string(clientID) + " added to game " + std::to_string(gameContainerID) + "\n";
}

std::string GameContainerManager::giveGameContainerPlayerInput(int gameContainerID, int clientID, std::string data) {
    std::string response =
            "gameContainer " + std::to_string(gameContainerID) + " received player " + std::to_string(clientID) +
            " input: " + data + "\n";
    return response;
}

// ClientsManager Implementation
// TODO: Function name is unclear - not sure what it does specifically.
// TODO: Unclear how this function is used, why it is used, and by who.
bool ClientsManager::isClientPlayer(int clientID) {
    bool foundClientInplayerIDtoGameIDMap = playerIDtoGameIDMap.find(clientID) != playerIDtoGameIDMap.end();
    return foundClientInplayerIDtoGameIDMap;
}

void ClientsManager::addPlayerToGame(int clientID, int clientGameCode) {
    playerIDtoGameIDMap[clientID] = clientGameCode;
}

int ClientsManager::getGameContainerIDofPlayer(int clientID) {
    return playerIDtoGameIDMap[clientID];
}

void ClientsManager::setOwnerOfGameContainer(int clientID, int gameContainerID) {
    ownerIDtoGameIDMap[clientID] = gameContainerID;
}

// CreateProcessor Implementation
CreateProcessor::CreateProcessor(GameContainerManager &gameContainerManager, ClientsManager &clientsManager)
        : gameContainerManager(gameContainerManager), clientsManager(clientsManager) {
    // Constructor implementation
}

ServerToClientsDataObject CreateProcessor::processCreateCommand(const ClientToServerDataObject &requestDTO) {
    ServerToClientsDataObject responseDTO;

    if (isCreateCommandValid(requestDTO)) {
        responseDTO = createGame(requestDTO);
    } else {
        responseDTO = invalidCreateCommandResponder(requestDTO);
    }

    return responseDTO;
}

bool CreateProcessor::isCreateCommandValid(const ClientToServerDataObject &requestDTO) {
    // Stub Function
    return true;
}

ServerToClientsDataObject CreateProcessor::createGame(const ClientToServerDataObject &requestDTO) {
    int gameContainerID = gameContainerManager.createGameContainer();
    clientsManager.setOwnerOfGameContainer(requestDTO.clientID, gameContainerID);
    std::string responseData = "create pipeline called. invite code: " + std::to_string(gameContainerID);

    ServerToClientsDataObject responseDTO;
    responseDTO.clientIDs = {requestDTO.clientID};
    responseDTO.command = "CREATE ROOM COMMAND SUCCESS";
    responseDTO.data = responseData;
    return responseDTO;
}

ServerToClientsDataObject CreateProcessor::invalidCreateCommandResponder(const ClientToServerDataObject &requestDTO) {
    // Stub Function
    ServerToClientsDataObject responseDTO;
    responseDTO.clientIDs = {requestDTO.clientID};
    responseDTO.command = "INVALID CREATE COMMAND";
    responseDTO.data = "Create Command is Invalid";
    return responseDTO;
}

// JoinProcessor Implementation
JoinProcessor::JoinProcessor(GameContainerManager &gameContainerManager, ClientsManager &clientsManager)
        : gameContainerManager(gameContainerManager), clientsManager(clientsManager) {
    // Constructor implementation
}

ServerToClientsDataObject JoinProcessor::processJoinCommand(const ClientToServerDataObject &requestDTO) {
    ServerToClientsDataObject responseDTO;

    if (isJoinCommandValid(requestDTO)) {
        responseDTO = joinGame(requestDTO);
    } else {
        responseDTO = invalidJoinCommandResponder(requestDTO);
    }

    return responseDTO;
}

bool JoinProcessor::gameContainerExists(int gameContainerID) {
    return gameContainerManager.doesGameContainerIDExist(gameContainerID);
}

bool JoinProcessor::isClientAlreadyPlayer(int clientID) {
    return clientsManager.isClientPlayer(clientID);
}


/* TODO: Using stoi and such in logic heavy code is inadvisable, since it can crash. Consider parsing the
int and storing it beforehand, wherever c2sDTO.data is first initialized, rather than parsing it
here. This brings the added benefit of not storing a string that should be an int, which saves on
memory and processing. (stringly typed APIs) */
bool JoinProcessor::isJoinCommandValid(const ClientToServerDataObject &requestDTO) {
    int gameContainerID = std::stoi(requestDTO.data);
    return (gameContainerExists(gameContainerID) && !isClientAlreadyPlayer(requestDTO.clientID));
}

// TODO: See Above 
ServerToClientsDataObject JoinProcessor::joinGame(const ClientToServerDataObject &requestDTO) {
    int gameContainerID = std::stoi(requestDTO.data);

    clientsManager.addPlayerToGame(requestDTO.clientID, gameContainerID);
    std::string gameContainerResponse = gameContainerManager.addPlayerToGame(requestDTO.clientID, gameContainerID);

    ServerToClientsDataObject responseDTO;
    responseDTO.clientIDs = {requestDTO.clientID};
    responseDTO.command = "JOIN ROOM COMMAND SUCCESS";
    responseDTO.data = gameContainerResponse;
    return responseDTO;
}

ServerToClientsDataObject JoinProcessor::invalidJoinCommandResponder(const ClientToServerDataObject &requestDTO) {
    std::string response_data = "";
    int gameContainerID = std::stoi(requestDTO.data);

    if (!gameContainerExists(gameContainerID)) {
        response_data += "Game Container " + std::to_string(gameContainerID) + " doesn't exist. ";
    }

    if (isClientAlreadyPlayer(requestDTO.clientID)) {
        response_data += "Client " + std::to_string(requestDTO.clientID) + " is already a Player. ";
    }

    ServerToClientsDataObject responseDTO;
    responseDTO.clientIDs = {requestDTO.clientID};
    responseDTO.command = "INVALID JOIN COMMAND";
    responseDTO.data = response_data;
    return responseDTO;
}

// InputProcessor Implementation
InputProcessor::InputProcessor(GameContainerManager &gameContainerManager, ClientsManager &clientsManager)
        : gameContainerManager(gameContainerManager), clientsManager(clientsManager) {
    // Constructor implementation
}

ServerToClientsDataObject InputProcessor::processInputCommand(const ClientToServerDataObject &requestDTO) {
    ServerToClientsDataObject responseDTO;

    if (isInputCommandValid(requestDTO)) {
        responseDTO = stubGameRoomManagerProcessor(requestDTO);
    } else {
        responseDTO = invalidInputCommandResponder(requestDTO);
    }

    return responseDTO;
}

bool InputProcessor::isClientPlayer(int clientID) {
    return clientsManager.isClientPlayer(clientID);
}

bool InputProcessor::isInputCommandValid(const ClientToServerDataObject &requestDTO) {
    return isClientPlayer(requestDTO.clientID);
}

ServerToClientsDataObject InputProcessor::stubGameRoomManagerProcessor(const ClientToServerDataObject &requestDTO) {
    // This should be refactored alongside GameRoomManager
    int gameContainerIDofPlayer = clientsManager.getGameContainerIDofPlayer(requestDTO.clientID);
    std::string gameContainerResponse = gameContainerManager.giveGameContainerPlayerInput(gameContainerIDofPlayer,
                                                                                          requestDTO.clientID,
                                                                                          requestDTO.data);

    ServerToClientsDataObject responseDTO;
    responseDTO.clientIDs = {requestDTO.clientID};
    responseDTO.command = "STUB_GAMEROOM RESPONSE COMMAND";
    responseDTO.data = gameContainerResponse;
    return responseDTO;
}

ServerToClientsDataObject InputProcessor::invalidInputCommandResponder(const ClientToServerDataObject &requestDTO) {
    ServerToClientsDataObject responseDTO;
    responseDTO.clientIDs = {requestDTO.clientID};
    responseDTO.command = "INVALID INPUT COMMAND";

    if (!isClientPlayer(requestDTO.clientID)) {
        responseDTO.data = "client " + std::to_string(requestDTO.clientID) + " is not a player!";
    }

    return responseDTO;
}

// InvalidCommandProcessor Implementation
ServerToClientsDataObject InvalidCommandProcessor::processInvalidCommand(const ClientToServerDataObject &requestDTO) {
    ServerToClientsDataObject responseDTO;
    responseDTO.clientIDs = {requestDTO.clientID};
    responseDTO.command = "RECEIVED_INVALID_COMMAND";
    responseDTO.data = "command not recognized: " + requestDTO.command + "\n";
    return responseDTO;
}
