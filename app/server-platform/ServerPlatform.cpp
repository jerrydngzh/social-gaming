#include "ServerManager.h"


std::vector<network::Connection> clients;

void onConnect(network::Connection c)
{
    std::cout << "New connection found: " << c.id << "\n";
    // TODO: decide how we want to manage clients
    clients.push_back(c);
}

void onDisconnect(network::Connection c)
{
    std::cout << "Connection lost: " << c.id << "\n";
    auto eraseBegin = std::remove(std::begin(clients), std::end(clients), c);
    clients.erase(eraseBegin, std::end(clients));
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

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage:\n  " << argv[0] << " <port>\n"
                  << "  e.g. " << argv[0] << " 4002\n";
        return 1;
    }

    // initialize dependencies
    const unsigned short port = std::stoi(argv[1]);
    // GameEngine gameEngine{};
    // MessageProcessor messageProcessor{};
    // ServerProcessor serverProcessor{gameEngine};

    network::Server server{port, getHTTPMessage("index.html"), onConnect, onDisconnect};

    // inject dependencies into ServerManager
    ServerManager serverManager{port, server}; //, messageProcessor, serverProcessor};

    // run the server
    serverManager.startServer();
}