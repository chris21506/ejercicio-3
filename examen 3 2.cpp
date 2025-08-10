#pragma once

#include <iostream>
using namespace std;

#include <cmath> // Para funciones matemáticas si necesitas (ej. log)

double log_base_n(double x, double base);

int MinimaAlturaDeArbol(int numeroDeNodos, int maximoDeHijosPorNodo);

template <typename T>
class BinarySearchTree
{
    // Clase anidada para nodo del árbol
    template <typename U>
    class TreeNode
    {
    public:
        TreeNode()
        {
            parent = leftChild = rightChild = nullptr;
            data = {};
        }

        TreeNode(U data)
        {
            parent = leftChild = rightChild = nullptr;
            this->data = data;
        }

        U data;
        TreeNode<U>* parent;
        TreeNode<U>* leftChild;
        TreeNode<U>* rightChild;
    };

public:
    BinarySearchTree()
    {
        root = nullptr;
        count = 0;
    }

    void AddWithAddRecursive(T value)
    {
        if (root == nullptr)
        {
            root = new TreeNode<T>(value);
            count++;
            return;
        }
        AddRecursive(value, root);
    }

    void InsertarNode(TreeNode<T>* currentNode, bool isLeftChild, T value)
    {
        TreeNode<T>* newNode = new TreeNode<T>(value);
        newNode->parent = currentNode;
        if (isLeftChild)
            currentNode->leftChild = newNode;
        else
            currentNode->rightChild = newNode;
        count++;
    }

    void AddRecursive(T value, TreeNode<T>* currentNode)
    {
        if (value > currentNode->data)
        {
            if (currentNode->rightChild == nullptr)
            {
                InsertarNode(currentNode, false, value);
                return;
            }
            AddRecursive(value, currentNode->rightChild);
        }
        else if (value < currentNode->data)
        {
            if (currentNode->leftChild == nullptr)
            {
                InsertarNode(currentNode, true, value);
                return;
            }
            AddRecursive(value, currentNode->leftChild);
        }
    }

    void Add(T value)
    {
        if (root == nullptr)
        {
            root = new TreeNode<T>(value);
            count++;
            return;
        }

        TreeNode<T>* currentNode = root;

        while (currentNode != nullptr)
        {
            if (value > currentNode->data)
            {
                if (currentNode->rightChild == nullptr)
                {
                    InsertarNode(currentNode, false, value);
                    return;
                }
                currentNode = currentNode->rightChild;
            }
            else if (value < currentNode->data)
            {
                if (currentNode->leftChild == nullptr)
                {
                    InsertarNode(currentNode, true, value);
                    return;
                }
                currentNode = currentNode->leftChild;
            }
            else
            {
                // Valor duplicado: no inserta nada
                return;
            }
        }
    }

    void InOrderWithRecursive()
    {
        InOrderRecursive(root);
    }

    int MinimaAltura()
    {
        return MinimaAlturaDeArbol(count, 2);
    }

    bool SearchWithRecursive(T value)
    {
        TreeNode<T>* resultNode = SearchRecursive(root, value);
        return resultNode != nullptr;
    }

    void Delete(T value)
    {
        TreeNode<T>* nodeToDelete = SearchRecursive(root, value);
        if (nodeToDelete == nullptr)
        {
            cout << "No existe el valor " << value << " en este árbol." << endl;
            return;
        }

        // Caso 1: Nodo sin hijos
        if (nodeToDelete->leftChild == nullptr && nodeToDelete->rightChild == nullptr)
        {
            if (nodeToDelete->parent != nullptr)
            {
                if (nodeToDelete->parent->leftChild == nodeToDelete)
                    nodeToDelete->parent->leftChild = nullptr;
                else
                    nodeToDelete->parent->rightChild = nullptr;
            }
            else
            {
                // Nodo raíz sin hijos
                root = nullptr;
            }
            delete nodeToDelete;
            count--;
            return;
        }

        // Caso 2: Nodo con un solo hijo derecho
        if (nodeToDelete->leftChild == nullptr && nodeToDelete->rightChild != nullptr)
        {
            if (nodeToDelete->parent != nullptr)
            {
                if (nodeToDelete->parent->leftChild == nodeToDelete)
                    nodeToDelete->parent->leftChild = nodeToDelete->rightChild;
                else
                    nodeToDelete->parent->rightChild = nodeToDelete->rightChild;
            }
            else
            {
                root = nodeToDelete->rightChild;
            }
            nodeToDelete->rightChild->parent = nodeToDelete->parent;
            delete nodeToDelete;
            count--;
            return;
        }

        // Caso 3: Nodo con un solo hijo izquierdo
        if (nodeToDelete->leftChild != nullptr && nodeToDelete->rightChild == nullptr)
        {
            if (nodeToDelete->parent != nullptr)
            {
                if (nodeToDelete->parent->leftChild == nodeToDelete)
                    nodeToDelete->parent->leftChild = nodeToDelete->leftChild;
                else
                    nodeToDelete->parent->rightChild = nodeToDelete->leftChild;
            }
            else
            {
                root = nodeToDelete->leftChild;
            }
            nodeToDelete->leftChild->parent = nodeToDelete->parent;
            delete nodeToDelete;
            count--;
            return;
        }

        // Caso 4: Nodo con dos hijos
        TreeNode<T>* successorNode = Successor(nodeToDelete);
        // Reasignar hijos y padres
        if (successorNode->parent != nodeToDelete)
        {
            if (successorNode->parent->leftChild == successorNode)
                successorNode->parent->leftChild = successorNode->rightChild;
            else
                successorNode->parent->rightChild = successorNode->rightChild;

            if (successorNode->rightChild != nullptr)
                successorNode->rightChild->parent = successorNode->parent;

            successorNode->rightChild = nodeToDelete->rightChild;
            nodeToDelete->rightChild->parent = successorNode;
        }

        successorNode->leftChild = nodeToDelete->leftChild;
        nodeToDelete->leftChild->parent = successorNode;

        successorNode->parent = nodeToDelete->parent;

        if (nodeToDelete->parent != nullptr)
        {
            if (nodeToDelete->parent->leftChild == nodeToDelete)
                nodeToDelete->parent->leftChild = successorNode;
            else
                nodeToDelete->parent->rightChild = successorNode;
        }
        else
        {
            root = successorNode;
        }

        delete nodeToDelete;
        count--;
    }

private:
    TreeNode<T>* root;
    int count;

    TreeNode<T>* SearchRecursive(TreeNode<T>* currentNode, T value)
    {
        if (currentNode == nullptr) return nullptr;
        if (currentNode->data == value) return currentNode;

        if (value < currentNode->data)
            return SearchRecursive(currentNode->leftChild, value);
        else
            return SearchRecursive(currentNode->rightChild, value);
    }

    void InOrderRecursive(TreeNode<T>* node)
    {
        if (node != nullptr)
        {
            InOrderRecursive(node->leftChild);
            cout << node->data << endl;
            InOrderRecursive(node->rightChild);
        }
    }

    TreeNode<T>* Minimum(TreeNode<T>* node)
    {
        TreeNode<T>* current = node;
        while (current->leftChild != nullptr)
            current = current->leftChild;
        return current;
    }

    TreeNode<T>* Successor(TreeNode<T>* node)
    {
        if (node->rightChild != nullptr)
            return Minimum(node->rightChild);

        TreeNode<T>* ancestor = node->parent;
        while (ancestor != nullptr && node == ancestor->rightChild)
        {
            node = ancestor;
            ancestor = ancestor->parent;
        }
        return ancestor;
    }
};
