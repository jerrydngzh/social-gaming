#pragma once

#include <string>
#include <tuple>
#include <vector>
#include <cpp-tree-sitter.h>

#include "mapping.h"
#include "gameLibrary.h"

class Configuration : public GameLibrary {
    public:
        Configuration(const std::vector<Mapping> &data);
        ~Configuration();
};

// // Handles the configuration section of the Game file
// class Configuration {
//     class Setting {//for storing the setup data
//     protected:
//         std::string prompt;
//         bool hasDefaultValue;
//     public:
//         enum Kind {
//             BOOLEAN,
//             INTEGER,
//             STRING,
//             ENUM,
//             QUESTION_ANSWER,
//             MULTIPLE_CHOICE,
//             JSON
//         } kind;
//         std::string getPrompt() const;
//         Kind getKind() const;
//         bool getHasDefaultValue() const;

//         Setting(Kind kind, std::string prompt, const bool hasDefaultValue);
//     };

//     class BooleanSetting : public Setting {
//     private:
//         bool value;
//         bool defaultValue;
//     public:
//         BooleanSetting(std::string prompt, const bool defaultValue);
//         BooleanSetting(std::string prompt);
//         ~BooleanSetting();
//         bool getValue() const;
//         void setValue(const bool value);
//         bool getDefaultValue() const;
//     };

//     class IntegerSetting : public Setting {
//     private:
//         int value;
//         int defaultValue;
//         std::tuple<int, int> range;
//     public:
//         IntegerSetting(std::string prompt, const int defaultValue, const int min, const int max);
//         IntegerSetting(std::string prompt, const int min, const int max);
//         ~IntegerSetting();
//         int getValue() const;
//         void setValue(const int value);
//         int getDefaultValue() const;
//     };

//     //TODO: implement the rest of the settings (String, Enum, QuestionAnswer, MultipleChoice, JSON)


// private:
//     const std::string_view gameFile;
//     ts::Node node;
//     std::string gameName;
//     std::tuple<int, int> players;
//     bool hasAudience;
//     std::vector<Setting> settings; //setup up stage from nick's requirements
// public:
//     static const std::string GAME_NAME_FIELD;
//     static const std::string PLAYERS_FIELD;
//     static const std::string AUDIENCE_FIELD;
//     static const std::string SETUP_FIELD;

//     Configuration(const ts::Node& node, const std::string_view& gameFile);
//     ~Configuration();
//     ts::Node getNode() const;
//     void parsePlayers(const std::string_view& playersString);
//     std::string_view getContents(const std::string_view& gameFile) const;
//     std::string_view getGameFile() const;
//     std::string getGameName() const;
//     std::tuple<int, int> getPlayer() const;
//     bool getHasAudience() const;
//     bool isPlayerCountInRanger(const int playerCount) const;
// };

