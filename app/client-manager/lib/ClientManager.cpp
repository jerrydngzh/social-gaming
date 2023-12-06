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
                chatWindow->displayText("Request failed, please try again: " + serverResponse.messageResult);
            }

            // TODO: process incoming messages, handle the command from server
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
    if ("EXIT" == s || "QUIT" == s)
    {
        isClientDone = true;
    }
    else
    {
        // TODO: flow the logic here, matching commands
        


        MessageProcessors::ClientRequestMessageDTO requestDTO = matchCommandToRequest(s);
        std::string outgoingMessage = this->clientMessageProcessor->buildOutgoingClientMessage(requestDTO);
        client->send(outgoingMessage);
    }
}

// TODO: unit test this
// TODO: look at the pending command sent from the server, and match it against a corresponding command to be sent back out
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

    TYPES OF COMMANDS FOR CLIENT FROM SERVER:
    1. NEW_CONNECTION -> supply a username
    2. *MENU_SELECT -> contains a message expecting client to enter "1" to create or "2" join a game
        - 1 -> sends command SELECT_CREATE: server responds with more info about the creation menu
        - 2 -> sends command SELECT_JOIN: server asks for game code
    3. ?START -> if owner, starts the game
    4. *INPUT -> input something according to the messageResult/commandData from server
    5. *INFO -> just displays info, expects no commands for client 
    6. *GAME_END -> ends the game
*/
MessageProcessors::ClientRequestMessageDTO ClientManager::matchCommandToRequest(std::string_view message)
{
    MessageProcessors::ClientRequestMessageDTO requestDTO;

    // TODO: insert logic here to handle deciding which command to attach, to send out

    requestDTO.command = "test";
    requestDTO.data = message;
    return requestDTO;
}