/* TODO Code Review Interface General Notes
- Stringview vs String. This may not be correct, as Mike noted. 
*/ 

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <algorithm>

// "object" classes -- i.e. single unit of data
// TODO: C2SDTO is not a clear name
struct C2SDTO
{
    int clientID;
    std::string command;
    std::string data;
};

// TODO: S2CDTO is not a clear name, avoid abbreviations -> creates confusion
// espeically when you have multiple DTOs
struct S2CDTO
{
    std::vector<int> clientIDs;
    std::string command;
    std::string data;
};

// Andy's Note: This Game Container is a Stub for future game container. 
class GameContainer
{
public:
    GameContainer(int gameContainerID);
    int getGameContainerID() const;

private:
    int gameContainerID;
};

// "manager" classes -- i.e. manages a collection of objects
// TODO: Consider making Clients Manager a component of GameContainerManager. 
class GameContainerManager
{
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

// TODO: maybe turn this into a map of users
//       maps have O(1) lookup time, 
//       modification of particular user is O(1) as well 
//       as we just lookup and then modify the specific field we want
//
// clientId -> user object
// as we pass down the clientId from the layer above, we can just use that to lookup the user

/* TODO: Be able to provide multiple way information. 
    For example, ClientsManager should be able to answer "whats the owner of this game AND what game(s) does the player own."
    The same can be restated for players and games. 
*/

/* TODO: ClientsManager Validation and consistent State Change 
    The clientsManager should be responsible for maintaining a consistent and valid state at all times. 
    If a user attempts to violate this, their actions should be stopped. 
    For example, currently it is possible to set two owners of a game. 
*/
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


// TODO: Processor Classes should be placed in their own file. 

// "processor" classes -- i.e. processes data and returns data
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


/* The joinPipeline method has a conversion from string to int. There doesn't seem
to be any checking for validity here, possibly resulting in undefined behavior. */
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