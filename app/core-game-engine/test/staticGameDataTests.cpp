#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <memory>

#include "util.h"
#include "staticGameData.h"

//******************************
//      GLOBAL VARIABLES
//******************************

static const std::string FILE_LOCATION = "test-game-files/rock-paper-scissors.game";
static const bool TEST_PRINT_CONFIGURATION = false;
static const bool TEST_PRINT_CONSTANTS = false;
static const bool TEST_PRINT_PER_AUDIENCE = false;
static const bool TEST_PRINT_PER_PLAYER = false;
static const bool TEST_PRINT_VARIABLES = false;

//******************************
//          SETUP
//******************************

// get the file contents
static std::string init() {
    return parseGAMEFromFile(FILE_LOCATION);
}


//******************************
//           TESTS
//******************************

TEST(staticGameData, print) {
    std::string fileContents = init();

    std::unique_ptr<StaticGameData> game = std::make_unique<StaticGameData>(fileContents);
    
    if(TEST_PRINT_CONFIGURATION) game->printStaticData("configuration");
    if(TEST_PRINT_CONSTANTS) game->printStaticData("constants");
    if(TEST_PRINT_PER_AUDIENCE) game->printStaticData("perAudience");
    if(TEST_PRINT_PER_PLAYER) game->printStaticData("perPlayer");
    if(TEST_PRINT_VARIABLES) game->printStaticData("variables");

    EXPECT_TRUE(true);
}// print


TEST(staticGameData, getName) {
    std::string fileContents = init();
    std::unique_ptr<StaticGameData> game = std::make_unique<StaticGameData>(fileContents);

    const std::string expected = "Rock, Paper, Scissors";
    EXPECT_TRUE(game->getGameName() == expected);
}// getName