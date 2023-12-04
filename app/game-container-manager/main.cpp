/*
The Server Processor takes in client messages, processes them, and outputs a server message.
In this file, we demonstrate how the Server Processor would be used in the Server Platform.
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "gamesDataManager.h"
#include "serverProcessors.h"
#include "ClientToServerDataObject.h"
#include "ServerToClientsDataObject.h"

// DUMMY FUNCTION - SERVES EXAMPLE ONLY
// Dummy Function which replicates when the Server Platform gets a message from the client,
// processes it into a DTO, and returns it.
ClientToServerDataObject messageProcessorGetMessage()
{
    // Get Client ID
    std::string clientIDstring = "";
    std::cout << "Enter clientID: ";
    std::cin >> clientIDstring;
    uintptr_t clientID = std::stoi(clientIDstring);

    // Get Client Command
    std::string clientCommand = "";
    std::cout << "Enter client command: ";
    std::cin >> clientCommand;

    // Get Client Data
    std::string clientData = "";
    std::cout << "Enter client data: ";
    std::cin >> clientData;

    ClientToServerDataObject c2sDTO = {clientID, clientCommand, clientData};

    return c2sDTO;
}

// DUMMY FUNCTION - SERVES EXAMPLE ONLY
// Dummy Function which replicates when the Server Processor returns a DTO,
// It should process the DTO, sending the correct message to the correct clients.
void messageProcessorSendMessage(ServerToClientsDataObject message)
{
    std::cout << "Message to be sent to clients: ";
    for (uintptr_t clientID : message.clientIDs)
    {
        std::cout << std::to_string(clientID);
    }
    std::cout << "\n";
    std::cout << "Message Command: " << message.command << "\n";
    std::cout << "Message Data: " << message.data << "\n";
}

/*
    EXAMPLE USAGE OF SERVER PROCESSOR

    A server processor is created. The server loop is turned on, which begins to recieve
    messages from the client. These messages are turned onto some structured data,
    which is then pipelined into the serverProcessor.
    The ServerProcessor does its processing, and will return some structured data, this time with messages for clients.

    messageProcessorGetMessage() and messageProcessorSendMessage() are stub functions which are
    standins for future functions, which actually handles the websockets, and processing of raw strings to DTO's.
*/
int main()
{
    GameContainerManager gameContainerManager;
    ClientsManager clientsManager;

    CreateProcessor createProcessor(gameContainerManager, clientsManager);
    JoinProcessor joinProcessor(gameContainerManager, clientsManager);
    InputProcessor inputProcessor(gameContainerManager, clientsManager);
    InvalidCommandProcessor invalidCommandProcessor;

    while (true)
    {
        ClientToServerDataObject requestDTO = messageProcessorGetMessage();

        // Figures out what process to run depending on the Command.
        if (requestDTO.command == "CREATE")
        {
            ServerToClientsDataObject responseDTO = createProcessor.process(requestDTO);
            messageProcessorSendMessage(responseDTO);
        }
        else if (requestDTO.command == "JOIN")
        {
            ServerToClientsDataObject responseDTO = joinProcessor.process(requestDTO);
            messageProcessorSendMessage(responseDTO);
        }
        else if (requestDTO.command == "INPUT")
        {
            ServerToClientsDataObject responseDTO = inputProcessor.process(requestDTO);
            messageProcessorSendMessage(responseDTO);
        }
        else
        {
            ServerToClientsDataObject responseDTO = invalidCommandProcessor.process(requestDTO);
            messageProcessorSendMessage(responseDTO);
        }

        clientsManager.displayPlayerGameMap();
        clientsManager.displayOwnerGameMap();
    }

    return 0;
}
