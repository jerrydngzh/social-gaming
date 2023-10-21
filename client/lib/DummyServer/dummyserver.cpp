#include "include/dummyserver.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <ctime>

std::string enumToString(RPS rockPaperScissors) {
    switch (rockPaperScissors)
    {
    case ROCK:
        return "Rock";
    case PAPER:
        return "Paper";
    case SCISSORS:
        return "Scissors";
    }
    return "Rock";
}

DummyServer::DummyServer(){};

void DummyServer::process()
{
    // Simulate server processing
    std::cout << "Server processing..." << std::endl;

    if (messageFromClient == "")
    {
        // do nothing
    }
    else
    {
        std::string copyMessageFromClient = messageFromClient;
        std::istringstream iss(copyMessageFromClient);
        std::string firstLine;
        std::getline(iss, firstLine);

        std::cout << "First line: " << firstLine << std::endl;

        firstLine.erase(std::remove_if(firstLine.begin(), firstLine.end(), ::isspace), firstLine.end());
        if (firstLine == "create") {
            std::cout << "test worked \n";

            // Find the position of the first newline character
            size_t pos = copyMessageFromClient.find('\n');
            if (pos != std::string::npos) {
                // Remove the first line
                copyMessageFromClient.erase(0, pos + 1); // +1 to also remove the newline character
            } else {
                // Handle the case where there is no newline character
                copyMessageFromClient.clear();
            }

            std::cout << copyMessageFromClient << "\n";

            int gameCode = generateGameCode();
            std::string gameCodeString = std::to_string(gameCode);
            messageForClient = "game_code " + gameCodeString;
        }

        if (messageFromClient == "create")
        {
            int gameCode = generateGameCode();
            std::string gameCodeString = std::to_string(gameCode);
            messageForClient = "game_code " + gameCodeString;
        }

        if (messageFromClient == "join")
        {
            messageForClient = "game_instruction user input rock paper or scissors.";
        }

        if (messageFromClient == "rock" || messageFromClient == "paper" || messageFromClient == "scissors")
        {
            messageForClient = play();
        }
    }
}

// reads the message in serverMailbox - from client to server.
void DummyServer::getMessage(std::string message)
{
    messageFromClient = message;
}

// writes a message from the server into clientMailbox - from server to client.
std::string DummyServer::setMessage()
{
    return messageForClient;
}

// PRIVATE METHODS

// pick a random move for the server as an "AI" opponent
RPS DummyServer::randomMove()
{
    int random = std::rand() % 3;
    switch (random)
    {
    case 0:
        return ROCK;
    case 1:
        return PAPER;
    case 2:
        return SCISSORS;
    }
    // default in case random doesn't work
    return ROCK;
}

// generates a game code
int DummyServer::generateGameCode()
{
    std::srand(std::time(0));
    int randomGameCode = (std::rand() % 10);
    return randomGameCode;
}

// takes the two moves, plays rps, and returns the winner
std::string DummyServer::gameResult(std::string player1Move, RPS player2Move)
{
    if (player1Move == enumToString(player2Move))
    {
        return "draw";
    }
    if (player1Move == "rock" && player2Move == PAPER)
    {
        return "player2";
    }
    if (player1Move == "paper" && player2Move == SCISSORS)
    {
        return "player2";
    }
    if (player1Move == "scissors" && player2Move == ROCK)
    {
        return "player2";
    }
    if (player1Move == "paper" && player2Move == ROCK)
    {
        return "player1";
    }
    if (player1Move == "scissors" && player2Move == PAPER)
    {
        return "player1";
    }
    if (player1Move == "rock" && player2Move == SCISSORS)
    {
        return "player1";
    }
    // Handle the case when the input is invalid
    return "invalid";
}

std::string DummyServer::play()
{
    std::string clientPlayer = messageFromClient;
    RPS aiPlayer = randomMove();
    std::string result = gameResult(clientPlayer, aiPlayer);
    if (result == "draw")
    {
        std::string serverMessage = "";
        serverMessage = "game_instruction ";
        serverMessage += "Player1 Hand: " + clientPlayer + " | Player2 Hand: " + enumToString(aiPlayer) + "\n";
        serverMessage += "Draw! Enter rock, paper, or scissors";
        return serverMessage;
    }
    else
    {
        std::string serverMessage = "";
        serverMessage = "game_over ";
        serverMessage += "Player1 Hand: " + clientPlayer + " | Player2 Hand: " + enumToString(aiPlayer) + "\n";
        serverMessage += "Winner! " + result + "\n";
        return serverMessage;
    }
}