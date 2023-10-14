#include "dummyserver.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <ctime>

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
std::string DummyServer::randomMove()
{
    int random = std::rand() % 3;
    switch (random)
    {
    case 0:
        return "rock";
    case 1:
        return "paper";
    case 2:
        return "scissors";
    }
    // default in case random doesn't work
    return "rock";
}

// generates a game code
int DummyServer::generateGameCode()
{
    std::srand(std::time(0));
    int randomGameCode = (std::rand() % 10);
    return randomGameCode;
}

// takes the two moves, plays rps, and returns the winner
std::string DummyServer::gameResult(std::string player1Move, std::string player2Move)
{
    if (player1Move == player2Move)
    {
        return "draw";
    }
    if (player1Move == "rock" && player2Move == "paper")
    {
        return "player2";
    }
    if (player1Move == "paper" && player2Move == "scissors")
    {
        return "player2";
    }
    if (player1Move == "scissors" && player2Move == "rock")
    {
        return "player2";
    }
    if (player1Move == "paper" && player2Move == "rock")
    {
        return "player1";
    }
    if (player1Move == "scissors" && player2Move == "paper")
    {
        return "player1";
    }
    if (player1Move == "rock" && player2Move == "scissors")
    {
        return "player1";
    }
    // Handle the case when the input is invalid
    return "invalid";
}

std::string DummyServer::play()
{
    std::string p1 = messageFromClient;
    std::string p2 = randomMove();
    std::string result = gameResult(p1, p2);
    if (result == "draw")
    {
        std::string serverMessage = "";
        serverMessage = "game_instruction ";
        serverMessage += "Player1 Hand: " + p1 + " | Player2 Hand: " + p2 + "\n";
        serverMessage += "Draw! Enter rock, paper, or scissors";
        return serverMessage;
    }
    else
    {
        std::string serverMessage = "";
        serverMessage = "game_over ";
        serverMessage += "Player1 Hand: " + p1 + " | Player2 Hand: " + p2 + "\n";
        serverMessage += "Winner! " + result + "\n";
        return serverMessage;
    }
}