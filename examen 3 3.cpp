#pragma once
#include <iostream>
using namespace std;

template <typename T>
class BinarySearchTree {
public:
    struct TreeNode {
        T data;
        TreeNode* parent;
        TreeNode* leftChild;
        TreeNode* rightChild;

        TreeNode(const T& val, TreeNode* p = nullptr)
            : data(val), parent(p), leftChild(nullptr), rightChild(nullptr) {
        }
    };

    BinarySearchTree() : root(nullptr), count(0) {}
    ~BinarySearchTree() { clear(root); }

    // Inserción recursiva pública
    void AddRecursive(const T& value) {
        if (!root) {
            root = new TreeNode(value);
            count++;
        }
        else {
            addRecursive(value, root);
        }
    }

    // Inserción iterativa
    void Add(const T& value) {
        if (!root) {
            root = new TreeNode(value);
            count++;
            return;
        }
        TreeNode* current = root;
        TreeNode* parent = nullptr;
        while (current) {
            parent = current;
            if (value < current->data)
                current = current->leftChild;
            else if (value > current->data)
                current = current->rightChild;
            else
                return; // No permitimos duplicados
        }
        TreeNode* newNode = new TreeNode(value, parent);
        if (value < parent->data)
            parent->leftChild = newNode;
        else
            parent->rightChild = newNode;
        count++;
    }

    // Buscar nodo recursivamente
    bool Search(const T& value) const {
        return (searchRecursive(root, value) != nullptr);
    }

    // Borrar nodo (todos los casos)
    void Delete(const T& value) {
        TreeNode* node = searchRecursive(root, value);
        if (!node) {
            cout << "No existe el valor " << value << " en el árbol.\n";
            return;
        }
        deleteNode(node);
        count--;
    }

    // Recorridos
    void InOrder() const { inOrderRecursive(root); }
    void PreOrder() const { preOrderRecursive(root); }
    void PostOrder() const { postOrderRecursive(root); }

    int Size() const { return count; }
    TreeNode* Root() const { return root; }

private:
    TreeNode* root;
    int count;

    void addRecursive(const T& value, TreeNode* currentNode) {
        if (value < currentNode->data) {
            if (!currentNode->leftChild) {
                currentNode->leftChild = new TreeNode(value, currentNode);
                count++;
            }
            else {
                addRecursive(value, currentNode->leftChild);
            }
        }
        else if (value > currentNode->data) {
            if (!currentNode->rightChild) {
                currentNode->rightChild = new TreeNode(value, currentNode);
                count++;
            }
            else {
                addRecursive(value, currentNode->rightChild);
            }
        }
        // si es igual no hace nada (sin duplicados)
    }

    TreeNode* searchRecursive(TreeNode* node, const T& value) const {
        if (!node) return nullptr;
        if (value == node->data) return node;
        if (value < node->data)
            return searchRecursive(node->leftChild, value);
        else
            return searchRecursive(node->rightChild, value);
    }

    void deleteNode(TreeNode* node) {
        if (!node->leftChild && !node->rightChild) {
            // Sin hijos
            replaceParentChild(node, nullptr);
            delete node;
        }
        else if (node->leftChild && !node->rightChild) {
            // Solo hijo izquierdo
            replaceParentChild(node, node->leftChild);
            delete node;
        }
        else if (!node->leftChild && node->rightChild) {
            // Solo hijo derecho
            replaceParentChild(node, node->rightChild);
            delete node;
        }
        else {
            // Dos hijos: buscar sucesor (mínimo en subárbol derecho)
            TreeNode* successor = minimum(node->rightChild);
            node->data = successor->data; // Copiar dato
            deleteNode(successor); // Eliminar sucesor
        }
    }

    void replaceParentChild(TreeNode* node, TreeNode* newChild) {
        if (!node->parent) {
            root = newChild;
            if (newChild) newChild->parent = nullptr;
        }
        else if (node == node->parent->leftChild) {
            node->parent->leftChild = newChild;
            if (newChild) newChild->parent = node->parent;
        }
        else {
            node->parent->rightChild = newChild;
            if (newChild) newChild->parent = node->parent;
        }
    }

    TreeNode* minimum(TreeNode* node) const {
        while (node->leftChild) node = node->leftChild;
        return node;
    }

    void inOrderRecursive(TreeNode* node) const {
        if (!node) return;
        inOrderRecursive(node->leftChild);
        cout << node->data << " ";
        inOrderRecursive(node->rightChild);
    }

    void preOrderRecursive(TreeNode* node) const {
        if (!node) return;
        cout << node->data << " ";
        preOrderRecursive(node->leftChild);
        preOrderRecursive(node->rightChild);
    }

    void postOrderRecursive(TreeNode* node) const {
        if (!node) return;
        postOrderRecursive(node->leftChild);
        postOrderRecursive(node->rightChild);
        cout << node->data << " ";
    }

    void clear(TreeNode* node) {
        if (!node) return;
        clear(node->leftChild);
        clear(node->rightChild);
        delete node;
    }
};

