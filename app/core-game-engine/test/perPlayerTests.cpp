#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "util.h"
#include "treeParser.h"
#include "perPlayer.h"


//******************************
//      GLOBAL VARIABLES
//******************************

static const std::string FILE_LOCATION = "core-game-engine-build/game-files/rock-paper-scissors.game";
static const std::string LIBRARY_TYPE = "per_player";
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
}// init()


//******************************
//           TESTS
//******************************

TEST(PerPlayer, print) {
    PerPlayer perPlayerLibrary(init());

    if(TEST_PRINT == true) {
        perPlayerLibrary.print();
    }

    EXPECT_TRUE(true);
}// print


TEST(PerPlayer, lookupWins) {
    PerPlayer perPlayerLibrary(init());

    int wins = std::get<int>(perPlayerLibrary.lookup("per-player.wins"));
    EXPECT_TRUE(wins == 0);
}// lookupWins