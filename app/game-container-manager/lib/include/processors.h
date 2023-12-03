#pragma once


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