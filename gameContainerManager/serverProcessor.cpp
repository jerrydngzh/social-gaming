#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "serverProcessorDTO.h"

// Coupling Checklist
// Content Coupling - Clear
// Subclass Coupling - Clear
// Common / External Coupling - Clear
// Control Coupling - Not Clear
// Temporal Coupling - ???

class GameContainerManager
{
public:
    GameContainerManager(){};

    int createGameContainer()
    {
        int gameContainerID = numberOfGameContainers;

        gameContainerVector.push_back(gameContainerID);

        numberOfGameContainers++;

        return gameContainerID;
    };

    bool doesGameContainerIDExist(int gameContainerID)
    {
        auto gameContainerVector_iter = std::find(gameContainerVector.begin(), gameContainerVector.end(), gameContainerID);
        if (gameContainerVector_iter != gameContainerVector.end())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    std::string addPlayerToGame(int clientID, int gameContainerID)
    {
        return "client id " + std::to_string(clientID) + " added to game " + std::to_string(gameContainerID) + "\n";
    }

    std::string giveGameContainerPlayerInput(int gameContainerID, int clientID, std::string data)
    {
        std::string response = "gameContainer " + std::to_string(gameContainerID) + " recieved player " + std::to_string(clientID) + " input: " + data + "\n";
        return response;
    }

private:
    int numberOfGameContainers = 0;
    std::vector<int> gameContainerVector;
};

class PlayersManager
{
public:
    bool isClientPlayer(int clientID)
    {
        // TODO Control Coupling
        bool foundClientInplayerIDtoGameIDMap = playerIDtoGameIDMap.find(clientID) != playerIDtoGameIDMap.end();
        if (foundClientInplayerIDtoGameIDMap)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void addPlayerToGame(int clientID, int clientGameCode)
    {
        playerIDtoGameIDMap[clientID] = clientGameCode;
    }

    // TODO - Doesn't handle when non-clientid is passed
    int getGameContainerIDofPlayer(int clientID)
    {
        return playerIDtoGameIDMap[clientID];
    }

private:
    std::unordered_map<int, int> playerIDtoGameIDMap;
};

class OwnersManager
{
public:
    void setOwnerOfGameContainer(int clientID, int gameContainerID)
    {
        ownerIDtoGameIDMap[clientID] = gameContainerID;
    }

private:
    std::unordered_map<int, int> ownerIDtoGameIDMap;
};

// New Modules
class CreateProcessor
{
public:
    CreateProcessor(GameContainerManager &gameContainerManager, OwnersManager &ownersManager)
        : gameContainerManager(gameContainerManager), ownersManager(ownersManager){};

    S2CDTO processCreateCommand(const C2SDTO &requestDTO)
    {
        int gameContainerID = gameContainerManager.createGameContainer();

        // add clientId as owner of gamecontainerid
        ownersManager.setOwnerOfGameContainer(requestDTO.clientID, gameContainerID);

        std::string responseData = "create pipeline called. invite code: " + std::to_string(gameContainerID);

        S2CDTO responseDTO;
        responseDTO.data = responseData;

        return responseDTO;
    }

private:
    GameContainerManager &gameContainerManager;
    OwnersManager &ownersManager;
};

class JoinProcessor
{
public:
    JoinProcessor(GameContainerManager &gameContainerManager, PlayersManager &playersManager)
        : gameContainerManager(gameContainerManager), playersManager(playersManager){};


    // PRE: The command field of the requestDTO should be a JOIN command.
    // The join request is validated against server logic, then is executed. 
    // POST: Either an invalid responseDTO is generated, or a responseDTO echoing join execution status is returned
    S2CDTO processJoinCommand(const C2SDTO &requestDTO)
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

private:
    GameContainerManager &gameContainerManager;
    PlayersManager &playersManager;

private: 

    bool gameContainerExists(int gameContainerID) {
        return gameContainerManager.doesGameContainerIDExist(gameContainerID);
    }

    bool isClientAlreadyPlayer(int clientID) {
        return playersManager.isClientPlayer(clientID);
    }

