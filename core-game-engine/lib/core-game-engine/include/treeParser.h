#pragma once
#include <cpp-tree-sitter.h>
#include <string>
#include <vector>

#include "mapping.h"

ts::Tree parseTree(const std::string& source);


// Extracts the information from a tree using a string of contents
// Format is a public method that takes in a node and will return 
// a std::vector of type Mapping
class Extractor {
    private:
        const std::vector<std::string_view> rootTypes = {"configuration", "constants", "per-player", "per-audience", "variables"};
        const std::vector<std::string_view> keyTypes = {"identifier", "name:", "audience:", "kind:", "prompt:", "player range:", "range:", "setup:"};
        const std::vector<std::string_view> valueTypes = {"integer", "boolean", "quoted_string", "number"};
        const std::vector<std::string_view> ignoredTypes = {"map_entry", "value_map", "false", "per_player", "per_audience"};
        const std::vector<std::string_view> invalidTypes = {"{", "}", "[", "]", ":", ",", "(", ")"};
        std::string_view key;
        std::string_view value;
        int parent;
        const std::string fileContents;

        // Create a Mapping object and add to Mapping Vector
        void append(std::vector<Mapping> &data, const std::string_view &key, const std::string_view &value, const uint32_t &parent, const std::string_view &type);

        // Recurse the Tree, extracting contents and adding to Mapping Vector
        void recurse(const ts::Node &node, std::vector<Mapping> &data);

        // Returns True if the type if found in validList, otherwise returns false
        bool isValidType(const std::string_view &type, const std::vector<std::string_view> &validList);

        // Will throw error if the Type is unrecognized
        void checkUnrecognizedType(const std::string_view &type);
    public:
        Extractor(const std::string &fileContents);
        ~Extractor();

        // Returns a new Mapping Vector by recursively traversing the tree starting at the argument node
        std::vector<Mapping> format(const ts::Node &node);
};
