#pragma once
#include <string>
#include <vector>


// int clientAddress - > clientID

class Server {
public:
    Server();

    std::vector<std::string> recieveMessageFromAllClients(std::vector<int> clientIDs);

    std::string concatenateAllMessages(std::vector<std::string> clientMessages);
    
    void broadcastResultsToAllClients(std::string results);

private:
    std::vector<int> clientIDs; 
    std::vector<std::string> clientMessages;
    std::string concatenatedMessages;
};