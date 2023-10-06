#include "RockPaperScissorsGame.h"
#include <iostream>
#include <ctime>
#include <cstdlib>


RockPaperScissorsGame::RockPaperScissorsGame() {
    // Constructor (if needed)
    // You can add any initialization code here
    srand(time(0)); // Seed the random number generator with the current time
}

void RockPaperScissorsGame::play() {
    displayStartGameInfo();

    int playerChoice = getPlayerChoice();
    int computerChoice = generateComputerChoice();

    displayChoices(playerChoice, computerChoice);

    int result = determineWinner(playerChoice, computerChoice);

    displayResult(result);
}

void RockPaperScissorsGame::displayStartGameInfo() {
    std::cout << "Let's play Rock, Paper, Scissors!" << std::endl;
    std::cout << "1. Rock\n2. Paper\n3. Scissors\nEnter your choice (1-3): ";
}

int RockPaperScissorsGame::getPlayerChoice() {
    int choice;
    std::cin >> choice;
    return choice;
}

int RockPaperScissorsGame::generateComputerChoice() {
    return rand() % 3 + 1;
}

void RockPaperScissorsGame::displayChoices(int playerChoice, int computerChoice) {
    std::cout << "You chose: " << getChoiceName(playerChoice) << std::endl;
    std::cout << "Computer chose: " << getChoiceName(computerChoice) << std::endl;
}

std::string RockPaperScissorsGame::getChoiceName(int choice) {
    switch (choice) {
        case 1:
            return "Rock";
        case 2:
            return "Paper";
        case 3:
            return "Scissors";
        default:
            return "Invalid";
    }
}

int RockPaperScissorsGame::determineWinner(int playerChoice, int computerChoice) {
    if (playerChoice == computerChoice) {
        return 0; // It's a tie
    } else if ((playerChoice == 1 && computerChoice == 3) ||
               (playerChoice == 2 && computerChoice == 1) ||
               (playerChoice == 3 && computerChoice == 2)) {
        return 1; // You win
    } else {
        return -1; // Computer wins
    }
}

void RockPaperScissorsGame::displayResult(int result) {
    if (result == 0) {
        std::cout << "It's a tie!" << std::endl;
    } else if (result == 1) {
        std::cout << "You win!" << std::endl;
    } else {
        std::cout << "Computer wins!" << std::endl;
    }
}
