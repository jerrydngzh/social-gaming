#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "server.h"



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

std::string Server::requestMessageFromClient(int clientID){
   
}

// do processing of the message recieved
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


std::string concatenateAllMessages(){


}  
    
void broadcastResultsToAllClients(std::string results){
    
}




