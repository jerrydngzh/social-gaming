#include "Client.h"
#include "ChatWindow.h"
#include <unordered_map>
#include "messageProcessor.h"

enum class IncomingCommandType
{
    INVALID,
    NEW_CONNECTION,
    QUIT,
    MENU_SELECT,
    INPUT,
    INFO,
    GAME_END
};

enum class OutgoingCommandType
{
    QUIT,
    EXIT,
    JOIN,
    CREATE,
    USERNAME,
    SELECT_CREATE,
    SELECT_JOIN,
    INPUT
};

class ClientManager
{
public:
    void startClient();
    ClientManager(std::string_view ipAddress, std::string_view port);
    IncomingCommandType getCurrentCommand();
    bool isOutgoingCommmandValid(const std::string &command);
    void textEntryHandler(const std::string &s);
    IncomingCommandType matchCommandToIncomingCommand(std::string_view message);
    MessageProcessors::ClientRequestMessageDTO matchOutgoingCommandToRequest(std::string_view message);
private:
    bool isClientDone = false;
    IncomingCommandType currentCommand;

    const std::unordered_map<std::string, OutgoingCommandType> outgoingCommandMap = {
        {"QUIT", OutgoingCommandType::QUIT},
        {"EXIT", OutgoingCommandType::EXIT},
        {"JOIN", OutgoingCommandType::JOIN},
        {"CREATE", OutgoingCommandType::CREATE},
        {"INPUT", OutgoingCommandType::INPUT},
        {"USERNAME", OutgoingCommandType::USERNAME},
        {"SELECT_CREATE", OutgoingCommandType::SELECT_CREATE},
        {"SELECT_JOIN", OutgoingCommandType::SELECT_JOIN}
    };

    std::unordered_map<std::string_view, IncomingCommandType> incomingCommandMap = {
        {"QUIT", IncomingCommandType::QUIT},
        {"MENU_SELECT", IncomingCommandType::MENU_SELECT},
        {"INPUT", IncomingCommandType::INPUT},
        {"INFO", IncomingCommandType::INFO},
        {"GAME_END", IncomingCommandType::GAME_END},
        {"NEW_CONNECTION", IncomingCommandType::NEW_CONNECTION}
    };



    ClientManager *instance = nullptr;
    std::unique_ptr<ChatWindow> chatWindow;
    std::unique_ptr<networking::Client> client;
    std::unique_ptr<MessageProcessors::ClientMessageProcessor> clientMessageProcessor;
};