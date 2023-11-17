#include "configuration.h"

class GameContainer {
    Game game = new Game();
    Configuration config = game.initialize("filepath to .game");
    std::vector<Configuration::Setting> settings = config.getSettings();
    
private:
    std::vector<Configuration::Setting> settings;
};