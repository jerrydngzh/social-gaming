#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

struct C2SDTO
{
    int clientID;
    std::string command;
    std::string data;
};

struct S2CDTO
{
    std::vector<int> clientIDs;
    std::string command;
    std::string data;
};

class GameContainerManager
{
public:
    GameContainerManager();

    int createGameContainer();

    bool doesGameContainerIDExist(int gameContainerID);

    std::string addPlayerToGame(int clientID, int gameContainerID);

    std::string giveGameContainerPlayerInput(int gameContainerID, int clientID, std::string data);

private:
    int numberOfGameContainers = 0;
    std::vector<int> gameContainerVector;
};

class ClientsManager
{
public:
    bool isClientPlayer(int clientID);

    void addPlayerToGame(int clientID, int clientGameCode);

    int getGameContainerIDofPlayer(int clientID);

    void setOwnerOfGameContainer(int clientID, int gameContainerID);

private:
    std::unordered_map<int, int> playerIDtoGameIDMap;
    std::unordered_map<int, int> ownerIDtoGameIDMap;
};

class CreateProcessor
{
public:
    CreateProcessor(GameContainerManager &gameContainerManager, ClientsManager &clientsManager);

    S2CDTO processCreateCommand(const C2SDTO &requestDTO);

private:
    GameContainerManager &gameContainerManager;
    ClientsManager &clientsManager;

    bool isCreateCommandValid(const C2SDTO &requestDTO);

    S2CDTO createGame(const C2SDTO &requestDTO);

    S2CDTO invalidCreateCommandResponder(const C2SDTO &requestDTO);
};

class JoinProcessor
{
public:
    JoinProcessor(GameContainerManager &gameContainerManager, ClientsManager &clientsManager);

    S2CDTO processJoinCommand(const C2SDTO &requestDTO);

private:
    GameContainerManager &gameContainerManager;
    ClientsManager &clientsManager;

    bool gameContainerExists(int gameContainerID);

    bool isClientAlreadyPlayer(int clientID);

    bool isJoinCommandValid(const C2SDTO &requestDTO);

    S2CDTO joinGame(const C2SDTO &requestDTO);

    S2CDTO invalidJoinCommandResponder(const C2SDTO &requestDTO);
};

class InputProcessor
{
public:
    InputProcessor(GameContainerManager &gameContainerManager, ClientsManager &clientsManager);

    S2CDTO processInputCommand(const C2SDTO &requestDTO);

private:
    GameContainerManager &gameContainerManager;
    ClientsManager &clientsManager;

    bool isClientPlayer(int clientID);

    bool isInputCommandValid(const C2SDTO &requestDTO);

    S2CDTO stubGameRoomManagerProcessor(const C2SDTO &requestDTO);

    S2CDTO invalidInputCommandResponder(const C2SDTO &requestDTO);
};

class InvalidCommandProcessor
{
public:
    S2CDTO processInvalidCommand(const C2SDTO &requestDTO);
};
