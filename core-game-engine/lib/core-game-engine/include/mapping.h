#pragma once

// this file is used to inherit the Mapping struct
// so we do not have have to include the treesitter header
// in our business logic
struct Mapping {
    int index;
    std::string_view key;
    std::string_view value;         // TODO: this will need to be able to handle different types eventually
    int parent;
    std::vector<int> children;
    std::string_view type;
}; 
