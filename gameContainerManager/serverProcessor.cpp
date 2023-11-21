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

    S2CDTO processJoinCommand(const C2SDTO &requestDTO)
    {
        std::string response = "join pipeline called \n";

        int clientGameCode = std::stoi(requestDTO.data);

        std::cout << "Test \n";

        // TODO Control Coupling
        // check if clientGameCode maps to gameContainerID
        bool gameContainerExists = gameContainerManager.doesGameContainerIDExist(clientGameCode);
        if (gameContainerExists)
        {
            std::cout << "Test in\n";

            response += "Game to Join Exists! \n";

            // TODO Control Coupling
            bool isClientAlreadyPlayer = playersManager.isClientPlayer(requestDTO.clientID);
            if (isClientAlreadyPlayer)
            {
                response += "This client is already a player of another game! \n";
            }
            else
            {
                response += "This client can play this game \n";
                playersManager.addPlayerToGame(requestDTO.clientID, clientGameCode);

                std::string gameContainerResponse = gameContainerManager.addPlayerToGame(requestDTO.clientID, clientGameCode);
                response += gameContainerResponse;
            }
        }
        else
        {
            std::cout << "Test out \n";
            response += "Game to Join Doesn't Exists! \n";
        }

        S2CDTO responseDTO;
        responseDTO.data = response;

        return responseDTO;
    }

private:
    GameContainerManager &gameContainerManager;
    PlayersManager &playersManager;
};

class InputProcessor
{
public:
    InputProcessor(GameContainerManager &gameContainerManager, PlayersManager &playersManager)
        : gameContainerManager(gameContainerManager), playersManager(playersManager){};

    S2CDTO processInputCommand(const C2SDTO &requestDTO)
    {
        std::string response = "player input pipeline called \n";

        // TODO Control Coupling
        bool isClientPlayer = playersManager.isClientPlayer(requestDTO.clientID);
        if (isClientPlayer)
        {
            response += "client is player \n";

            int gameContainerIDofPlayer = playersManager.getGameContainerIDofPlayer(requestDTO.clientID);
            std::string gameContainerResponse = gameContainerManager.giveGameContainerPlayerInput(gameContainerIDofPlayer, requestDTO.clientID, requestDTO.data);
            response += gameContainerResponse;
        }
        else
        {
            response += "client is not player! Error! \n";
        }

        S2CDTO responseDTO;
        responseDTO.data = response;

        return responseDTO;
    }

private:
    GameContainerManager &gameContainerManager;
    PlayersManager &playersManager;
};

class InvalidCommandProcessor
{
public:
    InvalidCommandProcessor(){};

    S2CDTO processInvalidCommand(const C2SDTO &requestDTO)
    {
        S2CDTO responseDTO;

        responseDTO.data = "command not recognized: " + requestDTO.command + "\n";

        return responseDTO;
    }
};