    bool isJoinCommandValid(const C2SDTO &requestDTO) {
        int gameContainerID = std::stoi(requestDTO.data);

        bool isJoinCommandValid = (
            gameContainerExists(gameContainerID) 
            && 
            ! isClientAlreadyPlayer(requestDTO.clientID)
        );
        return isJoinCommandValid;
    }

    S2CDTO joinGame(const C2SDTO &requestDTO) {
        int gameContainerID = std::stoi(requestDTO.data);
        
        playersManager.addPlayerToGame(requestDTO.clientID, gameContainerID);
        std::string gameContainerResponse = gameContainerManager.addPlayerToGame(requestDTO.clientID, gameContainerID);

        S2CDTO responseDTO;

        responseDTO.clientIDs = {requestDTO.clientID};
        responseDTO.command = "JOIN ROOM COMMAND SUCCESS";
        responseDTO.data = gameContainerResponse;

        return responseDTO;
    }

    S2CDTO invalidJoinCommandResponder(const C2SDTO &requestDTO)
    {
        std::string response_data = "";
        int gameContainerID = std::stoi(requestDTO.data);

        if (! gameContainerExists(gameContainerID)) {
            response_data += "Game Container " + std::to_string(gameContainerID) + " doesn't exist. ";
        }

        if (isClientAlreadyPlayer(requestDTO.clientID)) {
            response_data += "Client " + std::to_string(requestDTO.clientID) + " is already a Player. ";
        }

        S2CDTO responseDTO;

        responseDTO.clientIDs = {requestDTO.clientID};
        responseDTO.command = "INVALID JOIN COMMAND";
        responseDTO.data = response_data;

        return responseDTO;
    }
};

class InputProcessor
{
public:
    InputProcessor(GameContainerManager &gameContainerManager, PlayersManager &playersManager)
        : gameContainerManager(gameContainerManager), playersManager(playersManager){};

    // PRE: The command field of the requestDTO should be an INPUT command.
    // The input request is validated against server logic, then is passed on to its gameroom.
    // POST: Either an invalid responseDTO is generated, or a responseDTO from a gameroom is returned
    S2CDTO processInputCommand(const C2SDTO &requestDTO)
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

private:
    GameContainerManager &gameContainerManager;
    PlayersManager &playersManager;

private:
    bool isClientPlayer(int clientID)
    {
        return playersManager.isClientPlayer(clientID);
    }

    bool isInputCommandValid(const C2SDTO &requestDTO)
    {
        if (isClientPlayer(requestDTO.clientID))
        {
            return true;
        }

        return false;
    }

    S2CDTO stubGameRoomManagerProcessor(const C2SDTO &requestDTO)
    {
        // This should be refactored alongside GameRoomManager
        int gameContainerIDofPlayer = playersManager.getGameContainerIDofPlayer(requestDTO.clientID);
        std::string gameContainerResponse = gameContainerManager.giveGameContainerPlayerInput(gameContainerIDofPlayer, requestDTO.clientID, requestDTO.data);

        S2CDTO responseDTO;

        responseDTO.clientIDs = {requestDTO.clientID};
        responseDTO.command = "STUB_GAMEROOM RESPONSE COMMAND";
        responseDTO.data = gameContainerResponse;

        return responseDTO;
    }

    S2CDTO invalidInputCommandResponder(const C2SDTO &requestDTO)
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
};

// InvalidCommandProcessor handles the case when the server platform recieves a DTO whose command
// does not match a valid/known command.
class InvalidCommandProcessor
{
public:
    InvalidCommandProcessor(){};

    // PRE: The command field of the requestDTO should be an invalid command.
    // POST: A responseDTO indicating that the command is invalid,
    // along with a description of the invalid command.
    S2CDTO processInvalidCommand(const C2SDTO &requestDTO)
    {
        S2CDTO responseDTO;

        responseDTO.clientIDs = {requestDTO.clientID};
        responseDTO.command = "RECIEVED_INVALID_COMMAND";
        responseDTO.data = "command not recognized: " + requestDTO.command + "\n";

        return responseDTO;
    }
};
