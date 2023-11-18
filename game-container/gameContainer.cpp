#include "../core-game-engine/lib/include/game.h"
#include "DTO.h"
#include "configuration.h"

class GameContainer {

    GameContainer(){
        Game gameInstance("filepath");
        // The configuration we are expectig is the one included in this file (Our code)
        // but currently it returns the configuration in game-container (Mike's code)
        Configuration* config = gameInstance.getConfiguration();
        std::vector<Configuration::Setting> settings = config->getSettings();
    }
    
    
private:
    std::vector<Configuration::Setting> settings;
};