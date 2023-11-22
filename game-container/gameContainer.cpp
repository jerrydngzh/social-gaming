#include "gameContainer.h"
#include "../core-game-engine/lib/include/game.h"
#include "DTO.h"
#include "configuration.h"

// GameContainer()
// {
//     Game gameInstance("../docs/rock-paper-scissors.game");
//     // The configuration we are expectig is the one included in this file (Our code)
//     // but currently it returns the configuration in game-container (Mike's code)
//     Configuration *config = gameInstance.getConfiguration();
//     std::vector<Configuration::Setting> settings = config->getSettings();
// };

GameContainer::GameContainer() : ownerID(0), game(nullptr), gameInviteCode(0), playerList(){
    game = std::make_unique<Game>("../docs/rock-paper-scissors.game");
    // The configuration we are expecting is the one included in this file (Our code)
    // but currently it returns the configuration in game-container (Mike's code)
    Configuration *config = game->getConfiguration();
    settings = config->getSettings();
    // game->runStub();
};



void GameContainer::getMsgFromGCManager(const C2SDTO& serverDTO)
{
    if (serverDTO.command == "JOIN")
    {
        addPlayerToList(serverDTO.clientID);
        
    }
    else if (serverDTO.command == "INPUT")
    {
        //do something with player input, run game?
        game->run();

    }
}

DTOtoGameContainerManager GameContainer::sendMsgToGCManager()
{
    DtoFromGame dto = {true, 42, "example", 123, {1, 10}, {}};
    return dto;
}
