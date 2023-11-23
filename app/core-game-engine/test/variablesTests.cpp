#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "util.h"
#include "treeParser.h"
#include "variables.h"

//******************************
//      GLOBAL VARIABLES
//******************************

static const std::string FILE_LOCATION = "test-game-files/rock-paper-scissors.game";
static const std::string LIBRARY_TYPE = "variables";
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

TEST(Variables, print) {
    Variables variablesLibrary(init());

    if(TEST_PRINT == true) {
        variablesLibrary.print();
    }

    EXPECT_TRUE(true);
}// print


TEST(Variables, lookupWinners) {
    Variables variablesLibrary(init());

    std::string winners = std::get<std::string>(variablesLibrary.lookup("variables.winners"));
    EXPECT_TRUE(winners == "");
}// lookupWinners