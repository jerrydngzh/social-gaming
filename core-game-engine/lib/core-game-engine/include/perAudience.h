#pragma once

#include <string>
#include <cpp-tree-sitter.h>


// Handles the per_audience section of the Game file
class PerAudience {
    private:
        ts::Node node;
    public:
        PerAudience(const ts::Node& node);
        ~PerAudience();
        ts::Node getNode() const;
        std::string_view getContents(const std::string_view& gameFile) const;
};