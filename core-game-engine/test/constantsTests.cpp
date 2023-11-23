#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "util.h"
#include "treeParser.h"
#include "constants.h"

//******************************
//      GLOBAL VARIABLES
//******************************

static const std::string FILE_LOCATION = "core-game-engine-build/game-files/rock-paper-scissors.game";
static const std::string LIBRARY_TYPE = "constants";
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

TEST(Constants, print) {
    Constants constantsLibrary(init());

    if(TEST_PRINT == true){
        constantsLibrary.print();
    }

    EXPECT_TRUE(true);
}// print


TEST(Constants, weapons) {
    Constants constantsLibrary(init());

    std::string weaponName1 = std::get<std::string>(constantsLibrary.lookup("constants.weapons[0].name"));
    std::string weaponBeats1 = std::get<std::string>(constantsLibrary.lookup("constants.weapons[0].beats"));
    std::string weaponName2 = std::get<std::string>(constantsLibrary.lookup("constants.weapons[1].name"));
    std::string weaponBeats2 = std::get<std::string>(constantsLibrary.lookup("constants.weapons[1].beats"));
    std::string weaponName3 = std::get<std::string>(constantsLibrary.lookup("constants.weapons[2].name"));
    std::string weaponBeats3 =  std::get<std::string>(constantsLibrary.lookup("constants.weapons[2].beats"));

    EXPECT_TRUE(weaponName1 == "Rock");
    EXPECT_TRUE(weaponBeats1 == "Scissors");
    EXPECT_TRUE(weaponName2 == "Paper");
    EXPECT_TRUE(weaponBeats2 == "Rock");
    EXPECT_TRUE(weaponName3 == "Scissors");
    EXPECT_TRUE(weaponBeats3 == "Paper");
}// weapons
