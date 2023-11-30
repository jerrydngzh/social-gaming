#include "Server.h"

#include "messageProcessor.h"
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
    ServerManager(const unsigned short port);

    void startServer();

private:
    struct MessageResult
    {
        std::string result;
        bool shouldShutdown;
    };

    std::vector<Connection> clients;

    // define all services here
    std::unique_ptr<Server> server;
    std::unique_ptr<MessageProcessors::MessageProcessor> messageProcessors;
    // MessageProcessor messageProcessor;
    // ServerProcessor gameContainerManager;

    std::deque<MessageProcessors::RequestMessageDTO>
    processMessages(const std::deque<Message> &incoming);

    // TODO: migrate to MessageProcessors
    std::deque<Message>
    buildOutgoing(const std::deque<MessageProcessors::ResponseMessageDTO> &messageResults);

    void onConnect(networking::Connection c);
    void onDisconnect(networking::Connection c);

    std::string
    getHTTPMessage(const char *htmlLocation);

};