#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "gameContainer.h"
#include <tuple>
#include <vector>

using namespace testing;


class GameContainerTests : public testing::Test {
protected:
    int expectedClientId = 1;
    Setting::Kind expectedKind = Setting::STRING;
    Setting expectedSetting{"weapon", expectedKind};
    bool expectedIsParallel = false;
    std::variant<int, bool> expectedValue = static_cast<int>(42);
    std::tuple<int, int> expectedRange = std::make_tuple(1, 2);
    GameRequest expectedRequest{"command"};

    std::vector<int> clientIds = { 3, 5, 0 }; 
    ClientsToServerDataObject joinDTO = {1, "JOIN", "2", true};
    GameContainer joinGameContainer{0, 0, clientIds, joinDTO};

    ClientsToServerDataObject inputDTO = {1, "INPUT", "2", true};
    GameContainer inputGameContainer{0, 0, clientIds, inputDTO};

    GameContainer container{0, 0, clientIds, inputDTO};
};

TEST_F(GameContainerTests, POC) {
    EXPECT_TRUE(true);
};

TEST_F(GameContainerTests, testConstructor){
    EXPECT_EQ(0, container.getOwnerID());
    EXPECT_EQ(0, container.getGameInviteCode());
    EXPECT_EQ(std::vector<int>({3, 5, 0}), container.getPlayerList());
};

TEST_F(GameContainerTests, testProcessCommandInput){ 
    DTOtoGameContainerManager expectedInputDTO{expectedClientId, clientIds, expectedSetting,
                                     expectedIsParallel, expectedValue, expectedRange, expectedRequest};

    DTOtoGameContainerManager resultDTO = inputGameContainer.proccessCommandAndGetNextRequest(inputDTO);

    EXPECT_EQ(expectedInputDTO, resultDTO);
};

TEST_F(GameContainerTests, testProcessCommandJoin) {
    std::vector<int> expectedPlayerList = clientIds;
    expectedPlayerList.push_back(1);  

    DTOtoGameContainerManager expectedJoinDTO{expectedClientId, expectedPlayerList, expectedSetting,
                                     expectedIsParallel, expectedValue, expectedRange, expectedRequest};

    DTOtoGameContainerManager resultDTO = joinGameContainer.proccessCommandAndGetNextRequest(joinDTO);

    EXPECT_EQ(expectedJoinDTO, resultDTO);
};

TEST_F(GameContainerTests, testIsInValid) {
    bool shouldBeFalse = container.validateInput("boo");
    EXPECT_FALSE(shouldBeFalse);
};

TEST_F(GameContainerTests, testIsValid) {
    container.addValidInput("foo");
    bool shouldBeTrue = container.validateInput("foo");
    EXPECT_TRUE(shouldBeTrue);
};

TEST_F(GameContainerTests, testIsValidandInvalid) {
    container.addValidInput("foo");
    container.addValidInput("xoo");
    container.addValidInput("too");
    bool shouldBeTrue = container.validateInput("foo");
    EXPECT_TRUE(shouldBeTrue);
    bool shouldBeFalse = container.validateInput("hi");
    EXPECT_FALSE(shouldBeFalse);
};

TEST_F(GameContainerTests,testGameContainerProcesor){
    DtoFromGame inputDto{expectedIsParallel,expectedClientId,"command",expectedValue,expectedRange,expectedSetting,{}};
    DTOtoGameContainerManager dtoToManager = container.GameContainerProcessor(inputDto);
    DTOtoGameContainerManager expectedOutput = {expectedClientId,clientIds,expectedSetting,expectedIsParallel,expectedValue,expectedRange,expectedRequest};

    EXPECT_EQ(expectedOutput, dtoToManager);
}


