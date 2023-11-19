#pragma once
#include <cpp-tree-sitter.h>
#include <string>
#include <vector>
#include <cassert>
#include <cstdio>
#include <memory>
#include <iostream>

#include "mapping.h"

ts::Tree parseTree(const std::string& source);


// Extracts the information from a tree using a string of contents
// Format is a public method that takes in a node and will return 
// a std::vector of type Mapping
class Extractor {
    private:
        const std::vector<std::string> rootKeys = {"configuration", "constants", "per-player", "per-audience", "variables"};
        const std::vector<std::string> wrapperTypes = {"expression"};
        const std::vector<std::string> keyTypes = {"identifier", "name:", "audience:", "kind:", "prompt:", "player range:", "range:", "default:"};
        const std::vector<std::string> valueTypesWithKey = {"integer", "boolean", "string", "enum", "question-answer", "multiple-choice", "json", "quoted_string", "number", "number_range"};
        const std::vector<std::string> valueTypesNoKey = {};
        const std::vector<std::string> listTypes = {"expression_list", "number_range", "list_literal"};
        const std::vector<std::string> keyOnlyTypes = {"list_literal"};
        const std::vector<std::string> ignoredTypes = {"map_entry", "value_map", "false", "per_player", "per_audience"};
        const std::vector<std::string> invalidTypes = {"{", "}", "[", "]", ":", ",", "(", ")"};
        const std::string fileContents;

        // adds Mapping object to data structure, adjusts parent's children if needed, and returns the index of added entry
        int append(std::vector<Mapping> &data, const Mapping &entry);

        // removes colons and replaces space chars with underscore chars
        std::string changeStringContent(std::string toFix);

        // Will throw error if the Type is unrecognized
        void checkUnrecognizedType(const std::string &type);

        // returns a modified key by adding second argument to first
        std::string createKey(const std::string currentKey, const std::string toAdd);

        // Create and format a specific Mapping object
        Mapping createMapping(std::vector<Mapping> &data, const std::string &key, const std::string &value, int &parent, const std::string &type);

        // creates a path as type string that is used for the Key field in Mapping
        std::string createUniquePath(const std::vector<Mapping> &data, const std::string &key, const int &parent, const std::string &type);

        // Returns True if the type if found in validList, otherwise returns false
        bool isTypeInList(const std::string &type, const std::vector<std::string> &validList);

        // Recurse the Tree, extracting contents and adding to Mapping Vector
        void recurse(const ts::Node &node, std::vector<Mapping> &data, std::string &key, int &parent);

    public:
        Extractor(const std::string &fileContents);
        ~Extractor();

        // Returns a new Mapping Vector by recursively traversing the tree starting at the argument node
        std::vector<Mapping> format(const ts::Node &node);
};
