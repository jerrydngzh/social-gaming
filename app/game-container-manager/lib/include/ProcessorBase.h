/* TODO Code Review Interface General Notes
- Stringview vs String. This may not be correct, as Mike noted.
-  Documentation could have been more informative to clarify the design and context.
- There are not enough comments and documentation to understand the decision-making
process behind this design choice. Although the design is clear, more expressive
documentation could help reviewers and developers understand the code functionality
and context better.
*/
#pragma once

#include "gameContainerManager.h"
#include "ServerToClientsDataObject.h"
#include "ClientToServerDataObject.h"


// a processor interface
// TODO: unsure if pimpl is needed / is done correctnly here
class ProcessorBase {
public:
    ServerToClientsDataObject process(const ClientToServerDataObject &requestDTO);
};

// TODO: More Comments are Needed
class CreateProcessor : public ProcessorBase {
public:
    CreateProcessor(GameContainerManager &gameContainerManager, ClientsManager &clientsManager);

    ServerToClientsDataObject process(const ClientToServerDataObject &requestDTO){
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
// TODO: More Comments are Needed
class JoinProcessor : public ProcessorBase {
public:
    JoinProcessor(GameContainerManager &gameContainerManager, ClientsManager &clientsManager);

    ServerToClientsDataObject process(const ClientToServerDataObject &requestDTO){
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

// TODO: More Comments are Needed
class InputProcessor : public ProcessorBase {
public:
    InputProcessor(GameContainerManager &gameContainerManager, ClientsManager &clientsManager);

    ServerToClientsDataObject process(const ClientToServerDataObject &requestDTO) {
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

class InvalidCommandProcessor : public ProcessorBase {
public:
    ServerToClientsDataObject process(const ClientToServerDataObject &requestDTO) {
        return invalidCommandImpl(requestDTO);
    }
private:
    ServerToClientsDataObject invalidCommandImpl(const ClientToServerDataObject &requestDTO);
};