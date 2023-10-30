#pragma once
#include <string>
#include <vector>
#include <unordered_map>

// int clientAddress - > clientID

class Server {
public:
    Server();

    void addNewClient(int clientId);
    void removeClient(int clientId);

    std::string sendMessageToClient(int clientID);

    void recieveMessageFromClient(int clientID, std::string message);

    std::string concatenateAllMessages();   

    // void removeClient(int clientId);
    
    void broadcastResultsToAllClients(std::string results);

private:
    void changeClientMessage(int clientId, std::string newMessage);
    std::vector<int> clientIDs; 
    std::vector<std::string> clientMessages;
    std::unordered_map<int, std::string> clientIDToMessageMap;
    std::string concatenatedMessages;
};