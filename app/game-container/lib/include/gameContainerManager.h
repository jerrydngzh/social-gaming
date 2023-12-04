#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <algorithm>

struct ClientsToServerDataObject {
    int clientID;
    std::string command;
    std::string data;
};

struct ServerToClientsDataObject {
    std::vector<int> clientIDs;
    std::string command;
    std::string data;
};

class GameContainer {
public:
    GameContainer(int gameContainerID);

    int getGameContainerID() const;

private:
    int gameContainerID;

};

class GameContainerManager {
public:
    GameContainerManager();

    int createGameContainer();

    bool doesGameContainerIDExist(int gameContainerID);

    std::string addPlayerToGame(int clientID, int gameContainerID);

    std::string giveGameContainerPlayerInput(int gameContainerID, int clientID, std::string data);

    // GameContainer getGameContainer(int gameContainerID);

private:
    int numberOfGameContainers = 0;
    std::vector<std::unique_ptr<GameContainer>> gameContainerVector;
    // std::vector<int> gameContainerVector;
    std::unordered_map<int, GameContainer *> gameContainerMap;
};

class ClientsManager {
public:
    bool isClientAlreadyPlayer(int clientID);

    void addPlayerToGame(int clientID, int clientGameCode);

    int getGameContainerIDofPlayer(int clientID);

    void setOwnerOfGameContainer(int clientID, int gameContainerID);

private:
    std::unordered_map<int, int> playerIDtoGameIDMap;
    std::unordered_map<int, int> ownerIDtoGameIDMap;
};

class CreateProcessor {
public:
    CreateProcessor(GameContainerManager &gameContainerManager, ClientsManager &clientsManager);

    ServerToClientsDataObject processCreateCommand(const ClientsToServerDataObject &requestDTO);

private:
    GameContainerManager &gameContainerManager;
    ClientsManager &clientsManager;

    bool isCreateCommandValid(const ClientsToServerDataObject &ClientToServerDataObject);

    ServerToClientsDataObject createGame(const ClientsToServerDataObject &requestDTO);

    ServerToClientsDataObject invalidCreateCommandResponder(const ClientsToServerDataObject &requestDTO);
};

class JoinProcessor {
public:
    JoinProcessor(GameContainerManager &gameContainerManager, ClientsManager &clientsManager);

    ServerToClientsDataObject processJoinCommand(const ClientsToServerDataObject &requestDTO);

private:
    GameContainerManager &gameContainerManager;
    ClientsManager &clientsManager;

    bool gameContainerExists(int gameContainerID);

    bool isClientAlreadyPlayer(int clientID);

    bool isJoinCommandValid(const ClientsToServerDataObject &requestDTO);

    ServerToClientsDataObject joinGame(const ClientsToServerDataObject &requestDTO);

    ServerToClientsDataObject invalidJoinCommandResponder(const ClientsToServerDataObject &requestDTO);
};

class InputProcessor {
public:
    InputProcessor(GameContainerManager &gameContainerManager, ClientsManager &clientsManager);

    ServerToClientsDataObject processInputCommand(const ClientsToServerDataObject &requestDTO);

private:
    GameContainerManager &gameContainerManager;
    ClientsManager &clientsManager;

    bool isClientPlayer(int clientID);

    bool isInputCommandValid(const ClientsToServerDataObject &requestDTO);

    ServerToClientsDataObject stubGameRoomManagerProcessor(const ClientsToServerDataObject &requestDTO);

    ServerToClientsDataObject invalidInputCommandResponder(const ClientsToServerDataObject &requestDTO);
};

class InvalidCommandProcessor {
public:
    ServerToClientsDataObject processInvalidCommand(const ClientsToServerDataObject &requestDTO);
};
