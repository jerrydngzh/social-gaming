#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include "DummyClient.h"

DummyClient::DummyClient() {
    bool choice = create_or_join_game();
    if (choice) {
        message_for_server = "create";
    } else {
        message_for_server = "join";
    }
}

bool DummyClient::create_or_join_game() {
    std::cout << "create or join game?: create | join : ";

    std::string user_choice;
    std::cin >> user_choice;

    if (user_choice == "create") {
        return true;
    }

    return false;
}

void DummyClient::process() {
    // Simulate client processing
    std::cout << "Client processing..." << std::endl;

    if (message_from_server == "") {
        // do nothing
    } else {
        std::string prefix_command = "";
        prefix_command = get_string_prefix(message_from_server);

        if (prefix_command == "game_code") {
            run_game_code();
        } else if (prefix_command == "game_instruction") {
            // print game instructions
            run_game_instruction();
            // Getting User Move
            std::cin >> message_for_server;
        } else if (prefix_command == "game_over") {
            std::cout << message_from_server << "\n";
            // then exits program
            exit(0);
        }
    }
}

void DummyClient::read_message(std::string message) {
    message_from_server = message;
}

std::string DummyClient::write_message() {
    return message_for_server;
}

std::string DummyClient::get_string_prefix(const std::string& message) {
    std::istringstream iss(message);
    std::string prefix;
    iss >> prefix;
    return prefix;
}

void DummyClient::run_game_code() {
    std::istringstream iss(message_from_server);
    std::string firstWord, secondWord;
    
    // Extract the first word
    iss >> firstWord;
    
    // Extract the second word
    iss >> secondWord;
    
    std::string game_code = secondWord;

    std::cout << "The game code is " << game_code << "\n";

    std::cout << "Join Game?: yes | no : "; 
    
    std::string user_choice; 
    std::cin >> user_choice;

    if (user_choice == "yes") {
        message_for_server = "join";
    } else {
        exit(0);
    }
}

void DummyClient::run_game_instruction() {
    std::string game_instruction = "";

    // Find the position of the first space
    size_t firstSpacePos = message_from_server.find(' ');

    if (firstSpacePos != std::string::npos) {
        // Remove the first word
        game_instruction = message_from_server.substr(firstSpacePos + 1);
    } else {
        // Handle the case when there are no spaces in the string
        game_instruction = "";
    }

    std::cout << game_instruction << "\n";
}
