#include "serverProcessors.h"

// CreateProcessor Implementation
CreateProcessor::CreateProcessor(GameContainerManager &gameContainerManager, ClientsManager &clientsManager)
    : gameContainerManager(gameContainerManager), clientsManager(clientsManager)
{
    // Constructor implementation
}

ServerToClientsDataObject CreateProcessor::process(const ClientToServerDataObject &requestDTO)
{
    if (isCreateCommandValid(requestDTO))
    {
        ServerToClientsDataObject responseDTO = createGame(requestDTO);
        return responseDTO;
    }
    else
    {
        ServerToClientsDataObject responseDTO = invalidCreateCommandResponder(requestDTO);
        return responseDTO;
    }
}

bool CreateProcessor::isCreateCommandValid(const ClientToServerDataObject &requestDTO)
{
    // Stub Function
    return true;
}

ServerToClientsDataObject CreateProcessor::createGame(const ClientToServerDataObject &requestDTO)
{
    int gameContainerID = gameContainerManager.createGameContainer();
    std::cout << "DEBUG LOG: gameContainerID " << gameContainerID << "\n";
    // TODO setOwnerOfGameContainer failing
    bool validCreateGame = clientsManager.setOwnerOfGameContainer(requestDTO.clientID, gameContainerID);

    if (validCreateGame) {
        std::vector<uintptr_t> clientIDs = {requestDTO.clientID};
        std::string command = "CREATE ROOM COMMAND SUCCESS";
        std::string data = "create pipeline called. invite code: " + std::to_string(gameContainerID);
        ServerToClientsDataObject responseDTO = {clientIDs, command, data};
        return responseDTO;
    } else {
        std::vector<uintptr_t> clientIDs = {requestDTO.clientID};
        std::string command = "CREATE ROOM COMMAND FAILED";
        std::string data = "TODO Error Message";
        ServerToClientsDataObject responseDTO = {clientIDs, command, data};
        return responseDTO;
    }
}

ServerToClientsDataObject CreateProcessor::invalidCreateCommandResponder(const ClientToServerDataObject &requestDTO)
{
    std::vector<uintptr_t> clientIDs = {requestDTO.clientID};
    std::string command = "INVALID CREATE COMMAND";
    std::string data = "Create Command is Invalid";
    ServerToClientsDataObject responseDTO = {clientIDs, command, data};
    return responseDTO;
}

// JoinProcessor Implementation
JoinProcessor::JoinProcessor(GameContainerManager &gameContainerManager, ClientsManager &clientsManager)
    : gameContainerManager(gameContainerManager), clientsManager(clientsManager)
{
    // Constructor implementation
}

ServerToClientsDataObject JoinProcessor::process(const ClientToServerDataObject &requestDTO)
{
    if (isJoinCommandValid(requestDTO))
    {
        ServerToClientsDataObject responseDTO = joinGame(requestDTO);
        return responseDTO;
    }
    else
    {
        ServerToClientsDataObject responseDTO = invalidJoinCommandResponder(requestDTO);
        return responseDTO;
    }
}

bool JoinProcessor::gameContainerExists(int gameContainerID)
{
    return gameContainerManager.doesGameContainerIDExist(gameContainerID);
}

bool JoinProcessor::isClientAlreadyPlayer(int clientID)
{
    return clientsManager.isClientAlreadyPlayer(clientID);
}

/* TODO: Using stoi and such in logic heavy code is inadvisable, since it can crash. Consider parsing the
int and storing it beforehand, wherever c2sDTO.data is first initialized, rather than parsing it
here. This brings the added benefit of not storing a string that should be an int, which saves on
memory and processing. (stringly typed APIs) */
bool JoinProcessor::isJoinCommandValid(const ClientToServerDataObject &requestDTO)
{
    int gameContainerID = std::stoi(requestDTO.data);
    return (gameContainerExists(gameContainerID) && !isClientAlreadyPlayer(requestDTO.clientID));
}

