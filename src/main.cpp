// Copyright 2021 NNTU-CS

#include "bst.h"
#include <iostream>
#include <string>

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
    std::cout << "=== Word Frequency Analysis ===" << std::endl;
    std::cout << "Analyzing 'War and Peace' by Leo Tolstoy" << std::endl;
    std::cout << "===========================================" << std::endl;
    BST<std::string> tree;
    const char* filename = "src/war_peace.txt";
    std::cout << "\nLoading file: " << filename << std::endl;
    makeTree(tree, filename);
    if (tree.isEmpty()) {
        std::cout << "Tree is empty. Check if the file exists and contains words." << std::endl;
        return 1;
    }
    printFreq(tree);
    std::cout << "\n=== Search Examples ===" << std::endl;
    std::string testWords[] = {"the", "and", "to", "war", "peace", "tolstoy"};
    for (const auto& word : testWords) {
        int count = tree.getCount(word);
        if (count > 0) {
            std::cout << "Word '" << word << "' appears " << count << " times" << std::endl;
        } else {
            std::cout << "Word '" << word << "' not found" << std::endl;
        }
    }
    std::cout << "\n=== Tree Statistics ===" << std::endl;
    std::cout << "Tree depth: " << tree.depth() << std::endl;
    return 0;
}
