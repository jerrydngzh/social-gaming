#include "ServerManager.h"

const char* htmlLoc = "./app/server-platform/index.html";
const std::string DISCONNECT = "DISCONNECT";

ServerManager::ServerManager(const unsigned short port)
{
    this->server = std::make_unique<Server>(port, getHTTPMessage(htmlLoc),
                    [this](networking::Connection c) { this->onConnect(c); },
                    [this](networking::Connection c) { this->onDisconnect(c); });

    this->messageProcessors = std::make_unique<MessageProcessors::MessageProcessor>();
}

void ServerManager::startServer()
{
    while (true)
    {
        bool errorWhileUpdating = false;
        try
        {
            this->server->update();
        }
        catch (std::exception &e)
        {
            std::cerr << "Exception from Server update:\n"
                      << " " << e.what() << "\n\n";
            errorWhileUpdating = true;
        }
        const auto incoming = this->server->receive();
        
        const auto incomingMessages = processMessages(incoming);

        // NOTE: single execution of requests
        for (const auto &request : incomingMessages)
        {
            // const auto messageResult = this->serverProcessor->execute(incomingMessages);
            // const auto outgoing = buildOutgoing(messageResult); 
            // this->server->send(outgoing);
        }

        // NOTE: or batch execution of requests
        // const auto messageResult = this->serverProcessor->execute(incomingMessages);
        // const auto outgoing = buildOutgoing(incomingMessages);
        // this->server->send(outgoing);

        if (errorWhileUpdating)
        {
            break;
        }
    }
}

void ServerManager::onConnect(networking::Connection c)
{
    std::cout << "New connection found: " << c.id << "\n";
    clients.push_back(c);
}

void ServerManager::onDisconnect(networking::Connection c)
{
    std::cout << "Connection lost: " << c.id << "\n";
    auto eraseBegin = std::remove(std::begin(clients), std::end(clients), c);
    clients.erase(eraseBegin, std::end(clients));
}

std::string
ServerManager::getHTTPMessage(const char *htmlLocation)
{
    if (access(htmlLocation, R_OK) != -1)
    {
        std::ifstream infile{htmlLocation};
        return std::string{std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>()};
    }
    std::cerr << "Unable to open HTML index file:\n"
              << htmlLocation << "\n";
    std::exit(-1);
}

std::deque<MessageProcessors::RequestMessageDTO>
ServerManager::processMessages(const std::deque<Message> &incoming)
{
    std::deque<MessageProcessors::RequestMessageDTO> requests;
    for (const auto &message : incoming)
    {
        Connection target{message.connection.id};
        auto loc = std::find(clients.begin(), clients.end(), target);

        if (loc != clients.end())
        {
            Connection connection = clients[std::distance(clients.begin(), loc)];
            std::cout << "Message from " << connection.id << ": " << message.text << "\n";

            MessageProcessors::RequestMessageDTO request = messageProcessors->processIncomingMessage(message.text);

            if (request.command == DISCONNECT)
            {
                this->server->disconnect(connection);
            }
            else
            {
                request.clientId = connection.id;
                requests.push_back(request);
            }
        }
        else
        {
            std::cout << "Connection: " 
                    << message.connection.id 
                    << " not found!\n";
            requests.push_back(MessageProcessors::RequestMessageDTO{message.connection.id, "Connection not found!"});
        }
    }
    return requests;
}

// TODO: modify to use MessageProcessors
std::deque<Message>
ServerManager::buildOutgoing(const std::deque<MessageProcessors::ResponseMessageDTO>& responses)
{
    std::deque<Message> outgoing;
    for (const auto &response : responses)
    {
        Connection target{response.clientId};
        auto loc = std::find(clients.begin(), clients.end(), target);

        if (loc != clients.end())
        {
            Connection connection = clients[std::distance(clients.begin(), loc)];
            auto message = messageProcessors->processOutgoingMessage(response);
            outgoing.push_back({connection, message});
        }
        else
        {
            std::cout << "Connection: " 
                    << response.clientId 
                    << " not found!\n";
        }
    }
    return outgoing;
}
