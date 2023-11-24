#include "../../../networking/lib/networking/include/Server.h"

// #include "MessageProcessor.h"
// #include "ServerProcessor.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

using networking::Connection;
using networking::Message;
using networking::Server;

class ServerManager
{
public:
    ServerManager(const unsigned short port, Server &server);

    void startServer();

private:
    struct MessageResult
    {
        std::string result;
        bool shouldShutdown;
    };



    // define all services here
    std::unique_ptr<Server> server;
    // MessageProcessor messageProcessor;
    // ServerProcessor gameContainerManager;

    // TODO: migrate to MessageProcessors
    MessageResult
    processMessages(Server &server, const std::deque<Message> &incoming);

    // TODO: migrate to MessageProcessors
    std::deque<Message>
    buildOutgoing(const std::string &log);

    // std::string
    // getHTTPMessage(const char *htmlLocation);
};