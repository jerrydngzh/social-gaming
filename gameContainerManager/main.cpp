/*
The Server Processor takes in client messages, processes them, and outputs a server message.
In this file, we demonstrate how the Server Processor would be used in the Server Platform.
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "serverProcessorDTO.h"
#include "serverProcessor.cpp"

// DUMMY FUNCTION - SERVES EXAMPLE ONLY
// Dummy Function which replicates when the Server Platform gets a message from the client,
// processes it into a DTO, and returns it.
C2SDTO messageProcessorGetMessage()
{
    // Get Client ID
    std::string clientIDstring = "";
    std::cout << "Enter clientID: ";
    std::cin >> clientIDstring;
    int clientID = std::stoi(clientIDstring);

    // Get Client Command
    std::string clientCommand = "";
    std::cout << "Enter client command: ";
    std::cin >> clientCommand;

    // Get Client Data
    std::string clientData = "";
    std::cout << "Enter client data: ";
    std::cin >> clientData;

    C2SDTO c2sDTO;
    c2sDTO.clientID = clientID;
    c2sDTO.command = clientCommand;
    c2sDTO.data = clientData;

    return c2sDTO;
}

// DUMMY FUNCTION - SERVES EXAMPLE ONLY
// Dummy Function which replicates when the Server Processor returns a DTO,
// It should process the DTO, sending the correct message to the correct clients.
void messageProcessorSendMessage(S2CDTO message)
{
    std::cout << "Message to be sent to clients: ";
    for (int clientID : message.clientIDs)
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
    PlayersManager playersManager;
    OwnersManager ownersManager;

    CreateProcessor createProcessor(gameContainerManager, ownersManager);
    JoinProcessor joinProcessor(gameContainerManager, playersManager);
    InputProcessor inputProcessor(gameContainerManager, playersManager);
    InvalidCommandProcessor invalidCommandProcessor;

    while (true)
    {
        C2SDTO requestDTO = messageProcessorGetMessage();
        S2CDTO responseDTO;

        // Figures out what process to run depending on the Command.
        if (requestDTO.command == "CREATE")
        {
            responseDTO = createProcessor.processCreateCommand(requestDTO);
        }
        else if (requestDTO.command == "JOIN")
        {
            responseDTO = joinProcessor.processJoinCommand(requestDTO);
        }
        else if (requestDTO.command == "INPUT")
        {
            responseDTO = inputProcessor.processInputCommand(requestDTO);
        }
        else
        {
            responseDTO = invalidCommandProcessor.processInvalidCommand(requestDTO);
        }

        messageProcessorSendMessage(responseDTO);
    }

    return 0;
}
