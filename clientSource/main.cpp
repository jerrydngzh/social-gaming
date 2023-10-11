#include <iostream>
#include <memory>
// #include "game.h"
// #include "gameroom.h"
#include "model/lib/User/include/user.h"

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

int main() {

    // User user;    
    std::cout << "Hello World\n"; 

    // TODO: Commented code out as currently running into library not found error for user
    User newUser("Bob", true, false, true, 123);

    std::cout << "Username: " << newUser.getUserName() << std::endl;
    std::cout << "Is Player: " << newUser.getIsPlayer() << std::endl;
    std::cout << "Is Audience: " << newUser.getIsAudience() << std::endl;
    std::cout << "Is Owner: " << newUser.getIsOwner() << std::endl;
}


