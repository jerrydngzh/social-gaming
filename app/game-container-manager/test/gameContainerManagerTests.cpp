#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "gameContainerManager.h"

TEST(gameContainerManager, POC) {
    EXPECT_TRUE(true);
} // POC

TEST(DummyTestSuite, DummyTest) {
    // Arrange 
    int x = 1;
    int result = 0;

    // Act 
    result = x + 1;

    // Assert 
    EXPECT_EQ(result, 2);
}

TEST(ComponentTest, InitializationTest) {
    ASSERT_NO_THROW({
        GameContainerManager gameContainerManager;
        ClientsManager clientsManager;

        CreateProcessor createProcessor(gameContainerManager, clientsManager);
        JoinProcessor joinProcessor(gameContainerManager, clientsManager);
        InputProcessor inputProcessor(gameContainerManager, clientsManager);
        InvalidCommandProcessor invalidCommandProcessor;
    });
}


TEST(ComponentTest, CreateGameContainer){

    GameContainerManager gameContainerManager;
    int containerID = gameContainerManager.createGameContainer();
    ASSERT_EQ(containerID, 0);
    ASSERT_TRUE(gameContainerManager.doesGameContainerIDExist(containerID));
}
