#include <unordered_map>
#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <tuple>

#include "include/MessageHandler.h"

//Handles messages from clients to server
ClientToServerMessageHandler::ClientToServerMessageHandler() {}
    
ClientToServerMessageHandler::~ClientToServerMessageHandler(){}

void ClientToServerMessageHandler::addClient(const int clientId) {
    if(clients.find(clientId) != clients.end()) {
        throw std::invalid_argument("Invalid argument: client already added");
    } 
    std::string message = "";
    clients.insert(std::make_pair(clientId, message));
}

std::string ClientToServerMessageHandler::getMessage(const int clientId) {
    auto client = clients.find(clientId);
    if(client == clients.end()) {
        throw std::invalid_argument("Invalid argument: cannot get message for unknown client");
    }
    std::string clientMsg = client -> second;
    return clientMsg;
}

void ClientToServerMessageHandler::setClientMessage(const int clientId, std::string& message) {
    auto client = clients.find(clientId);
    if(client == clients.end()) {
        throw std::invalid_argument("Invalid argument: cannot set message for unknown client");
    }
    clients[clientId] = message;
}

void ClientToServerMessageHandler::removeClient(const int clientId) {
    size_t elemsRemoved = clients.erase(clientId);
    if(elemsRemoved != 1) {
        throw std::invalid_argument("Invalid argument: cannot remove client that wasn't added");
    }
}

void ClientToServerMessageHandler::setAllClientMessage(const std::string& message) {
    for(auto& client : clients) {
        client.second = message;
    }
}

std::vector<std::tuple<int, std::string>> ClientToServerMessageHandler::getAllClientMessages() const {
    std::vector<std::tuple<int, std::string>> messages;
    for(const auto& client: clients) {
        messages.emplace_back(std::make_tuple(client.first, client.second));
    }
    return messages;
}

//returns the string representation of all the clients and their messaegs, equivalent to .toString()
std::string ClientToServerMessageHandler::allMessagesToString() const{
    std::string result = "";
    for(const auto& client: clients) {
        result += "Client: " + std::to_string(client.first) + ", Message: " + client.second + "\n";
    }
    return result;
}

std::vector<std::pair<int, std::string>> ClientToServerMessageHandler::getClientSubsetMessages(const std::vector<int>& clientIds) const{
    std::vector<std::pair<int, std::string>> result;
    for(const int id: clientIds){ 
        auto client = clients.find(id);
        if(client != clients.end()) {
            result.push_back(*client);
        }
    }
    return result;
}

void ClientToServerMessageHandler::setClientSubsetMessages(const std::vector<int>& clientIds, const std::string& message) {
    for(const int id : clientIds) {
        if(clients.find(id) != clients.end()) {
            clients[id] = message;
        }
    }
} 

ServerToClientMessageHandler::ServerToClientMessageHandler(){}

ServerToClientMessageHandler::~ServerToClientMessageHandler(){}

void ServerToClientMessageHandler::setClientMessage(const int clientId, std::string& message) {
    auto client = messagesToClients.find(clientId);
    if(client == messagesToClients.end()) {
        throw std::invalid_argument("Invalid argument: cannot set message for unknown client");
    }
    messagesToClients[clientId] = message;
}

std::string ServerToClientMessageHandler::getMessage(const int clientId) {
    auto client = messagesToClients.find(clientId);
    if(client == messagesToClients.end()) {
        throw std::invalid_argument("Invalid argument: cannot get message for unknown client");
    }
    std::string clientMsg = client -> second;
    return clientMsg;
}

int main() {
    ServerToClientMessageHandler serverToClientMessageHandler;
    ClientToServerMessageHandler clientToServerMessageHandler;
    clientToServerMessageHandler.addClient(2);
    std::string test = "hello";
    clientToServerMessageHandler.setClientMessage(2, test);
    std::cout <<  clientToServerMessageHandler.getMessage(2) << std::endl;
    return 0;
}
