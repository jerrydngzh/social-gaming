#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "serverProcessorDTO.h"
// #include "gameContainerManager.cpp"

class GameContainerManager
{
public:
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

class ServerProcessor
{
public:
    ServerProcessor(GameContainerManager &gameContainerManager, PlayersManager &playersManager, OwnersManager &ownersManager)
        : gameContainerManager(gameContainerManager), playersManager(playersManager), ownersManager(ownersManager){};

    S2CDTO commandProcessor(const C2SDTO &c2sDTO)
    {
        std::string response_data = "";

        if (c2sDTO.command == "CREATE")
        {
            response_data = createPipeline(c2sDTO);
        }
        else if (c2sDTO.command == "JOIN")
        {
            response_data = joinPipeline(c2sDTO);
        }
        else if (c2sDTO.command == "INPUT")
        {
            response_data = playerInputPipeline(c2sDTO);
        }
        else
        {
            response_data = "command not recognized: " + c2sDTO.command + "\n";
        }

        S2CDTO s2cdto;
        s2cdto.data = response_data;
        return s2cdto;
    }

private:
    std::string createPipeline(const C2SDTO &c2sDTO)
    {
        int gameContainerID = gameContainerManager.createGameContainer();

        // add clientId as owner of gamecontainerid
        ownersManager.setOwnerOfGameContainer(c2sDTO.clientID, gameContainerID);

        std::string response = "create pipeline called. invite code: " + std::to_string(gameContainerID);
        return response;
    }

    std::string joinPipeline(const C2SDTO &c2sDTO)
    {
        std::string response = "join pipeline called \n";

        int clientGameCode = std::stoi(c2sDTO.data);

        // check if clientGameCode maps to gameContainerID
        bool gameContainerExists = gameContainerManager.doesGameContainerIDExist(clientGameCode);

        if (gameContainerExists)
        {
            response += "Game to Join Exists! \n";

            bool isClientAlreadyPlayer = playersManager.isClientPlayer(c2sDTO.clientID);
            if (isClientAlreadyPlayer)
            {
                response += "This client is already a player of another game! \n";
            }
            else
            {
                response += "This client can play this game \n";
                playersManager.addPlayerToGame(c2sDTO.clientID, clientGameCode);

                std::string gameContainerResponse = gameContainerManager.addPlayerToGame(c2sDTO.clientID, clientGameCode);
                response += gameContainerResponse;
            }
        }
        else
        {
            response += "Game to Join Doesn't Exists! \n";
        }

        return response;
    }

    std::string playerInputPipeline(const C2SDTO &c2sDTO)
    {
        std::string response = "player input pipeline called \n";

        bool isClientPlayer = playersManager.isClientPlayer(c2sDTO.clientID);
        if (isClientPlayer)
        {
            response += "client is player \n";

            int gameContainerIDofPlayer = playersManager.getGameContainerIDofPlayer(c2sDTO.clientID);
            std::string gameContainerResponse = gameContainerManager.giveGameContainerPlayerInput(gameContainerIDofPlayer, c2sDTO.clientID, c2sDTO.data);
            response += gameContainerResponse;
        }
        else
        {
            response += "client is not player! Error! \n";
        }

        return response;
    }

    GameContainerManager gameContainerManager;
    PlayersManager playersManager;
    OwnersManager ownersManager;
};
