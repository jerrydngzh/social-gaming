#include <unordered_map>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>

class ServerMessageHandler {
private:    
    std::unordered_map<int, std::string> messages;
    std::vector<ClientMessageHandler> clientHandlers;
public:
    ServerMessageHandler() {}

    ~ServerMessageHandler() {}

    void addHandler(const ClientMessageHandler& clientHandler) {
        if(clientHandler == nullptr)  {
            return;
        }
        clientHandlers.push_back(clientHandler);
    }

    void disconnectClientHandler(const int clientID) {
        clientHandlers.erase(std::remove_if(
            clientHandlers.begin(), 
            clientHandlers.end(), 
            [clientID] (int x) {
                return x == clientID;
            }), 
            clientHandlers.end()
        );
    }

    void broadcast(const std::string& message) {
        for(ClientMessageHandler client : clientHandlers) {
            client.receiveMessage(message);
        } 
    }

    std::string getOldestMessage() const {
        std::string result = "";

        if(messages.empty()) {
            result = "n"
        }
    }

};

class ClientMessageHandler {
private:
    std::string clientMessage;
    int serverId;
    int clientId;
    std::vector<std::string> serverMessages;
    
public:
    
    ClientMessageHandler(){}

    ~ClientMessageHandler(){}

    void receiveMessage(const std::string& message) {
        serverMessages.push_back(message);
    }

    int getClientId() {
        return clientId;
    }

    int getServerId(){
        return serverId;
    }

    void addServerHandler(const ServerMessageHandler& serverHandler){
        if(serverHandler == nullptr){
            return;
        }
    }

    void broadcastClientMessaages(const& std::str)
    
};

int main() {
    ServerMessageHandler objecta; // From Client to Server
    ClientMessageHandler objectb; // From Server to Client 
    // assume clientID is an int
    // assume messages are all non complex strings 

    // Test the objects here! 
    // objecta.set_client_message(3, "bob"); 



    return 0; 
}