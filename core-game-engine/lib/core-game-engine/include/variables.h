#pragma once

#include <string>
#include <cpp-tree-sitter.h>

class Variables {
    private:
        ts::Node node;
    public:
        Variables(const ts::Node& node);
        ~Variables();
        ts::Node getNode() const;
        std::string_view getContents(const std::string_view& gameFile) const;
};