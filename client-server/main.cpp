#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>

#include "DummyClient.h"

/* Class */
class DummyServer {
public:
    DummyServer() {};

    // process should read message_from_client, and write a message_for_client accordingly.
    void process() {
        // Simulate server processing
        std::cout << "Server processing..." << std::endl;

        if (message_from_client == "") {
            // do nothing 
        } else {
            
            if (message_from_client == "create") {
                int game_code = generateGameCode();
                std::string game_code_string = std::to_string(game_code);
                message_for_client = "game_code " + game_code_string;
            }
            
            if (message_from_client == "join") {
                message_for_client = "game_instruction user input rock paper or scissors.";
            }

            if (message_from_client == "rock" || message_from_client == "paper" || message_from_client == "scissors") {
                message_for_client = play();
            }
        }

    }

    // reads the message in server_mailbox - from client to server. 
    void read_message(std::string message) {
        message_from_client = message;
    }

    // writes a message from the server into client_mailbox - from server to client. 
    std::string write_message() {
        return message_for_client;
    }
    
private:
    // pick a random move for the server as an "AI" opponent
    std::string randomMove() {
        int random = std::rand() % 3; 
        switch(random) {
            case 0: return "rock";
            case 1: return "paper";
            case 2: return "scissors";
        }
        // default in case random doesn't work
        return "rock";
    }

    // generates a game code
    int generateGameCode() {
        std::srand(std::time(0));
        int randomGameCode = (std::rand() % 10);
        return randomGameCode;
    }
    
    // takes the two moves, plays rps, and returns the winner 
    std::string gameResult(std::string player1Move, std::string player2Move) {
        if  (player1Move == player2Move) {
            return "draw";
        }
        if  (player1Move == "rock" && player2Move == "paper") {
            return "player2";
        }
        if  (player1Move == "paper" && player2Move == "scissors") {
            return "player2";
        }
        if  (player1Move == "scissors" && player2Move == "rock") {
            return "player2";
        }
        if  (player1Move == "paper" && player2Move == "rock") {
            return "player1";
        }
        if  (player1Move == "scissors" && player2Move == "paper") {
            return "player1";
        }
        if  (player1Move == "rock" && player2Move == "scissors") {
            return "player1";
        }
        // Handle the case when the input is invalid
        return "invalid";
    }
    
    std::string play() {
        std::string p1 = message_from_client;
        std::string p2 = randomMove();
        std::string result = gameResult(p1, p2);
        if (result == "draw") {
            std::string server_message = "";
            server_message = "game_instruction ";
            server_message += "Player1 Hand: " + p1 + " | Player2 Hand: " + p2 + "\n";
            server_message += "Draw! Enter rock, paper, or scissors";
            return server_message; 
        } else {
            std::string server_message = "";
            server_message = "game_over ";
            server_message += "Player1 Hand: " + p1 + " | Player2 Hand: " + p2 + "\n";
            server_message += "Winner! " + result + "\n";
            return server_message;
        }
    }

    std::string message_for_client;
    std::string message_from_client;
};


int main() {
    DummyClient client;
    DummyServer server;

    std::string client_mailbox = "";
    std::string server_mailbox = "";

    while (true) {
        server.process();
        client_mailbox = server.write_message(); // game_instruction user input rock paper or scissors.

        client.read_message(client_mailbox);
        client.process();

        server_mailbox = client.write_message(); // join, create
        server.read_message(server_mailbox);
    }

    return 0;
}