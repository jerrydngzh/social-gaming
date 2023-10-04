#include <cassert>
#include <cstdio>
#include <memory>
#include <string>

#include <cpp-tree-sitter.h>


extern "C" {
  TSLanguage* tree_sitter_socialgaming();
}

int main(int argc, char* argv[]) {
  // Concatenate all command-line arguments into a single string
  std::string inputString;
  for (int i = 1; i < argc; ++i) {
    inputString += argv[i];
    if (i < argc - 1) {
      inputString += ' '; // Add a space between arguments
    }
  }
  // Create a language and parser.
  ts::Language language = tree_sitter_socialgaming();
  ts::Parser parser{ language };

  // Parse the provided string into a syntax tree.
  std::string sourcecode = "[1, null]";
  if (argc > 1) {
    sourcecode = inputString;
  }
  ts::Tree tree = parser.parseString(sourcecode);

  // Get the root node of the syntax tree. 
  ts::Node root = tree.getRootNode();

  // Get some child nodes.
  ts::Node array = root.getNamedChild(0);
  ts::Node number = array.getNamedChild(0);

  // Check that the nodes have the expected types.
  /*assert(root.getType() == "document");
  assert(array.getType() == "array");
  assert(number.getType() == "number");

  // Check that the nodes have the expected child counts.
  assert(root.getNumChildren() == 1);
  assert(array.getNumChildren() == 5);
  assert(array.getNumNamedChildren() == 2);
  assert(number.getNumChildren() == 0);*/

  // Print the syntax tree as an S-expression.
  auto treestring = root.getSExpr();
  printf("Syntax tree: %s\n", treestring.get());

  return 0;
}