#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "gameState.h"
#include "configurationState.h"

//******************************
//      GLOBAL VARIABLES
//******************************

static const bool TEST_PRINT = true;

//******************************
//           TESTS
//******************************

TEST(ConfigurationStateTest, setting) {
    
    //setup
    ConfigurationState configurationState;

    if(TEST_PRINT) {
        printf("ConfigurationState, setting\n");
    }

    EXPECT_TRUE(true);
}// print