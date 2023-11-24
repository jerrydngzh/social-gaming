#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "gameState.h"
#include "configurationState.h"

//******************************
//      GLOBAL VARIABLES
//******************************

static const bool TEST_PRINT = false;

//******************************
//           TESTS
//******************************

TEST(ConfigurationStateTest, setting) {
    
    //setup
    ConfigurationState cS;

    cS.addSetting(new BooleanSetting("boolTest", true));
    cS.addSetting(new IntegerSetting("intTest", 1));

    if(TEST_PRINT) {
        printf("ConfigurationState, setting\n");
    }

    EXPECT_EQ(cS.getSetting("boolTest")->getKind(), Setting::Kind::BOOLEAN);
    EXPECT_EQ(cS.getSetting("intTest")->getKind(), Setting::Kind::INTEGER);

    BooleanSetting* bS = static_cast<BooleanSetting*>(cS.getSetting("boolTest"));
    EXPECT_EQ(bS->getValue(), true);
    bS->setValue(false);
    EXPECT_EQ(bS->getValue(), false);
    IntegerSetting* iS = static_cast<IntegerSetting*>(cS.getSetting("intTest"));
    EXPECT_EQ(iS->getValue(), 1);
    iS->setValue(2);
    EXPECT_EQ(iS->getValue(), 2);
}