// TODO: See Above
ServerToClientsDataObject JoinProcessor::joinGame(const ClientToServerDataObject &requestDTO)
{
    int gameContainerID = std::stoi(requestDTO.data);

    bool validAddPlayerToGame = clientsManager.addPlayerToGame(requestDTO.clientID, gameContainerID);

    if (validAddPlayerToGame) {
        std::vector<uintptr_t> clientIDs = {requestDTO.clientID};
        std::string command = "JOIN ROOM COMMAND SUCCESS";
        std::string data = gameContainerManager.addPlayerToGame(requestDTO.clientID, gameContainerID);
        ServerToClientsDataObject responseDTO = {clientIDs, command, data};
        return responseDTO;
    } else {
        std::vector<uintptr_t> clientIDs = {requestDTO.clientID};
        std::string command = "JOIN ROOM COMMAND FAILURE";
        std::string data = "TODO ERROR MESSAGE";
        ServerToClientsDataObject responseDTO = {clientIDs, command, data};
        return responseDTO;
    }
}

ServerToClientsDataObject JoinProcessor::invalidJoinCommandResponder(const ClientToServerDataObject &requestDTO)
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

    std::vector<uintptr_t> clientIDs = {requestDTO.clientID};
    std::string command = "INVALID JOIN COMMAND";
    std::string data = response_data;
    ServerToClientsDataObject responseDTO = {clientIDs, command, data};
    return responseDTO;
}

// InputProcessor Implementation
InputProcessor::InputProcessor(GameContainerManager &gameContainerManager, ClientsManager &clientsManager)
    : gameContainerManager(gameContainerManager), clientsManager(clientsManager)
{
    // Constructor implementation
}

ServerToClientsDataObject InputProcessor::process(const ClientToServerDataObject &requestDTO)
{
    if (isInputCommandValid(requestDTO))
    {
        ServerToClientsDataObject responseDTO = stubGameRoomManagerProcessor(requestDTO);
        return responseDTO;
    }
    else
    {
        ServerToClientsDataObject responseDTO = invalidInputCommandResponder(requestDTO);
        return responseDTO;
    }
}

bool InputProcessor::isClientPlayer(int clientID)
{
    return clientsManager.isClientAlreadyPlayer(clientID);
}

bool InputProcessor::isInputCommandValid(const ClientToServerDataObject &requestDTO)
{
    return isClientPlayer(requestDTO.clientID);
}

// TODO - The gameContainerResponse var is too long. 
ServerToClientsDataObject InputProcessor::stubGameRoomManagerProcessor(const ClientToServerDataObject &requestDTO)
{
    // This should be refactored alongside GameRoomManager
    int gameContainerIDofPlayer = clientsManager.getGameContainerIDofPlayer(requestDTO.clientID);
    std::string gameContainerResponse = gameContainerManager.giveGameContainerPlayerInput(gameContainerIDofPlayer,
                                                                                          requestDTO.clientID,
                                                                                          requestDTO.data);

    
    std::vector<uintptr_t> clientIDs = {requestDTO.clientID};
    std::string command = "STUB_GAMEROOM RESPONSE COMMAND";
    std::string data = gameContainerResponse;
    ServerToClientsDataObject responseDTO = {clientIDs, command, data};
    return responseDTO;
}

// TODO - Need to make making error messages easier to use / construct. 

ServerToClientsDataObject InputProcessor::invalidInputCommandResponder(const ClientToServerDataObject &requestDTO)
{
    std::vector<uintptr_t> clientIDs = {requestDTO.clientID};
    std::string command = "INVALID INPUT COMMAND";

    std::string data = "";
    if (!isClientPlayer(requestDTO.clientID))
    {
        data = "client " + std::to_string(requestDTO.clientID) + " is not a player!";
    }

    ServerToClientsDataObject responseDTO = {clientIDs, command, data};
    return responseDTO;
}

// InvalidCommandProcessor Implementation
// TODO - Need to make making error messages easier to use / construct. 
ServerToClientsDataObject InvalidCommandProcessor::process(const ClientToServerDataObject &requestDTO)
{
    std::vector<uintptr_t> clientIDs = {requestDTO.clientID};
    std::string command = "RECEIVED_INVALID_COMMAND";
    std::string data = "command not recognized: " + requestDTO.command + "\n";
    ServerToClientsDataObject responseDTO = {clientIDs, command, data};
    return responseDTO;
}
