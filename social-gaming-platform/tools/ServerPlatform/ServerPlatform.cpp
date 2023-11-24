#include "ServerManager.h"

int main()
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

    // inject dependencies into ServerManager
    ServerManager serverManager{port}; //, messageProcessor, serverProcessor};

    // run the server
    serverManager.startServer();
}