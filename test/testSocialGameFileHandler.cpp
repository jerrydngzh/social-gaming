#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../client/lib/SocialGameFileHandler/include/socialgamefilehandler.h"
#include <iostream>
#include <string>

using namespace testing;

class FileHandlerTests: public ::testing::Test {
protected:
    SocialGameFileHandler testFileHandler;
    //this should just be a temp test file bcs this file is too damn big
    std::string validFilePath = "../docs/rock-paper-scissors.game";
    std::string invalidFilePath = "../docs/fake-file.game";
};

// getFileContents() check that fileContent contains the correct content of a test file
TEST_F(FileHandlerTests, testFileContent) {
    EXPECT_EQ();
}

// getFileContents() check that we're getting an error if we put non-existent filePath

// getFileContents() check that we're getting an error if file cannot be opened...
// idk this one kinda hard lol we shall see...