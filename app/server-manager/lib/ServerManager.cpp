#include "ServerManager.h"

ServerManager::ServerManager(const unsigned short port)
{
    // TODO: this is probably broken, someone plz help fix, idk what to do - jerry
    // this->server = std::make_unique<Server>(port, getHTTPMessage("index.html"), this->onConnect, this->onDisconnect);
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

void onConnect(networking::Connection c)
{
    std::cout << "New connection found: " << c.id << "\n";
    // TODO: decide how we want to manage clients
    // clients.push_back(c);
}

void onDisconnect(networking::Connection c)
{
    std::cout << "Connection lost: " << c.id << "\n";
    // auto eraseBegin = std::remove(std::begin(clients), std::end(clients), c);
    // clients.erase(eraseBegin, std::end(clients));
}

std::string
getHTTPMessage(const char *htmlLocation)
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

