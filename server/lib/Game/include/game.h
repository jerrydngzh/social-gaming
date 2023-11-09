#pragma once

#include <cstdlib>
#include <fstream>
#include <unordered_map>
#include <memory>

// temporary
enum GameType {
   RockPaperScissors
};

// This Game class is roughly meant to represent the confiuration json
// defined in the project description. Have switched design
// from inheritance to composition
class Game {
public:
    
    // temporary
    GameType getTypeOfGame();
    
    // Creates Json File to send to server
    // PRE: No arguments (uses the variables it already has to build it)
    // POST: Returns a json file 
    std::ifstream createJsonFile();

    // You can also define other non-pure virtual functions with a default implementation
    std::tuple<int, int> getPlayerRange();
private:

    GameType typeOfGame;
    std::tuple<int, int> playerRange;
    bool hasAudience;
    
    // change it from std::string to something else later - avoid stringify
    // configuration contains many items + another map for "setup"
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> setupSettings;

    // this is how a unique point can be definded
    // std::unique_ptr<MyClass> myPtr = std::make_unique<MyClass>(42);
    // TODO: improve on value type (instead of void*)
    std::unordered_map<std::string_view, std::unique_ptr<void>> variables;
    std::unordered_map<std::string_view, std::unique_ptr<void>> constants;
};