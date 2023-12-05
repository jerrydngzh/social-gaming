#include "deserializer.h"
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

TEST(gameState, initialization) {
    // setup
    GameState gS;

    gS.addConstant(new BooleanValue("boolTest", true));
    gS.addConstant(new IntegerValue("intTest", 1));

    if (TEST_PRINT) {
        printf("gameState, initialization\n");
    }

    EXPECT_EQ(gS.values.at("boolTest")->kind, Value::Kind::BOOLEAN);
    EXPECT_EQ(gS.values.at("intTest")->kind, Value::Kind::INTEGER);

    BooleanValue* bS = static_cast<BooleanValue*>(gS.values.at("boolTest"));
    EXPECT_EQ(bS->value, true);
    bS->value = false;
    EXPECT_EQ(bS->value, false);
    IntegerValue* iS = static_cast<IntegerValue*>(gS.values.at("intTest"));
    EXPECT_EQ(iS->value, 1);
    iS->value = 2;
    EXPECT_EQ(iS->value, 2);
}

TEST(gameState, factroy) {
    GameStateFactory gSF;
    GameState gS = gSF.createInitialGameState();
    gS.addConstant(new BooleanValue("boolTest", true));

    EXPECT_EQ(gS.values["weapons"]->kind, Value::Kind::LIST);
}