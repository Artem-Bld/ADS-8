// Copyright 2021 NNTU-CS

#include "bst.h"
#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

bool isLatinLetter(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

char toLower(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return ch + ('a' - 'A');
    }
    return ch;
}

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "File error: Cannot open " << filename << std::endl;
        return;
    }
    std::string currentWord;
    while (true) {
        char ch = file.get();
        if (file.eof()) break;
        if (isLatinLetter(ch)) {
            currentWord += toLower(ch);
        } else {
            if (!currentWord.empty()) {
                tree.insert(currentWord);
                currentWord.clear();
            }
        }
    }
    if (!currentWord.empty()) {
        tree.insert(currentWord);
    }
    file.close();
}
bool compareByFrequency(const std::pair<std::string, int>& a, 
                        const std::pair<std::string, int>& b) {
    if (a.second != b.second) {
        return a.second > b.second;
    }
    return a.first < b.first;
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> nodes = tree.getAllNodes();
    std::sort(nodes.begin(), nodes.end(), compareByFrequency);
    std::ofstream outFile("result/freq.txt");
    if (!outFile) {
        std::cout << "Error: Cannot create result/freq.txt" << std::endl;
        return;
    }
    std::cout << "\n=== Frequency Analysis Results ===" << std::endl;
    std::cout << "Total unique words: " << nodes.size() << std::endl;
    std::cout << "Tree depth: " << tree.depth() << std::endl;
    std::cout << "\nWords sorted by frequency (descending):" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    outFile << "Word Frequency Analysis Results" << std::endl;
    outFile << "================================" << std::endl;
    outFile << "Total unique words: " << nodes.size() << std::endl;
    outFile << "Tree depth: " << tree.depth() << std::endl;
    outFile << "\nWord -> Frequency (sorted by frequency descending):" << std::endl;
    outFile << "----------------------------------------------------" << std::endl;
    for (size_t i = 0; i < nodes.size(); i++) {
        std::cout << nodes[i].first << " -> " << nodes[i].second << std::endl;
        outFile << nodes[i].first << " -> " << nodes[i].second << std::endl;
        if (i == 49 && nodes.size() > 50) {
            std::cout << "... and " << (nodes.size() - 50) << " more words" << std::endl;
            std::cout << "(Full list saved to result/freq.txt)" << std::endl;
        }
    }
    outFile.close();
    std::cout << "\nResults saved to result/freq.txt" << std::endl;
}
