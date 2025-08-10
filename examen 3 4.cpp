#pragma once

#include <iostream>
#include <stack>
using namespace std;

template <typename T>
class BinarySearchTree
{
    template <typename T>
    class TreeNode
    {
    public:
        TreeNode()
        {
            parent = leftChild = rightChild = nullptr;
            data = {};
        }

        TreeNode(T data)
        {
            parent = leftChild = rightChild = nullptr;
            this->data = data;
        }

        T data;
        TreeNode<T>* parent;
        TreeNode<T>* leftChild;
        TreeNode<T>* rightChild;
    };

public:
    BinarySearchTree()
    {
        root = nullptr;
        count = 0;
    }

    // Inserción recursiva con error intencional (<= en lugar de <)
    void AddWithError(T value)
    {
        if (root == nullptr)
        {
            root = new TreeNode<T>(value);
            count++;
            return;
        }
        root = InsertRec(root, nullptr, value);
    }

    TreeNode<T>* InsertRec(TreeNode<T>* node, TreeNode<T>* parent, T value)
    {
        if (node == nullptr)
        {
            TreeNode<T>* newNode = new TreeNode<T>(value);
            newNode->parent = parent;
            count++;
            return newNode;
        }

        // ERROR intencional: debería ser value < node->data
        if (value <= node->data)
        {
            node->leftChild = InsertRec(node->leftChild, node, value);
        }
        else
        {
            node->rightChild = InsertRec(node->rightChild, node, value);
        }
        return node;
    }

    // Búsqueda iterativa
    TreeNode<T>* SearchIterative(T value)
    {
        TreeNode<T>* current = root;
        while (current != nullptr)
        {
            if (value == current->data)
                return current;
            else if (value < current->data)
                current = current->leftChild;
            else
                current = current->rightChild;
        }
        return nullptr; // no encontrado
    }

    // Recorrido post-order iterativo usando dos pilas
    void PostOrderIterative()
    {
        if (root == nullptr)
            return;

        stack<TreeNode<T>*> stack1, stack2;
        stack1.push(root);

        while (!stack1.empty())
        {
            TreeNode<T>* node = stack1.top();
            stack1.pop();
            stack2.push(node);

            if (node->leftChild != nullptr)
                stack1.push(node->leftChild);
            if (node->rightChild != nullptr)
                stack1.push(node->rightChild);
        }

        while (!stack2.empty())
        {
            TreeNode<T>* node = stack2.top();
            stack2.pop();
            cout << node->data << " ";
        }
        cout << endl;
    }

private:
    TreeNode<T>* root;
    int count;
};
