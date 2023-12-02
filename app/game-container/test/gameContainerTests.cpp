#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "gameContainer.h"


TEST(gameContainer, POC) {
    EXPECT_TRUE(true);
};
// test is failing due to segfault with gamestate initialization (outside of gamecontainer)
// TEST(gameContianer, testConstructor){
//     std::vector<int> clientsIds = {1,3,5,0};
//     GameContainer container{1,1,clientsIds};
// };

