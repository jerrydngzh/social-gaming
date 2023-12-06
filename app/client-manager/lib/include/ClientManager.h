#include "Client.h"
#include "ChatWindow.h"
#include <unordered_map>
#include "messageProcessor.h"

enum class IncomingCommandType {
    QUIT,
    MENU_SELECT,
    START,
    INPUT,
    INFO,
    GAME_END
};

enum class OutgoingCommandType {
    QUIT,
    LEAVE,
    JOIN,
    CREATE
};

class ClientManager {
public:
    void startClient();
    ClientManager(std::string_view ipAddress, std::string_view port);
private:
    bool isClientDone = false;

    std::unordered_map<std::string_view, int> incomingCommandMap = {};
    std::unordered_map<std::string_view, int> outgoingCommandMap = {};

    ClientManager* instance = nullptr;
    std::unique_ptr<ChatWindow> chatWindow;
    std::unique_ptr<networking::Client> client;
    std::unique_ptr<MessageProcessors::ClientMessageProcessor> clientMessageProcessor;

    void textEntryHandler(const std::string& s);
    MessageProcessors::ClientRequestMessageDTO matchCommandToRequest(std::string_view message);
};