//This should be rewritten to just hold the final values of Setup (map of name to Setting or even variant)
#pragma once

#include <string>

class Setting {//for storing the setup data
    protected:
        std::string name;
    public: //Consider visitor patter instead of storing a type like this?
        enum Kind {
            BOOLEAN,
            INTEGER,
            STRING,
            ENUM,
            QUESTION_ANSWER,
            MULTIPLE_CHOICE,
            JSON
        } kind;
        Kind getKind() const {
            return kind;
        };
        Setting(std::string name, Kind kind) : name(name), kind(kind) {};
    };

class BooleanSetting : public Setting {
private:
    bool value;
public:
    BooleanSetting(std::string name, const bool value) : Setting(name, Kind::BOOLEAN), value(value) {};
    ~BooleanSetting();
    bool getValue() const {
        return value;
    };
    void setValue(const bool value){
        this->value = value;
    };
};

class IntegerSetting : public Setting {
private:
    int value;
public:
    IntegerSetting(std::string name, const int value) : Setting(name, Kind::INTEGER), value(value) {};
    ~IntegerSetting();
    int getValue() const {
        return value;
    };
    void setValue(const int value) {
        this->value = value;
    }
};

//TODO: implement the rest of the settings (String, Enum, QuestionAnswer, MultipleChoice, JSON)
