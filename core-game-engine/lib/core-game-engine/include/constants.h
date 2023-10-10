#pragma once

#include <string>
#include <cpp-tree-sitter.h>


// Handles the constants section of the Game file
class Constants {
    private:
        ts::Node node;
    public:
        Constants(const ts::Node& node);
        ~Constants();
        ts::Node getNode() const;
        std::string_view getContents(const std::string_view& gameFile) const;
};