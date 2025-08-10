#pragma once

#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class BinarySearchTree
{
private:
    // Nodo del árbol
    class TreeNode
    {
    public:
        T data;
        TreeNode* parent;
        TreeNode* leftChild;
        TreeNode* rightChild;

        TreeNode(const T& value)
            : data(value), parent(nullptr), leftChild(nullptr), rightChild(nullptr)
        {
        }
    };

    TreeNode* root;
    int count;

public:
    BinarySearchTree() : root(nullptr), count(0) {}

    ~BinarySearchTree() {
        Clear(root);
    }

    // Inserción recursiva pública
    void AddWithAddRecursive(const T& value) {
        if (!root) {
            root = new TreeNode(value);
            count++;
            return;
        }
        AddRecursive(root, value);
    }

    // Inserción iterativa
    void Add(const T& value) {
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
                // No insertamos duplicados
                return;
            }
        }
    }

    // Búsqueda recursiva
    bool SearchWithRecursive(const T& value) {
        return SearchRecursive(root, value) != nullptr;
    }

    // Eliminación
    void Delete(const T& value) {
        TreeNode* nodeToDelete = SearchRecursive(root, value);
        if (!nodeToDelete) {
            cout << "No existe el valor " << value << " en el árbol.\n";
            return;
        }
        DeleteNode(nodeToDelete);
    }

    // Recorridos
    void InOrder() {
        InOrderRecursive(root);
    }

    void PreOrder() {
        PreOrderRecursive(root);
    }

    void PostOrder() {
        PostOrderRecursive(root);
    }

    // Obtener el mínimo y máximo valor del árbol
    T Minimum() {
        TreeNode* minNode = Minimum(root);
        if (!minNode) throw runtime_error("Árbol vacío");
        return minNode->data;
    }

    T Maximum() {
        TreeNode* maxNode = Maximum(root);
        if (!maxNode) throw runtime_error("Árbol vacío");
        return maxNode->data;
    }

    // Obtener sucesor de un valor (si existe)
    T Successor(const T& value) {
        TreeNode* node = SearchRecursive(root, value);
        if (!node) throw runtime_error("Valor no encontrado en el árbol");

        TreeNode* succ = Successor(node);
        if (!succ) throw runtime_error("No existe sucesor para este valor");

        return succ->data;
    }

    int Size() const {
        return count;
    }

private:
    void InsertNode(TreeNode* parentNode, bool isLeftChild, const T& value) {
        TreeNode* newNode = new TreeNode(value);
        newNode->parent = parentNode;
        if (isLeftChild)
            parentNode->leftChild = newNode;
        else
            parentNode->rightChild = newNode;
        count++;
    }

    void AddRecursive(TreeNode* currentNode, const T& value) {
        if (value < currentNode->data) {
            if (!currentNode->leftChild)
                InsertNode(currentNode, true, value);
            else
                AddRecursive(currentNode->leftChild, value);
        }
        else if (value > currentNode->data) {
            if (!currentNode->rightChild)
                InsertNode(currentNode, false, value);
            else
                AddRecursive(currentNode->rightChild, value);
        }
        // No se insertan duplicados
    }

    TreeNode* SearchRecursive(TreeNode* node, const T& value) {
        if (!node) return nullptr;
        if (value == node->data) return node;
        if (value < node->data) return SearchRecursive(node->leftChild, value);
        else return SearchRecursive(node->rightChild, value);
    }

    void DeleteNode(TreeNode* node) {
        // Caso 1: Nodo hoja
        if (!node->leftChild && !node->rightChild) {
            if (!node->parent) {
                // Es la raíz
                delete node;
                root = nullptr;
            }
            else {
                if (node->parent->leftChild == node)
                    node->parent->leftChild = nullptr;
                else
                    node->parent->rightChild = nullptr;
                delete node;
            }
            count--;
        }
        // Caso 2: Un solo hijo
        else if (!node->leftChild || !node->rightChild) {
            TreeNode* child = node->leftChild ? node->leftChild : node->rightChild;
            if (!node->parent) {
                // Nodo raíz con un solo hijo
                root = child;
                child->parent = nullptr;
                delete node;
            }
            else {
                if (node->parent->leftChild == node)
                    node->parent->leftChild = child;
                else
                    node->parent->rightChild = child;
                child->parent = node->parent;
                delete node;
            }
            count--;
        }
        // Caso 3: Dos hijos
        else {
            TreeNode* succ = Successor(node);
            node->data = succ->data;
            DeleteNode(succ);
        }
    }

    TreeNode* Minimum(TreeNode* node) {
        if (!node) return nullptr;
        while (node->leftChild)
            node = node->leftChild;
        return node;
    }

    TreeNode* Maximum(TreeNode* node) {
        if (!node) return nullptr;
        while (node->rightChild)
            node = node->rightChild;
        return node;
    }

    TreeNode* Successor(TreeNode* node) {
        if (node->rightChild)
            return Minimum(node->rightChild);

        TreeNode* ancestor = node->parent;
        while (ancestor && node == ancestor->rightChild) {
            node = ancestor;
            ancestor = ancestor->parent;
        }
        return ancestor;
    }

    void InOrderRecursive(TreeNode* node) {
        if (!node) return;
        InOrderRecursive(node->leftChild);
        cout << node->data << " ";
        InOrderRecursive(node->rightChild);
    }

    void PreOrderRecursive(TreeNode* node) {
        if (!node) return;
        cout << node->data << " ";
        PreOrderRecursive(node->leftChild);
        PreOrderRecursive(node->rightChild);
    }

    void PostOrderRecursive(TreeNode* node) {
        if (!node) return;
        PostOrderRecursive(node->leftChild);
        PostOrderRecursive(node->rightChild);
        cout << node->data << " ";
    }

    void Clear(TreeNode* node) {
        if (!node) return;
        Clear(node->leftChild);
        Clear(node->rightChild);
        delete node;
    }
};
