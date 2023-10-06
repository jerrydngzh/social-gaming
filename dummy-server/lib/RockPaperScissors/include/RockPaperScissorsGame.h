#pragma once

#include <iostream>

class RockPaperScissorsGame {
public:
    RockPaperScissorsGame(); // Constructor
    void play();

private:
    void displayStartGameInfo();
    int getPlayerChoice();
    int generateComputerChoice();
    void displayChoices(int playerChoice, int computerChoice);
    std::string getChoiceName(int choice);
    int determineWinner(int playerChoice, int computerChoice);
    void displayResult(int result);
};
