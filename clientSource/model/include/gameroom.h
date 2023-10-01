#include <string_view>
#include "user.h"

/*
Contains all the information regarding players and pre-game setup
*/
class GameRoom{
public: 
private:
    const std::string_view gameCode;

    // A GameRoom has-a Game (composition)
    std::unique_ptr<GameRoom> game;

    // this is how a unique point can be definded
    // std::unique_ptr<MyClass> myPtr = std::make_unique<MyClass>(42);
    // TODO: improve on value type (instead of void*)
    std::unorded_map<std::string_view, std::unique_ptr<void*>> variables;

    // User has fields to determine if is player, audience, or owner
    // maybe explore better way than that in defining it  
    std::unorded_map<std::string_view, std::unique_ptr<User>> perPlayer;
    std::unorded_map<std::string_view, std::unique_ptr<User>> perAudience;
}