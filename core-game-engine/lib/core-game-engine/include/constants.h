#pragma once

#include <string>
#include <cpp-tree-sitter.h>

class Constants {
    private:
        ts::Node node;
    public:
        Constants(const ts::Node& node);
        ~Constants();
        ts::Node getNode() const;
        std::string_view getContents(const std::string_view& gameFile) const;
};