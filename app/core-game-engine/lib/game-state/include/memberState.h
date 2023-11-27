//This will be specific data for a player or audience member
#pragma once

class MemberState {
    public:
        const std::string name;
        const int id;
        std::map<std::string, Value*> elements;
        MemberState(std::string name, int id) : name(name), id(id) {};
        ~MemberState() {
            for (auto element : elements) {
                delete element.second;
            }
        };
};