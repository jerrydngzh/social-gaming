// These can be constant, players, audience, or variable values
#pragma once

class Value {
   public:
    const std::string name;
    const enum Kind {
        MAP,
        LIST,
        STRING,
        INTEGER,
        BOOLEAN
    } kind;
    bool isConst;
    Value(std::string name, Kind kind, bool isConst) : name(name), kind(kind), isConst(isConst){};
    Value(Kind kind, bool isConst) : name(""), kind(kind), isConst(isConst){};
};

class MapValue : public Value {
   public:
    std::map<std::string, Value*> value;
    MapValue(std::string name, std::map<std::string, Value*> value) : Value(name, Kind::MAP, false), value(value){};
    MapValue(std::map<std::string, Value*> value) : Value(Kind::MAP, false), value(value){};
    ~MapValue() {
        for (auto value : value) {
            delete value.second;
        }
    }
};

class ListValue : public Value {
   public:
    std::vector<Value*> value;
    ListValue(std::string name, std::vector<Value*> value) : Value(name, Kind::LIST, false), value(value){};
    ListValue(std::vector<Value*> value) : Value(Kind::LIST, false), value(value){};
    ~ListValue() {
        for (auto value : value) {
            delete value;
        }
    }
};

class StringValue : public Value {
   public:
    std::string value;
    StringValue(std::string name, std::string value) : Value(name, Kind::STRING, false), value(value){};
    StringValue(std::string value) : Value(Kind::STRING, false), value(value){};
    ~StringValue();
};

class IntegerValue : public Value {
   public:
    int value;
    IntegerValue(std::string name, int value) : Value(name, Kind::INTEGER, false), value(value){};
    IntegerValue(int value) : Value(Kind::INTEGER, false), value(value){};
    ~IntegerValue();
};

class BooleanValue : public Value {
   public:
    bool value;
    BooleanValue(std::string name, bool value) : Value(name, Kind::BOOLEAN, false), value(value){};
    BooleanValue(bool value) : Value(Kind::BOOLEAN, false), value(value){};
    ~BooleanValue();
};