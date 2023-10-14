#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include "DummyClient.h"

DummyClient::DummyClient() {
    messageForServer = createOrJoinGame();
}

std::string DummyClient::createOrJoinGame() {
    std::cout << "create or join game?: create | join : ";

    // implemented without user input validation. 

    std::string userChoice;
    std::cin >> userChoice;

    return userChoice;
}

void DummyClient::process() {
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

void DummyClient::getMessage(std::string message) {
    messageFromServer = message;
}

std::string DummyClient::setMessage() {
    return messageForServer;
}

std::string DummyClient::getStringPrefix(const std::string& message) {
    std::istringstream iss(message); 
    std::string prefix;
    iss >> prefix;
    return prefix;
}

void DummyClient::runGameCode() {
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

void DummyClient::runGameInstruction() {
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

bool DummyClient::getConnectionStatus() const {
    return connectionStatus;
}