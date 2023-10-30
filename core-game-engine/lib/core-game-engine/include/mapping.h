#pragma once

// this file is used to inherit the Mapping struct
// so we do not have have to include the treesitter header
// in our business logic
struct Mapping {
    uint32_t index;
    std::string_view key;
    std::string_view value;
    uint32_t parent;
    std::vector<uint32_t> children;
    std::string_view type;
}; 
