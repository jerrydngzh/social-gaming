/* TODO Code Review Interface General Notes
- Stringview vs String. This may not be correct, as Mike noted.
-  Documentation could have been more informative to clarify the design and context.
- There are not enough comments and documentation to understand the decision-making
process behind this design choice. Although the design is clear, more expressive
documentation could help reviewers and developers understand the code functionality
and context better.
*/
#pragma once

#include "gamesDataManager.h"
#include "ServerToClientsDataObject.h"
#include "ClientToServerDataObject.h"

// TODO: unsure if pimpl is needed / is done correctnly here

/* ProcessorBase
    - What it's For:
    When a server recieves a message from the client, the message will be of some specific command type.
    Each command type requires the server to run a set of logical steps, then return some value to the client or multiple clients.
    We call the these steps a Process, and the code that manages that logic a Processor.
    ProcessorBase is an interface for Processors. All processors should derive from it.
    - How to Use:
    When a new type of command is introduced, its logic should be encapsulated in a
    class that derives from ProcessorBase. It should then implement the processor method.
*/
class ProcessorBase
{
public:
    ServerToClientsDataObject process(const ClientToServerDataObject &requestDTO);
};

/* CreateProcessor
    - What it's For:
    Handles the logic for when a Client wishes to start a game. E.G. Create RockPaperScissors Game.
    - How to Use:
    Provide a command=CREATE ClientToServerDataObject to the process method.
*/
class CreateProcessor : public ProcessorBase
{
public:
    CreateProcessor(GameContainerManager &gameContainerManager, ClientsManager &clientsManager);

    ServerToClientsDataObject process(const ClientToServerDataObject &requestDTO)
    {
        return createProcessImpl(requestDTO);
    }

private:
    GameContainerManager &gameContainerManager;
    ClientsManager &clientsManager;

    ServerToClientsDataObject createProcessImpl(const ClientToServerDataObject &requestDTO);

    bool isCreateCommandValid(const ClientToServerDataObject &requestDTO);

    ServerToClientsDataObject createGame(const ClientToServerDataObject &requestDTO);

    ServerToClientsDataObject invalidCreateCommandResponder(const ClientToServerDataObject &requestDTO);
};

/* TODO: The joinPipeline method has a conversion from string to int. There doesn't seem
to be any checking for validity here, possibly resulting in undefined behavior. */

/* JoinProcessor
    - What it's For:
    Handles the logic for when a Client wishes to join a game. E.G. Join GameRoom 3.
    - How to Use:
    Provide a command=JOIN ClientToServerDataObject to the process method.
*/
class JoinProcessor : public ProcessorBase
{
public:
    JoinProcessor(GameContainerManager &gameContainerManager, ClientsManager &clientsManager);

    ServerToClientsDataObject process(const ClientToServerDataObject &requestDTO)
    {
        return joinProcessImpl(requestDTO);
    }

private:
    GameContainerManager &gameContainerManager;
    ClientsManager &clientsManager;

    ServerToClientsDataObject joinProcessImpl(const ClientToServerDataObject &requestDTO);

    bool gameContainerExists(int gameContainerID);

    bool isClientAlreadyPlayer(int clientID);

    bool isJoinCommandValid(const ClientToServerDataObject &requestDTO);

    ServerToClientsDataObject joinGame(const ClientToServerDataObject &requestDTO);

    ServerToClientsDataObject invalidJoinCommandResponder(const ClientToServerDataObject &requestDTO);
};

/* InputProcessor
    - What it's For:
    Handles the logic for when a Client sends game inputs. E.G. "Rock" in RockPaperScissors Game.
    - How to Use:
    Provide a command=INPUT ClientToServerDataObject to the process method.
*/
class InputProcessor : public ProcessorBase
{
public:
    InputProcessor(GameContainerManager &gameContainerManager, ClientsManager &clientsManager);

    ServerToClientsDataObject process(const ClientToServerDataObject &requestDTO)
    {
        return inputProcessImpl(requestDTO);
    }

private:
    GameContainerManager &gameContainerManager;
    ClientsManager &clientsManager;

    ServerToClientsDataObject inputProcessImpl(const ClientToServerDataObject &requestDTO);

    bool isClientPlayer(int clientID);

    bool isInputCommandValid(const ClientToServerDataObject &requestDTO);

    ServerToClientsDataObject stubGameRoomManagerProcessor(const ClientToServerDataObject &requestDTO);

    ServerToClientsDataObject invalidInputCommandResponder(const ClientToServerDataObject &requestDTO);
};

/* InvalidCommandProcessor
    - What it's For:
    Handles the case when a client messages command is not a recognized command by the server
    - How to Use:
    Call InvalidCommandProcessor's process method on DataObjects with unrecognized commands.
    Ex.
    if (serverCommands.find(command) == notFound),
        ServerToClientsDataObject responseDataObject = invalidCommandProcessor.process(requestDataObject);
*/
class InvalidCommandProcessor : public ProcessorBase
{
public:
    ServerToClientsDataObject process(const ClientToServerDataObject &requestDTO)
    {
        return invalidCommandImpl(requestDTO);
    }

private:
    ServerToClientsDataObject invalidCommandImpl(const ClientToServerDataObject &requestDTO);
};