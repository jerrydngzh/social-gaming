#include <iostream>
#include <memory>
// #include "model/lib/Game/include/game.h"
// #include "model/lib/GameRoom/include/gameroom.h"
#include "model/lib/User/include/user.h"
#include "model/lib/SocialGameFileHandler/include/socialgamefilehandler.h"
#include <fstream>

/* TODO:
    1. Main entry point UI:
        a. join game (1 flow)
            - generates an individual
            - input a game code (random string for now)
        b. create game (1 flow)
            - upload a file
            - generates a "main" display for the game
            - generates join code
*/

// dummy server functions:
void sendCodeToServer(const int inputCode)
{
    std::cout << inputCode << std::endl;
}

int requestFromServer(const std::string request)
{
    std::cout << request << std::endl;
    int newCode = 12345;
    return newCode;
}

// Prompts user to input game code and "sends" it to the server
void joinGame() {
        std::cout << "Enter the game invite code: ";
        int inputCode;
        std::cin >> inputCode;
        sendCodeToServer(inputCode);
}

int main()
{

    // User user;
    std::cout << "Hello World\n";

    // TODO: Commented code out as currently running into library not found error for user
    User newUser("Bob", true, false, true, 123);

    std::cout << "Username: " << newUser.getUserName() << std::endl;
    std::cout << "Is Player: " << newUser.getIsPlayer() << std::endl;
    std::cout << "Is Audience: " << newUser.getIsAudience() << std::endl;
    std::cout << "Is Owner: " << newUser.getIsOwner() << std::endl;

    std::cout << "Would you like to join or create a game? (type 'join' or 'create'): ";
    std::string userInput;
    std::cin >> userInput;
    if (userInput == "join")
    {
        joinGame();
    }
    else
    {
        SocialGameFileHandler gameFile;
        int newCode = requestFromServer("give me an invite code lol");
        std::cout << newCode;
    }
}
