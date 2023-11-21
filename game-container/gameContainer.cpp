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
    Configuration *config = gameInstance.getConfiguration();
    settings = config->getSettings();
};

void GameContainer::getMsgFromGCManager(const GameContainerManagerDTO& serverDTO)
{
    if (serverDTO.command == "JOIN")
    {
        addPlayerToList(serverDTO.clientID);
        
    }
    else if (serverDTO.command == "INPUT")
    {
        //do something with player input, run game?
        game.runGame(DTOtoGame);

    }
}

GameContainerManagerDTO GameContainer::sendMsgToGCManager()
{
    GameContainerManagerDTO dto;
    return dto;
}
