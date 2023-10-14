#include "include/user.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>

User::User(std::string_view username1, bool isPlayer1, bool isAudience1, bool isOwner1, int code1)
    : username(username1), isPlayer(isPlayer1), isAudience(isAudience1), isOwner(isOwner1), gameRoomCode(code1) {}

User::User() {
    messageForServer = createOrJoinGame();
}

bool User::getIsPlayer() {
    return isPlayer;
}

bool User::getIsAudience() {
    return isAudience;
}

bool User::getIsOwner() {
    return isAudience;
}

std::string_view User::getUserName(){
    return username;
}

std::string User::createOrJoinGame() {
    std::cout << "create or join game?: create | join : ";

    // implemented without user input validation. 

    std::string userChoice;
    std::cin >> userChoice;

    return userChoice;
}

void User::process() {
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
            // Getting User Move
            std::cin >> messageForServer;
        } else if (prefixCommand == "game_over") {
            std::cout << messageFromServer << "\n";
            // then exits program
            connectionStatus = false;
        }
    }
}

void User::getMessage(std::string message) {
    messageFromServer = message;
}

std::string User::setMessage() {
    return messageForServer;
}

std::string User::getStringPrefix(const std::string& message) {
    std::istringstream iss(message); 
    std::string prefix;
    iss >> prefix;
    return prefix;
}

void User::runGameCode() {
    std::istringstream iss(messageFromServer);
    std::string firstWord, secondWord;
    
    // Extract the first word
    iss >> firstWord;
    
    // Extract the second word
    iss >> secondWord;
    
    std::string gameCode = secondWord;

    std::cout << "The game code is " << gameCode << "\n";

    std::cout << "Join Game?: yes | no : "; 
    
    std::string userChoice; 
    std::cin >> userChoice;

    if (userChoice == "yes") {
        messageForServer = "join";
    } else {
        connectionStatus = false;
    }
}

void User::runGameInstruction() {
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

bool User::getConnectionStatus() const {
    return connectionStatus;
}