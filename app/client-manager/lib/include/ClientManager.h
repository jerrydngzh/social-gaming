#include "Client.h"
#include "ChatWindow.h"
#include <unordered_map>
#include "messageProcessor.h"

enum class IncomingCommandType {
    INVALID,
    NEW_CONNECTION,
    QUIT,
    MENU_SELECT,
    INPUT,
    INFO,
    GAME_END
};

enum class OutgoingCommandType {
    QUIT,
    LEAVE,
    EXIT,
    MENU_SELECT,
    JOIN,
    CREATE
};



class ClientManager {
public:
    void startClient();
    ClientManager(std::string_view ipAddress, std::string_view port);
private:
    bool isClientDone = false;
    IncomingCommandType currentCommand = IncomingCommandType::NEW_CONNECTION;

    const std::unordered_map<std::string, OutgoingCommandType> outgoingCommandMap = {
        {"QUIT", OutgoingCommandType::QUIT},
        {"LEAVE", OutgoingCommandType::LEAVE},
        {"EXIT", OutgoingCommandType::EXIT},
        {"JOIN", OutgoingCommandType::JOIN},
        {"CREATE", OutgoingCommandType::CREATE}
    };


    std::unordered_map<std::string_view, IncomingCommandType> incomingCommandMap = {
        {"QUIT", IncomingCommandType::QUIT},
        {"MENU_SELECT", IncomingCommandType::MENU_SELECT},
        {"INPUT", IncomingCommandType::INPUT},
        {"INFO", IncomingCommandType::INFO},
        {"GAME_END", IncomingCommandType::GAME_END}
    };

    ClientManager* instance = nullptr;
    std::unique_ptr<ChatWindow> chatWindow;
    std::unique_ptr<networking::Client> client;
    std::unique_ptr<MessageProcessors::ClientMessageProcessor> clientMessageProcessor;
    bool isOutgoingCommmandValid(const std::string& command);
    void textEntryHandler(const std::string& s);
    void matchCommandToIncomingCommand(std::string_view message);
    MessageProcessors::ClientRequestMessageDTO matchOutgoingCommandToRequest(std::string_view message);
};