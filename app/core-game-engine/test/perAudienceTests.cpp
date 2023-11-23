#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "util.h"
#include "treeParser.h"
#include "perAudience.h"


//******************************
//      GLOBAL VARIABLES
//******************************

static const std::string FILE_LOCATION = "core-game-engine-build/game-files/rock-paper-scissors.game";
static const std::string LIBRARY_TYPE = "per_audience";
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

TEST(PerAudience, print) {
    PerAudience perAudienceLibrary(init());

    if(TEST_PRINT == true) {
        perAudienceLibrary.print();
    }

    EXPECT_TRUE(true);
}// print


TEST(PerAudience, lookup) {
    PerAudience perAudienceLibrary(init());

    std::string root = std::get<std::string>(perAudienceLibrary.lookup("per-audience"));
    EXPECT_TRUE(root == "");
}// lookup