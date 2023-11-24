#include "ServerManager.h"

ServerManager::ServerManager(const unsigned short port, network::Server &server)
{
    // Server server{port, getHTTPMessage("index.html"), onConnect, onDisconnect};
    // this->server = std::make_unique<Server>(server);
    // this->server = std::make_unique<Server>(port, getHTTPMessage("index.html"), onConnect, onDisconnect);
    this->server = std::move(server);
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
        const auto [log, shouldQuit] = processMessages(*(this->server), incoming);
        const auto outgoing = buildOutgoing(log);
        this->server->send(outgoing);

        if (shouldQuit || errorWhileUpdating)
        {
            break;
        }

        sleep(1);
    }
}

ServerManager::MessageResult
ServerManager::processMessages(Server &server, const std::deque<Message> &incoming)
{
    std::ostringstream result;
    for (const auto &message : incoming)
    {

        Connection target = Connection{message.connection.id};
        auto loc = std::find(clients.begin(), clients.end(), target);

        if (loc != clients.end())
        {
            // auto connection = clients[std::distance(clients.begin(), loc)];
            result << message.connection.id << ", " << message.text << "\n";
        }
        else
        {
            result << message.connection.id << ", "
                   << "connection not found"
                   << "\n";
        }
    }
    return MessageResult{result.str(), false};
}

std::deque<Message>
ServerManager::buildOutgoing(const std::string &log)
{
    std::deque<Message> outgoing;
    for (auto client : clients)
    {
        outgoing.push_back({client, log});
    }
    return outgoing;
}

