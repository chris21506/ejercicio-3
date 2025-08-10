#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

class BinarySearchTree {
private:
    Node* root;

public:
    BinarySearchTree() {
        root = nullptr;
    }

    Node* insertNode(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }

        if (value < node->data) {
            node->left = insertNode(node->left, value);
        }
        else if (value > node->data) {
            node->right = insertNode(node->right, value);
        }
        return node;
    }

    void Insert(int value) {
        root = insertNode(root, value);
    }

    Node* SearchIterativo(int value) {
        Node* current = root;
        while (current != nullptr) {
            if (value == current->data) {
                return current;
            }
            else if (value < current->data) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        return nullptr;
    }

    void RecorrerDerecha(Node* node) {
        if (node == nullptr) {
            return;
        }
        RecorrerDerecha(node->right);
        cout << node->data << " ";
        RecorrerDerecha(node->left);
    }

    void RecorrerDerechaDesdeRaiz() {
        RecorrerDerecha(root);
    }
};

int main() {
    BinarySearchTree bst;

    bst.Insert(50);
    bst.Insert(30);
    bst.Insert(70);
    bst.Insert(20);
    bst.Insert(40);
    bst.Insert(60);
    bst.Insert(80);

    Node* found = bst.SearchIterativo(40);
    if (found != nullptr) {
        cout << "Encontrado: " << found->data << endl;
    }
    else {
        cout << "No encontrado" << endl;
    }

    cout << "Recorrido desde la derecha: ";
    bst.RecorrerDerechaDesdeRaiz();
    cout << endl;

    return 0;
}
