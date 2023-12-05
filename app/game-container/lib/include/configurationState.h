// Holds the final values of Setup and the name associated with them
#pragma once

#include <algorithm>
#include <string>
#include <vector>

class Setting {
   public:
    std::string name;
    enum Kind {
        BOOLEAN,
        INTEGER,
        STRING,
        ENUM,
        QUESTION_ANSWER,
        MULTIPLE_CHOICE,
        JSON
    } kind;
    Setting(std::string name, Kind kind) : name(name), kind(kind){};
    Setting& operator=(const Setting& other) {
        if (this != &other) {
            name = other.name;
            kind = other.kind;
        }
        return *this;
    }
    bool operator==(const Setting& other) const {
        return name == other.name && kind == other.kind;
    }
};

class BooleanSetting : public Setting {
   public:
    bool value;
    BooleanSetting(std::string name, const bool value) : Setting(name, Kind::BOOLEAN), value(value){};
    ~BooleanSetting();
};

class IntegerSetting : public Setting {
   public:
    int value;
    IntegerSetting(std::string name, const int value) : Setting(name, Kind::INTEGER), value(value){};
    ~IntegerSetting();
};

// TODO: implement the rest of the settings (String, Enum, QuestionAnswer, MultipleChoice, JSON)