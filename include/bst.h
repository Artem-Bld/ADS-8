// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

template<typename T>
class BST {
 private:
    struct Node {
        T data;
        int count;
        Node* left;
        Node* right;
        Node(const T& value) : data(value), count(1), left(nullptr), right(nullptr) {}
    };
    Node* root;
    Node* insert(Node* node, const T& value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        } else {
            // Слово уже существует - увеличиваем счетчик
            node->count++;
        }
        return node;
    }
    Node* search(Node* node, const T& value) const {
        if (node == nullptr || node->data == value) {
            return node;
        }
        if (value < node->data) {
            return search(node->left, value);
        } else {
            return search(node->right, value);
        }
    }
    int depth(Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        return 1 + std::max(depth(node->left), depth(node->right));
    }
    void clear(Node* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
    void collectNodes(Node* node, std::vector<std::pair<T, int>>& nodes) const {
        if (node != nullptr) {
            collectNodes(node->left, nodes);
            nodes.push_back(std::make_pair(node->data, node->count));
            collectNodes(node->right, nodes);
        }
    }
    
 public:
    BST() : root(nullptr) {}
    ~BST() {
        clear(root);
    }
    void insert(const T& value) {
        root = insert(root, value);
    }
    bool search(const T& value) const {
        return search(root, value) != nullptr;
    }
    int getCount(const T& value) const {
        Node* node = search(root, value);
        return node ? node->count : 0;
    }
    int depth() const {
        return depth(root);
    }
    bool isEmpty() const {
        return root == nullptr;
    }
    std::vector<std::pair<T, int>> getAllNodes() const {
        std::vector<std::pair<T, int>> nodes;
        collectNodes(root, nodes);
        return nodes;
    }
};

#endif  // INCLUDE_BST_H_
