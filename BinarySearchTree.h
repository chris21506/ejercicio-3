#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>
#include <stack>
#include <cmath>

using namespace std;

template <typename T>
class BinarySearchTree {
public:
    class TreeNode {
    public:
        T data;
        TreeNode* parent;
        TreeNode* leftChild;
        TreeNode* rightChild;

        TreeNode(T value) : data(value), parent(nullptr), leftChild(nullptr), rightChild(nullptr) {}
    };

    TreeNode* root;
    int count;

    BinarySearchTree() : root(nullptr), count(0) {}
    ~BinarySearchTree() {
        deleteSubtree(root);
    }

    void Add(T value) {
        if (!root) {
            root = new TreeNode(value);
            count++;
            return;
        }
        TreeNode* current = root;
        while (true) {
            if (value < current->data) {
                if (!current->leftChild) {
                    InsertNode(current, true, value);
                    return;
                }
                current = current->leftChild;
            }
            else if (value > current->data) {
                if (!current->rightChild) {
                    InsertNode(current, false, value);
                    return;
                }
                current = current->rightChild;
            }
            else {
                return; // valor duplicado
            }
        }
    }

    bool SearchIterative(T value) {
        TreeNode* current = root;
        while (current) {
            if (value == current->data) return true;
            if (value < current->data) current = current->leftChild;
            else current = current->rightChild;
        }
        return false;
    }

    void deleteSubtree(TreeNode* node) {
        if (!node) return;
        deleteSubtree(node->leftChild);
        deleteSubtree(node->rightChild);
        delete node;
        count--;
    }

    void PostOrderIterative() {
        if (!root) return;
        stack<TreeNode*> s1, s2;
        s1.push(root);
        while (!s1.empty()) {
            TreeNode* node = s1.top(); s1.pop();
            s2.push(node);
            if (node->leftChild) s1.push(node->leftChild);
            if (node->rightChild) s1.push(node->rightChild);
        }
        while (!s2.empty()) {
            cout << s2.top()->data << " ";
            s2.pop();
        }
        cout << endl;
    }

    int MinimaAltura() const {
        return MinimaAlturaDeArbol(count, 2);
    }

private:
    void InsertNode(TreeNode* parentNode, bool isLeft, T value) {
        TreeNode* newNode = new TreeNode(value);
        newNode->parent = parentNode;
        if (isLeft) parentNode->leftChild = newNode;
        else parentNode->rightChild = newNode;
        count++;
    }

    static double log_base_n(double x, double base) {
        return log(x) / log(base);
    }

    static int MinimaAlturaDeArbol(int numeroDeNodos, int maxHijos) {
        int h = ceil(log_base_n((maxHijos - 1) * numeroDeNodos + 1, maxHijos)) - 1;
        return h;
    }
};

#endif // BINARYSEARCHTREE_H
