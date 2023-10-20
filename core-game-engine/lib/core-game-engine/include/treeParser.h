#pragma once
#include <cpp-tree-sitter.h>
#include <string>
#include <vector>

ts::Tree parseTree(const std::string& source);

struct Mapping {
    int index;
    std::string_view key;
    std::string_view value;         // TODO: this will need to be able to handle different types eventually
    int parent;
    std::vector<int> children;
    std::string_view type;
}; 


// Creates an object that can extract the information from a tree
// Calling format with the root node to parse and the file contents as a string 
// will return a std::vector of type Mapping
class Extractor {
    private:
        std::string_view key;
        std::string_view value;     // TODO: needs to be variable type
        int parent;
        std::string fileContents;

        void append(std::vector<Mapping> &data, const int &index, const std::string_view &key, const std::string_view &value, const int &parent, const std::string_view &type);
        void recurse(const ts::Node &node, std::vector<Mapping> &data);
    public:
        Extractor(const std::string &fileContents);
        ~Extractor();

        std::vector<Mapping> format(const ts::Node &node);
};
