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

            // process the incoming command
            currentCommand = matchCommandToIncomingCommand(serverResponse.command);

            // display the response
            if (serverResponse.messageStatus)
            {
                chatWindow->displayText(serverResponse.messageResult);
            }
            else
            {
                chatWindow->displayText("Request failed, please try again:\n" + serverResponse.messageResult);
            }
        }

        // update the chat window with any new text
        // from server or client
        chatWindow->update();
    }
}

// =========== INCOMING ===========

// Conditional Validators for incoming commands
// This will control what kind of commands are valid for the client to enter
// to proceed to the next step
IncomingCommandType ClientManager::matchCommandToIncomingCommand(std::string_view command)
{
    if (incomingCommandMap.find(command) != incomingCommandMap.end())
    {
        return incomingCommandMap.at(command);
    }
    else
    {
        return IncomingCommandType::INVALID;
    }
}

// =========== OUTGOING ===========
bool ClientManager::isOutgoingCommmandValid(const std::string &command)
{
    if (outgoingCommandMap.find(command) != outgoingCommandMap.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}


// format of entered text: <command> <message>
void ClientManager::textEntryHandler(const std::string &s)
{
    // check if currentCommand is type input or type command
    std::string incoming = s;
    incoming.erase(std::remove(incoming.begin(), incoming.end(), '\n'), incoming.cend());
    if ("EXIT" == s || "QUIT" == s)
    {
        isClientDone = true;
    }
    else
    {
        MessageProcessors::ClientRequestMessageDTO requestDTO;
        std::string command = s.substr(0, s.find(" "));
        std::string data = s.substr(s.find(" ") + 1);
        if (this->getCurrentCommand() == IncomingCommandType::MENU_SELECT)
        {
            // expect SELECT_CREATE or SELECT_JOIN
            if (outgoingCommandMap.at(command) == OutgoingCommandType::SELECT_CREATE ||
                outgoingCommandMap.at(command) == OutgoingCommandType::SELECT_JOIN)
            {
                requestDTO = matchOutgoingCommandToRequest(s);
            }
            else
            {
                chatWindow->displayText("Invalid command, please try again.");
                return;
            }
            std::string outgoingMessage = this->clientMessageProcessor->buildOutgoingClientMessage(requestDTO);
            client->send(outgoingMessage);
            return;
        }
        else
        {
            // expect INPUT: <command> <input_data>
            MessageProcessors::ClientRequestMessageDTO requestDTO = matchOutgoingCommandToRequest(s);
            std::string outgoingMessage = this->clientMessageProcessor->buildOutgoingClientMessage(requestDTO);
            client->send(outgoingMessage);
            return;
        }
    }
}

// format of entered text: <command> <message>
MessageProcessors::ClientRequestMessageDTO ClientManager::matchOutgoingCommandToRequest(std::string_view textEntry)
{
    MessageProcessors::ClientRequestMessageDTO requestDTO;

    // populate command
    std::string_view command = textEntry.substr(0, textEntry.find(" "));
    std::string commandString = std::string(command);
    if (outgoingCommandMap.find(commandString) != outgoingCommandMap.end())
    {
        requestDTO.command = outgoingCommandMap.find(commandString)->first;
    }
    else
    {
        requestDTO.command = "INVALID";
    }

    // populate data
    std::string result = "";
    size_t firstSpacePos = textEntry.find(' ');

    if (firstSpacePos != std::string::npos)
    {
        result = textEntry.substr(firstSpacePos + 1);
    }

    requestDTO.data = result;
    return requestDTO;
}

IncomingCommandType ClientManager::getCurrentCommand()
{
    return currentCommand;
}