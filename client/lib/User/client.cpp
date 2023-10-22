#include "include/client.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>

Client::Client(std::string_view Clientname1, bool isPlayer1, bool isAudience1, bool isOwner1, int code1)
    : Clientname(Clientname1), isPlayer(isPlayer1), isAudience(isAudience1), isOwner(isOwner1), gameRoomCode(code1) {}

// Not a good constructor, should have a parameter to indicate createOrJoin
// TODO: Make this better
Client::Client() {
    messageForServer = createOrJoinGame();
}

bool Client::getIsPlayer() {
    return isPlayer;
}

bool Client::getIsAudience() {
    return isAudience;
}

bool Client::getIsOwner() {
    return isOwner;
}

std::string_view Client::getClientName(){
    return Clientname;
}

std::string Client::createOrJoinGame() {
    std::cout << "create or join game?: create | join : ";

    // implemented without Client input validation. 

    std::string ClientChoice;
    std::cin >> ClientChoice;

    return ClientChoice;
}

void Client::process() {
    // Simulate client processing
    std::cout << "Client processing..." << std::endl;

    if (messageFromServer == "") {
        // do nothing
    } else {
        std::string prefixCommand = "";
        prefixCommand = getStringPrefix(messageFromServer);

        if (prefixCommand == "game_code") {
            runGameCode();
        } else if (prefixCommand == "game_instruction") {
            // print game instructions
            runGameInstruction();
            // Getting Client Move
            std::cin >> messageForServer;
        } else if (prefixCommand == "game_over") {
            std::cout << messageFromServer << "\n";
            // then exits program
            connectionStatus = false;
        }
    }
}

void Client::setMessage(std::string message) {
    messageFromServer = message;
}

std::string Client::getMessage() {
    return messageForServer;
}

std::string Client::getStringPrefix(const std::string& message) {
    std::istringstream iss(message); 
    std::string prefix;
    iss >> prefix;
    return prefix;
}

void Client::runGameCode() {
    std::istringstream iss(messageFromServer);
    std::string firstWord, secondWord;
    
    // Extract the first word
    iss >> firstWord;
    
    // Extract the second word
    iss >> secondWord;
    
    std::string gameCode = secondWord;

    std::cout << "The game code is " << gameCode << "\n";

    std::cout << "Join Game?: yes | no : "; 
    
    std::string ClientChoice; 
    std::cin >> ClientChoice;

    if (ClientChoice == "yes") {
        messageForServer = "join";
    } else {
        connectionStatus = false;
    }
}

void Client::runGameInstruction() {
    std::string gameInstruction = "";

    // Find the position of the first space
    size_t firstSpacePos = messageFromServer.find(' ');

    if (firstSpacePos != std::string::npos) {
        // Remove the first word
        gameInstruction = messageFromServer.substr(firstSpacePos + 1);
    } else {
        // Handle the case when there are no spaces in the string
        gameInstruction = "";
    }

    std::cout << gameInstruction << "\n";
}

bool Client::getConnectionStatus() const {
    return connectionStatus;
}