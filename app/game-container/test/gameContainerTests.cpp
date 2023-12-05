#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "gameContainer.h"
#include <tuple>

using namespace testing;


class GameContainerTests : public testing::Test {
protected:
    // const ClientsToServerDataObject joinCommandDTO = {1, "JOIN", "2", true};
    std::variant<int, bool> myVariant = static_cast<int>(42);
    std::tuple<int, int> myTuple = std::make_tuple(1, 2);
    Setting::Kind kind = Setting::STRING;
    Setting mySetting{"weapon", kind};
    GameRequest request{"pause"} ;

    // DTOtoGameContainerManager expectedJoinDTO = { 2, {}, mySetting, true, myVariant, myTuple, request};
};

TEST(GameContainerTests, POC) {
    EXPECT_TRUE(true);
};
// test is failing due to segfault with gamestate initialization (outside of gamecontainer)
TEST(GameContainerTests, testConstructor){
    // test gamefactory first
    GameStateFactory gsFactory;
    GameState game = gsFactory.createInitialGameState();
    
    ClientsToServerDataObject dto = {1, "JOIN", "2", true};
    std::vector<int> clientsIds = {1,3,5,0};
    GameContainer container{1, 1, clientsIds, dto};
    
};

TEST(GameContainerTests, testGameContainerManagerFunctionInputInvalid){

    const ClientsToServerDataObject dto = {1, "INPUT", "2", true};

    std::vector<int> clientsIds = {1,3,5,0};
    GameContainer container{1, 1, clientsIds, dto}; 


    container.proccessCommandAndGetNextRequest(dto);
};

TEST(GameContainerTests, testProcessCommandJoin){
    const ClientsToServerDataObject dto = {1, "JOIN", "2", true};

    std::vector<int> clientsIds = {1,3,5,0};
    GameContainer container{1, 1, clientsIds, dto}; 
    std::variant<int, bool> myVariant = static_cast<int>(42);
    std::tuple<int, int> myTuple = std::make_tuple(1, 2);
    Setting::Kind kind = Setting::STRING;
    Setting mySetting{"weapon", kind};
    GameRequest request{"pause"} ;


    DTOtoGameContainerManager resultDTO = container.proccessCommandAndGetNextRequest(dto);
    
    DTOtoGameContainerManager expectedJoinDTO = {2, {}, mySetting, true, myVariant, myTuple, request};

    EXPECT_TRUE(expectedJoinDTO == resultDTO);
};

TEST(GameContainerTests, testIsInValid) {
    const ClientsToServerDataObject dto = {1, "JOIN", "2", true};

    std::vector<int> clientsIds = {1,3,5,0};
    GameContainer container{1, 1, clientsIds, dto}; 
    bool shouldBeFalse = container.validateInput("boo");
    EXPECT_FALSE(shouldBeFalse);
};

TEST(GameContainerTests, testIsValid) {
    const ClientsToServerDataObject dto = {1, "JOIN", "2", true};

    std::vector<int> clientsIds = {1,3,5,0};
    GameContainer container{1, 1, clientsIds, dto}; 
    container.addValidInput("foo");
    bool shouldBeTrue = container.validateInput("foo");
    EXPECT_TRUE(shouldBeTrue);
};

TEST(GameContainerTests, testIsValidandInvalid) {
    const ClientsToServerDataObject dto = {1, "JOIN", "2", true};

    std::vector<int> clientsIds = {1,3,5,0};
    GameContainer container{1, 1, clientsIds, dto}; 
    container.addValidInput("foo");
    container.addValidInput("xoo");
    container.addValidInput("too");
    bool shouldBeTrue = container.validateInput("foo");
    EXPECT_TRUE(shouldBeTrue);
    bool shouldBeFalse = container.validateInput("hi");
    EXPECT_FALSE(shouldBeFalse);
};
TEST(GameContainerTests,testGameContainerProcesor){
    const ClientsToServerDataObject dto = {1, "JOIN", "2", true};
    std::vector<int> clientsIds = {1,3,5,0};
    GameContainer container{1, 1, clientsIds, dto}; 

    std::variant<int, bool> myVariant = static_cast<int>(42);
    std::tuple<int, int> myTuple = std::make_tuple(1, 2);
    Setting::Kind kind = Setting::STRING;
    Setting mySetting("weapon", kind);

    DtoFromGame myDto = {false,1,"command",myVariant,myTuple,mySetting,{}};
    DTOtoGameContainerManager dtoToManager = container.GameContainerProcessor(myDto);
    GameRequest request{"hello"};
    DTOtoGameContainerManager expectedOutput = {1,{},mySetting,false,myVariant,myTuple};
    EXPECT_TRUE(expectedOutput == dtoToManager);
    // EXPECT_EQ(expectedOutput, dtoToManager);
}


