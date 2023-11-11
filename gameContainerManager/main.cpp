/* 
The Server Processor takes in client messages, processes them, and outputs a server message. 
In this file, we demonstrate how the Server Processor would be used in the Server Platform. 
*/ 

#include <iostream>
#include <string>
#include <vector>

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
    ServerProcessor serverProcessor(gameContainerManager, playersManager, ownersManager);

    while (true)
    {
        C2SDTO c2sDTO = messageProcessorGetMessage();

        S2CDTO s2cDTO = serverProcessor.commandProcessor(c2sDTO);

        messageProcessorSendMessage(s2cDTO);
    }

    return 0;
}
