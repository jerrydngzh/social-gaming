#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "util.h"
#include "treeParser.h"
#include "configuration.h"

//******************************
//      GLOBAL VARIABLES
//******************************

static const std::string FILE_LOCATION = "core-game-engine-build/game-files/rock-paper-scissors.game";
static const std::string LIBRARY_TYPE = "configuration";
static const bool TEST_PRINT = false;

//******************************
//          SETUP
//******************************

// initialize an extractor object
// extract node type from tree
// parse data and store in Mapping data structure
static std::vector<Mapping> init() {
    std::string fileContents = parseGAMEFromFile(FILE_LOCATION);
    ts::Tree tree = parseTree(fileContents);
    ts::Node root = tree.getRootNode();
    
    Extractor extractor(fileContents);
    ts::Node node = root.getChildByFieldName(LIBRARY_TYPE);

    return extractor.format(node);
}


//******************************
//           TESTS
//******************************

TEST(Configuration, print) {
    Configuration configurationLibrary(init());

    if(TEST_PRINT == true) {
        configurationLibrary.print();
    }

    EXPECT_TRUE(true);
}// print


TEST(Configuration, gameName) {
    Configuration configurationLibrary(init());

    // via lookup
    std::string name = std::get<std::string>(configurationLibrary.lookup("configuration.name"));
    EXPECT_TRUE(name == "Rock, Paper, Scissors");

    // via getGameName()
    EXPECT_TRUE(configurationLibrary.getGameName() == "Rock, Paper, Scissors");
}// getGameName


TEST(Configuration, playerRange) {
    Configuration configurationLibrary(init());

    // via lookup
    int lowerBound = std::get<int>(configurationLibrary.lookup("configuration.player_range[0]"));
    int upperBound = std::get<int>(configurationLibrary.lookup("configuration.player_range[1]"));
    EXPECT_TRUE(lowerBound == 2);
    EXPECT_TRUE(upperBound == 4);

    // via getPlayerRange()
    std::tuple<int, int> player_range = configurationLibrary.getPlayerRange();
    EXPECT_TRUE(std::get<0>(player_range) == 2);
    EXPECT_TRUE(std::get<1>(player_range) == 4);
}// getPlayerRange


TEST(Configuration, audience) {
    Configuration configurationLibrary(init());

    // via lookup
    bool audience = std::get<bool>(configurationLibrary.lookup("configuration.audience"));
    EXPECT_TRUE(audience == false);

    // via getHasAudience()
    EXPECT_TRUE(configurationLibrary.getHasAudience() == false);
}// getHasAudience


TEST(Configuration, isPlayerCountInRange) {
    Configuration configurationLibrary(init());

    EXPECT_TRUE(configurationLibrary.isPlayerCountInRange(0) == false);
    EXPECT_TRUE(configurationLibrary.isPlayerCountInRange(1) == false);
    EXPECT_TRUE(configurationLibrary.isPlayerCountInRange(2) == true);
    EXPECT_TRUE(configurationLibrary.isPlayerCountInRange(3) == true);
    EXPECT_TRUE(configurationLibrary.isPlayerCountInRange(4) == true);
    EXPECT_TRUE(configurationLibrary.isPlayerCountInRange(5) == false);
}// isPlayerCountInRange


TEST(Configuration, lookupRoundsKind) {
    Configuration configurationLibrary(init());
    std::string kind = std::get<std::string>(configurationLibrary.lookup("configuration.setup.rounds.kind"));

    EXPECT_TRUE(kind == "integer");
}// lookupRoundsKind


TEST(Configuration, lookupRoundsPrompt) {
    Configuration configurationLibrary(init());
    std::string prompt = std::get<std::string>(configurationLibrary.lookup("configuration.setup.rounds.prompt"));

    EXPECT_TRUE(prompt == "The number of rounds to play");
}// lookupRoundsPrompt


TEST(Configuration, lookupRoundsRange) {
    Configuration configurationLibrary(init());
    int roundsLowerBound = std::get<int>(configurationLibrary.lookup("configuration.setup.rounds.range[0]"));
    int roundsUpperBound = std::get<int>(configurationLibrary.lookup("configuration.setup.rounds.range[1]"));

    EXPECT_TRUE(roundsLowerBound == 1);
    EXPECT_TRUE(roundsUpperBound == 20);
}// lookupRoundsRange