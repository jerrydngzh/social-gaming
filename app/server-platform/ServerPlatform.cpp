#include "ServerManager.h"


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage:\n  " << argv[0] << " <port>\n"
                  << "  e.g. " << argv[0] << " 4002\n";
        return 1;
    }

    // TODO: initialize dependencies
    const unsigned short port = std::stoi(argv[1]);
    // GameEngine gameEngine{};
    // MessageProcessor messageProcessor{};
    // ServerProcessor serverProcessor{gameEngine};

    // TODO: inject dependencies into ServerManager
    ServerManager serverManager{port}; //, messageProcessor, serverProcessor};

    // run the server
    serverManager.startServer();
}