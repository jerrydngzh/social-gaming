#include <string_view>

class GameRoom {
public: 
private:
    const std::string_view gameCode;

    // this is how a unique point can be definded
    // std::unique_ptr<MyClass> myPtr = std::make_unique<MyClass>(42);
    // TODO: improve on value type (instead of void*)
    std::unorded_map<std::string, std::unique_ptr<void*>> variables;
}