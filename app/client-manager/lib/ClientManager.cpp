#include "ClientManager.h"

ClientManager::ClientManager(std::string_view ipAddress, std::string_view port)
{
    this->client = std::make_unique<networking::Client>(ipAddress, port);
    this->clientMessageProcessor = std::make_unique<MessageProcessors::MessageProcessor>();
    this->chatWindow = std::make_unique<ChatWindow>(
        [this](const std::string &s)
        { this->textEntryHandler(s); });
}

void ClientManager::startClient()
{

    while (!isClientDone && !client->isDisconnected())
    {
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
            // TODO: handle the response
            chatWindow->displayText(response);
        }

        // update the chat window with any new text
        // from server or client
        chatWindow->update();
    }
}

// 
void ClientManager::textEntryHandler(const std::string& s)
{
    // TODO: or map for commands
    if ("exit" == s || "quit" == s)
    {
        isClientDone = true;
    }
    
    else
    {
        // TODO: process the text
        client->send(s);
    }
}