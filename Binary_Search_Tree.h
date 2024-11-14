#pragma once

#include <iostream>

struct Data {
    int phone;
    string name;
};

class Binary_Search_Tree {
public:
    class Node {
    public:
        Data value;
        Node* left;
        Node* right;

        Node(Data value) : value(value), left(nullptr), right(nullptr) {}
    };

    Binary_Search_Tree() : root(nullptr) {}

    ~Binary_Search_Tree() {
        destroy(root);
    }

    void insert(Data value) {
        insert(root, value);
    }

    void inorder() {
        inorder(root);
        std::cout << std::endl;
    }

    void preorder() {
        preorder(root);
        std::cout << std::endl;
    }

    void postorder() {
        postorder(root);
        std::cout << std::endl;
    }

    Node* search(string name) {
        return search(root, name);
    }

    Node* delete_node(Node* node, Data value) {
        if (node == nullptr) {
            return node;
        }

        if (value.name < node->value.name) {
            node->left = delete_node(node->left, value);
        }
        else if (value.name > node->value.name) {
            node->right = delete_node(node->right, value);
        }
        else {
            // ”зел с одним дочерним узлом или без дочерних узлов
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // ”зел с двум€ дочерними узлами: получить минимальный узел из правого поддерева
            Node* temp = min_value_node(node->right);
            node->value = temp->value; //  опируем значение минимального узла
            node->right = delete_node(node->right, temp->value); // ”дал€ем минимальный узел
        }
        return node;
    }

private:
    Node* root;

    void insert(Node*& node, Data value) {
        if (node == nullptr) {
            node = new Node(value);
        }
        else if (value.name < node->value.name) {
            insert(node->left, value);
        }
        else {
            insert(node->right, value);
        }
    }

    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);
            std::cout << node->value.name << " ";
            inorder(node->right);
        }
    }

    void preorder(Node* node) {
        if (node != nullptr) {
            std::cout << node->value.name << " ";
            inorder(node->left);
            inorder(node->right);
        }
    }

    void postorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);
            inorder(node->right);
            std::cout << node->value.name << " ";
        }
    }

    Node* search(Node* node, string name) {
        if (node == nullptr || node->value.name == name) {
            return node;
        }
        if (name < node->value.name) {
            return search(node->left, name);
        }
        else {
            return search(node->right, name);
        }
    }

    Node* min_value_node(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    void destroy(Node* node) {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }
};