#include <cstdlib>

enum GameType {
   RockPaperScissors
};



class Game {
    
public:
    // Pure virtual function, making it an abstract method
    virtual GameType getTypeOfGame() = {
        return typeOfGame;
    };

    // You can also define other non-pure virtual functions with a default implementation
    virtual std::tuple<int, int> getPlayerRange() {
        return getPlayerRange;
    }

    // Virtual destructor (important when working with interfaces)
    virtual ~Game() {}
private:
    GameType typeOfGame;
    std::tuple<int, int> playerRange;
    bool hasAudience;
    
    // change it from std::string to something else later - avoid stringify
    // configuration contains many items + another map for "setup"
    std::unordered_map<std::string,std::unordered_map<std::string, std::string>> configuration;
};