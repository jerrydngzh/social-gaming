#include <unordered_map>
#include <string>
#include <stdexcept>
#include <vector>
#include <tuple>


//Handles messages from clients to server
class ClientToServerMessageHandler{
private: 
    std::unordered_map<int, std::string> clients;

public:
    ClientToServerMessageHandler() {}
    
    ~ClientToServerMessageHandler(){}

    void addClient(const int clientId) {
        if(clients.find(clientId) != clients.end()) {
            throw std::invalid_argument("Invalid argument: client already added");
        } 
        std::string message = "";
        clients.insert(std::make_pair(clientId, message));
    }

    std::string getMessage(const int clientId) const{
        auto client = clients.find(clientId);
        if(client == clients.end()) {
            throw std::invalid_argument("Invalid argument: cannot get message for unknown client");
        }
        std::string clientMsg = client -> second;
        return clientMsg;
    }

    void setClientMessage(const int clientId, const std::string& message) {
        auto client = clients.find(clientId);
        if(client == clients.end()) {
            throw std::invalid_argument("Invalid argument: cannot set message for unknown client");
        }
        clients[clientId] = message;
    }

    void removeClient(const int clientId) {
        size_t elemsRemoved = clients.erase(clientId);
        if(elemsRemoved != 1) {
            throw std::invalid_argument("Invalid argument: cannot remove client that wasn't added");
        }
    }

    void setAllClientMessage(const std::string& message) {
        for(auto& client : clients) {
            client.second = message;
        }
    }

    std::vector<std::tuple<int, std::string>> getAllClientMessages() const {
        std::vector<std::tuple<int, std::string>> messages;
        for(const auto& client: clients) {
            messages.emplace_back(std::make_tuple(client.first, client.second));
        }
        return messages;
    }

    //returns the string representation of all the clients and their messaegs, equivalent to .toString()
    std::string allMessagesToString() const{
        std::string result = "";
        for(const auto& client: clients) {
            result += "Client: " + std::to_string(client.first) + ", Message: " + client.second + "\n";
        }
        return result;
    }

    std::vector<std::pair<int, std::string>> getClientSubsetMessages(const std::vector<int>& clientIds) const{
        std::vector<std::pair<int, std::string>> result;
        for(const int id: clientIds){ 
            auto client = clients.find(id);
            if(client != clients.end()) {
                result.push_back(*client);
            }
        }
        return result;
    }

    void setClientSubsetMessages(const std::vector<int>& clientIds, const std::string& message) {
        for(const int id : clientIds) {
            if(clients.find(id) != clients.end()) {
                clients[id] = message;
            }
        }
    } 

};

//Handles messges from server to client
class ServerToClientMessageHandler{
private:
std::unordered_map<int, std::string> messagesToClients;

public:

    ServerToClientMessageHandler(){}

    ~ServerToClientMessageHandler(){}

    void setClientMessage(int clientId, std::string message){
        auto client = messagesToClients.find(clientId);
        if(client == messagesToClients.end()) {
            throw std::invalid_argument("Invalid argument: cannot set message for unknown client");
        }
        messagesToClients[clientId] = message;
    }

    std::string getMessage(const int clientId) const{
        auto client = messagesToClients.find(clientId);
        if(client == messagesToClients.end()) {
            throw std::invalid_argument("Invalid argument: cannot get message for unknown client");
        }
        std::string clientMsg = client -> second;
        return clientMsg;
    }

    
};