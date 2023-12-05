#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "gameContainer.h"
using namespace testing;

class GameContainerTests : public testing::Test {
protected:
    ClientsToServerDataObject dto = {1, "JOIN", "2", true};
};

TEST(gameContainer, POC) {
    EXPECT_TRUE(true);
};
// test is failing due to segfault with gamestate initialization (outside of gamecontainer)
TEST(gameContainer, testConstructor){
    // test gamefactory first
    GameStateFactory gsFactory;
    GameState game = gsFactory.createInitialGameState();
    
    ClientsToServerDataObject dto = {1, "JOIN", "2", true};
    std::vector<int> clientsIds = {1,3,5,0};
    GameContainer container{1, 1, clientsIds, dto};
    
};

TEST(gameContainer, testGameContainerManagerFunctionInputInvalid){

    const ClientsToServerDataObject dto = {1, "INPUT", "2", true};

    std::vector<int> clientsIds = {1,3,5,0};
    GameContainer container{1, 1, clientsIds, dto}; 


    container.proccessCommandAndGetNextRequest(dto);
};

TEST(gameContainer, test){
    const ClientsToServerDataObject dto = {1, "JOIN", "2", true};

    std::vector<int> clientsIds = {1,3,5,0};
    GameContainer container{1, 1, clientsIds, dto}; 

    container.proccessCommandAndGetNextRequest(dto);
};