#pragma once

// this file is used to inherit the Mapping struct
// so we do not have have to include the treesitter header
// in our business logic
struct Mapping {
    int index;
    std::string key;
    std::string_view value;
    int parent;
    std::vector<int> children;
    std::string_view type;

    Mapping& operator=(const Mapping &other) {
        if(this != &other) {
            index = other.index;
            key = other.key;
            value = other.value;
            parent = other.parent;
            children = other.children;
            type = other.type;
        }
        return *this;
    }

    bool operator==(const Mapping &other) {
        return (
            index == other.index &&
            key == other.key &&
            value == other.value && 
            parent == other.parent &&
            children == other.children &&
            type == other.type);
    }

    bool operator!=(const Mapping &other) {
        return (
            index != other.index ||
            key != other.key ||
            value != other.value ||
            parent != other.parent ||
            children != other.children ||
            type != other.type);
    }
}; 
