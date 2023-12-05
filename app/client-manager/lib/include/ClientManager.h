#include "Client.h"
#include "ChatWindow.h"
#include "messageProcessor.h"

class ClientManager {
public:
    
    void startClient();
    ClientManager(std::string_view ipAddress, std::string_view port);
private:
    bool isClientDone = false;

    ClientManager* instance = nullptr;
    std::unique_ptr<ChatWindow> chatWindow;
    std::unique_ptr<networking::Client> client;
    std::unique_ptr<MessageProcessors::MessageProcessor> clientMessageProcessor;

    void textEntryHandler(const std::string& s);

};