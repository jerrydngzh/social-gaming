#include "ClientManager.h"

ClientManager::ClientManager(std::string_view ipAddress, std::string_view port)
{
    this->client = std::make_unique<networking::Client>(ipAddress, port);
    this->clientMessageProcessor = std::make_unique<MessageProcessors::ClientMessageProcessor>();
    this->chatWindow = std::make_unique<ChatWindow>(
        [this](const std::string &s)
        { this->textEntryHandler(s); });
}

void ClientManager::startClient()
{

    while (!isClientDone && !client->isDisconnected())
    {
        // get from server
        try
        {
            client->update();
        }
        catch (std::exception &e)
        {
            chatWindow->displayText("Exception from Client update:");
            chatWindow->displayText(e.what());
            isClientDone = true;
        }

        // display incoming messages from server
        auto response = client->receive();
        if (!response.empty())
        {
            MessageProcessors::ClientResponseMessageDTO serverResponse = this->clientMessageProcessor->processIncomingServerMessage(response);

            // display the response
            if (serverResponse.messageStatus)
            {
                chatWindow->displayText(serverResponse.messageResult);
            }
            else
            {
                chatWindow->displayText("FAILED: " + serverResponse.messageResult);
            }

            // TODO: handle the command returned from server response
            // TODO: introduce a map for command to enum
            /*
            switch (serverResponse.command)
            {
                case "test":
                    break;
                default:
                    break;
            }
            */
        }

        // update the chat window with any new text
        // from server or client
        chatWindow->update();
    }
}

//
void ClientManager::textEntryHandler(const std::string &s)
{
    // TODO: map for commands
    if ("exit" == s || "quit" == s)
    {
        isClientDone = true;
    }
    else
    {
        // TODO: match the enum to command string
        // flow the command to the message processor
        MessageProcessors::ClientRequestMessageDTO requestDTO = matchCommandToRequest(s);
        std::string outgoingMessage = this->clientMessageProcessor->processOutgoingClientMessage(requestDTO);
        client->send(outgoingMessage);
    }
}

// TODO: 
/*
    client server interaction:
    1a. server starts up, waits for a client
    1b. client starts up
        - CLIENT_REQUEST: (Connection) immediately sends a connection to server

    2. on connection
        a. SERVER_RESPONSE: ask for a name
        b. CLIENT_REQUEST: should enter a username

    3. server recieves the client's username, bind it to the user object
        a. SERVER_RESPONSE: displays a menu screen
        b. CLIENT_REQUEST: enter something that corresponds to the message
    
    4. menu selection
        a. SERVER_RESPONSE: 
            1. CREATE:
                - return a message showing available games to select or to input own game (a file path, stub this)
            2. JOIN: ask for a game code id
        b. CLIENT_REQUEST:
            1. CREATE:
                - select the game or enter a game via file path
            2. JOIN: enter a game code id
                - server will return a message that client has joined, echo this to all other clients
    
    4b. display of main screen ??? (for owner)



    5. playing the game -- inputs
        a. SERVER_RESPONSE: game start, enter something (based on the message displayed)
        b. CLIENT_REQUEST: enter that thing
            - server will do validation on the message 
*/
MessageProcessors::ClientRequestMessageDTO matchCommandToRequest(std::string message)
{
    MessageProcessors::ClientRequestMessageDTO requestDTO;
    requestDTO.command = "test";
    requestDTO.data = message;
    return requestDTO;
}