#include "Server.h"

#include "messageProcessor.h"
#include "serverProcessors.h"
#include "gamesDataManager.h"
#include "ServerToClientsDataObject.h"
#include "ClientToServerDataObject.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

using networking::Connection;
using networking::Message;
using networking::Server;

enum class Command
{
    CREATE,
    JOIN,
    INPUT,
    INVALID,
    DISCONNECT,
    NEW_CONNECTION,
    USERNAME,
    MENU_SELECT,
    SELECT_CREATE,
    SELECT_JOIN,
    INFO,
    GAME_END,
};

class ServerManager
{
public:
    ServerManager(const unsigned short port);

    void startServer();

private:
    // ===================== DATA =====================
    struct MessageResult
    {
        std::string result;
        bool shouldShutdown;
    };

    std::vector<Connection> clients;

    std::unordered_map<std::string, Command> InputCommandMap{
        {"CREATE", Command::CREATE},
        {"JOIN", Command::JOIN},
        {"INPUT", Command::INPUT},
        {"DISCONNECT", Command::DISCONNECT},
        {"NEW_CONNECTION", Command::NEW_CONNECTION},
        {"INVALID", Command::INVALID},
        {"USERNAME", Command::USERNAME}};

    std::unordered_map<Command, std::string> OutputCommandMap{
        {Command::CREATE, "CREATE"},
        {Command::JOIN, "JOIN"},
        {Command::INPUT, "INPUT"},
        {Command::INVALID, "INVALID"},
        {Command::DISCONNECT, "DISCONNECT"},
        {Command::NEW_CONNECTION, "NEW_CONNECTION"}};

    // ===================== SERVICES =====================
    std::unique_ptr<Server> server;
    std::unique_ptr<MessageProcessors::MessageProcessor> messageProcessors;

    // Server Processor Services
    GameContainerManager gameContainerManager;
    ClientsManager clientsManager;
    CreateProcessor createProcessor;
    JoinProcessor joinProcessor;
    InputProcessor inputProcessor;
    InvalidCommandProcessor invalidCommandProcessor;

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
    ClientToServerDataObject messageDTOToServerProcessorDTO(const MessageProcessors::RequestMessageDTO &message);
    std::deque<MessageProcessors::ResponseMessageDTO> serverProcessorDTOToMessageDTO(const ServerToClientsDataObject &message);
};