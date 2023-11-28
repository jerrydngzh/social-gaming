#include "gameState.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

//******************************
//      GLOBAL VARIABLES
//******************************

static const bool TEST_PRINT = false;

//******************************
//           TESTS
//******************************

TEST(ConfigurationStateTest, setting) {
    // setup
    GameState cS;

    cS.addSetting(new BooleanSetting("boolTest", true));
    cS.addSetting(new IntegerSetting("intTest", 1));

    if (TEST_PRINT) {
        printf("ConfigurationState, setting\n");
    }

    EXPECT_EQ(cS.settings.at("boolTest")->kind, Setting::Kind::BOOLEAN);
    EXPECT_EQ(cS.settings.at("intTest")->kind, Setting::Kind::INTEGER);

    BooleanSetting* bS = static_cast<BooleanSetting*>(cS.settings.at("boolTest"));
    EXPECT_EQ(bS->value, true);
    bS->value = false;
    EXPECT_EQ(bS->value, false);
    IntegerSetting* iS = static_cast<IntegerSetting*>(cS.settings.at("intTest"));
    EXPECT_EQ(iS->value, 1);
    iS->value = 2;
    EXPECT_EQ(iS->value, 2);
}