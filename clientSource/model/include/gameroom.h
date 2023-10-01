#include <string_view>
#include "user.h"

class GameRoom : public Game{
public: 
private:
    const std::string_view gameCode;

    // this is how a unique point can be definded
    // std::unique_ptr<MyClass> myPtr = std::make_unique<MyClass>(42);
    // TODO: improve on value type (instead of void*)
    std::unorded_map<std::string, std::unique_ptr<void*>> variables;

    // User has fields to determine if is player, audience, or owner
    // maybe explore better way than that in defining it  
    std::unorded_map<std::string, std::unique_ptr<User>> perPlayer;
    std::unorded_map<std::string, std::unique_ptr<User>> perAudience;
}