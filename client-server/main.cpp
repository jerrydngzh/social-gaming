#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>

#include "user.h"

/* Class */
class DummyServer {
public:
    DummyServer() {};

    // process should read message_from_client, and write a message_for_client accordingly.
    void process() {
        // Simulate server processing
        std::cout << "Server processing..." << std::endl;

        if (messageFromClient == "") {
            // do nothing 
        } else {
            
            if (messageFromClient == "create") {
                int gameCode = generateGameCode();
                std::string gameCodeString = std::to_string(gameCode);
                messageForClient = "game_code " + gameCodeString;
            }
            
            if (messageFromClient == "join") {
                messageForClient = "game_instruction user input rock paper or scissors.";
            }

            if (messageFromClient == "rock" || messageFromClient == "paper" || messageFromClient == "scissors") {
                messageForClient = play();
            }
        }

    }

    // reads the message in serverMailbox - from client to server. 
    void getMessage(std::string message) {
        messageFromClient = message;
    }

    // writes a message from the server into clientMailbox - from server to client. 
    std::string setMessage() {
        return messageForClient;
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
        std::string p1 = messageFromClient;
        std::string p2 = randomMove();
        std::string result = gameResult(p1, p2);
        if (result == "draw") {
            std::string serverMessage = "";
            serverMessage = "game_instruction ";
            serverMessage += "Player1 Hand: " + p1 + " | Player2 Hand: " + p2 + "\n";
            serverMessage += "Draw! Enter rock, paper, or scissors";
            return serverMessage; 
        } else {
            std::string serverMessage = "";
            serverMessage = "game_over ";
            serverMessage += "Player1 Hand: " + p1 + " | Player2 Hand: " + p2 + "\n";
            serverMessage += "Winner! " + result + "\n";
            return serverMessage;
        }
    }

    std::string messageForClient;
    std::string messageFromClient;
};


int main() {
    User client;
    DummyServer server;

    std::string clientMailbox = "";
    std::string serverMailbox = "";

    bool clientConnected = true;

    while (clientConnected) {
        server.process();
        clientMailbox = server.setMessage(); // game_instruction user input rock paper or scissors.

        client.getMessage(clientMailbox);
        client.process();

        clientConnected = client.getConnectionStatus();
        if (clientConnected == false) {
            break;
        }

        serverMailbox = client.setMessage(); // join, create
        server.getMessage(serverMailbox);
    }

    return 0;
}