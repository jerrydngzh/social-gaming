#include "Server.h"

#include "messageProcessor.h"
#include "gameContainerManager.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

using networking::Connection;
using networking::Message;
using networking::Server;
using namespace ServerProcessor;

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

    // ===================== SERVICES =====================
    std::unique_ptr<Server> server;
    std::unique_ptr<MessageProcessors::MessageProcessor> messageProcessors;

    // Server Processor Services 
    std::unique_ptr<GameContainer> stubGameContainer;
    std::unique_ptr<GameContainerManager> gameContainerManager;
    std::unique_ptr<ClientsManager> clientsManager;
    std::unique_ptr<CreateProcessor> createProcessor;
    std::unique_ptr<JoinProcessor> joinProcessor;
    std::unique_ptr<InputProcessor> inputProcessor;
    std::unique_ptr<InvalidCommandProcessor> invalidCommandProcessor;


    // ===================== METHODS =====================
    std::deque<MessageProcessors::RequestMessageDTO>
    processMessages(const std::deque<Message> &incoming);

    std::deque<Message>
    buildOutgoing(const std::deque<MessageProcessors::ResponseMessageDTO> &messageResults);

    void onConnect(networking::Connection c);
    void onDisconnect(networking::Connection c);

    std::string
    getHTTPMessage(const char *htmlLocation);

    // DTO Adaptors
    ServerProcessor::C2SDTO messageDTOToServerProcessorDTO(const MessageProcessors::RequestMessageDTO &message);
    std::deque<MessageProcessors::ResponseMessageDTO> serverProcessorDTOToMessageDTO(const ServerProcessor::S2CDTO &message); 
};