#pragma once

#include <iostream>
#include <algorithm>

class AVL_Tree {
public:
    class Node {
    public:
        int value;
        int height;
        Node* left;
        Node* right;

        Node(int value) : value(value), left(nullptr), right(nullptr), height(1) {}
    };

    AVL_Tree() : root(nullptr) {}

    ~AVL_Tree() {
        destroy(root);
    }

    void insert(int value) {
        root = insert(root, value);
    }

    Node* search(int value) {
        return search(root, value);
    }

    void delete_node(int value) {
        root = delete_node(root, value);
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

private:
    Node* root;

    int height(Node* node) {
        return node ? node->height : 0;
    }

    int balance_factor(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void update_height(Node* node) {
        if (node) {
            node->height = 1 + std::max(height(node->left), height(node->right));
        }
    }

    Node* right_rotate(Node* y) {
        Node* x = y->left;
        Node* z = x->right;

        x->right = y;
        y->left = z;

        update_height(y);
        update_height(x);

        return x;
    }

    Node* left_rotate(Node* x) {
        Node* y = x->right;
        Node* z = y->left;

        y->left = x;
        x->right = z;

        update_height(x);
        update_height(y);

        return y;
    }

    Node* insert(Node* node, int value) {
        if (!node) {
            return new Node(value);
        }

        if (value < node->value) {
            node->left = insert(node->left, value);
        }
        else if (value > node->value) {
            node->right = insert(node->right, value);
        }
        else {
            return node; // Дубликаты не допускаются
        }

        update_height(node);

        int balance = balance_factor(node);

        // Левый левый случай
        if (balance > 1 && value < node->left->value) {
            return right_rotate(node);
        }

        // Правый правый случай
        if (balance < -1 && value > node->right->value) {
            return left_rotate(node);
        }

        // Левый правый случай
        if (balance > 1 && value > node->left->value) {
            node->left = left_rotate(node->left);
            return right_rotate(node);
        }

        // Правый левый случай
        if (balance < -1 && value < node->right->value) {
            node->right = right_rotate(node->right);
            return left_rotate(node);
        }

        return node;
    }

    Node* search(Node* node, int value) {
        if (node == nullptr || node->value == value) {
            return node;
        }
        if (value < node->value) {
            return search(node->left, value);
        }
        else {
            return search(node->right, value);
        }
    }
    
    Node* min_value_node(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node* delete_node(Node* node, int value) {
        if (!node) {
            return node;
        }

        if (value < node->value) {
            node->left = delete_node(node->left, value);
        }
        else if (value > node->value) {
            node->right = delete_node(node->right, value);
        }
        else {
            // Узел с одним дочерним элементом или без дочерних элементов
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Узел с двумя дочерними элементами
            Node* temp = min_value_node(node->right);
            node->value = temp->value;
            node->right = delete_node(node->right, temp->value);
        }

        update_height(node);

        int balance = balance_factor(node);

        // Левый левый случай
        if (balance > 1 && balance_factor(node->left) >= 0) {
            return right_rotate(node);
        }

        // Левый правый случай
        if (balance > 1 && balance_factor(node->left) < 0) {
            node->left = left_rotate(node->left);
            return right_rotate(node);
        }

        // Правый правый случай
        if (balance < -1 && balance_factor(node->right) <= 0) {
            return left_rotate(node);
        }

        // Правый левый случай
        if (balance < -1 && balance_factor(node->right) > 0) {
            node->right = right_rotate(node->right);
            return left_rotate(node);
        }

        return node;
    }

    void inorder(Node* node) {
        if (node) {
            inorder(node->left);
            std::cout << node->value << " ";
            inorder(node->right);
        }
    }

    void preorder(Node* node) {
        if (node) {
            std::cout << node->value << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    void postorder(Node* node) {
        if (node) {
            postorder(node->left);
            postorder(node->right);
            std::cout << node->value << " ";
        }
    }

    void destroy(Node* node) {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }
};