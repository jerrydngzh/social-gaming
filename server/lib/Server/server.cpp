#include "server.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <numeric>


// int clientAddress - > clientID
Server::Server(){}

void Server::addNewClient(int clientId){
    Server::clientIDToMessageMap.insert(std::make_pair(1, ""));
}
void Server::removeClient(int clientId){
    Server::clientIDToMessageMap.insert(std::make_pair(1, ""));
}
// helper function
void Server::changeClientMessage(int clientId, std::string newMessage){
    clientIDToMessageMap[clientId] = std::string(newMessage);
}
// This will use the mailman api
std::string Server::sendMessageToClient(int clientID, std::string results){
    return results;
}

// do processing of the message recieved
// Main processor of the mailman api
// Depending on the message recieved we will call functions in the server
// This is one of the two functions that should interact with the mailman api
void Server::recieveMessageFromClient(int clientID, std::string message){
    // we need to add a message that is sent to the server upon client construction through the 
    // mailman api
    if (message == "new client"){
        this->addNewClient(clientID);
    } else if (message == "remove client"){
        this->removeClient(clientID);
    }
    this->changeClientMessage(clientID,message);
    // Further business processing of messages will be here
    // TODO: We will need to know what type of messages are there and figure out
    // which ones to send back

}

// Don't think we need this
std::string Server::concatenateAllMessages(){
    std::string message = std::accumulate(clientIDToMessageMap.begin(), clientIDToMessageMap.end(),
    std::string(""),
    [](const std::string& accumulated, const std::pair<int, std::string>& pair) {
        return accumulated + pair.second;
    }
);
    return message;
}  
    
void Server::broadcastResultsToAllClients(std::string results){
    // all the keys in the map
    for (const auto& pair: this->clientIDToMessageMap){
        int client = pair.first;        
        this->sendMessageToClient(client, results);
    }
}




