#pragma once

#include <string>
#include <cpp-tree-sitter.h>


// Handles the variables section of the Game file
class Variables {
    private:
        ts::Node node;
    public:
        Variables(const ts::Node& node);
        ~Variables();
        ts::Node getNode() const;
        std::string_view getContents(const std::string_view& gameFile) const;
};