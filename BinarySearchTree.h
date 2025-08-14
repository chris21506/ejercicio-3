#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream> // Para imprimir datos en consola
#include <stack>    // Para la implementaci�n iterativa de recorridos
#include <cmath>    // Para funciones matem�ticas como log y ceil

using namespace std;

// Clase plantilla para un �rbol Binario de B�squeda
template <typename T>
class BinarySearchTree {
public:

    // Clase interna que representa un nodo del �rbol
    class TreeNode {
    public:
        T data;              // Valor almacenado en el nodo
        TreeNode* parent;    // Puntero al nodo padre
        TreeNode* leftChild; // Puntero al hijo izquierdo
        TreeNode* rightChild;// Puntero al hijo derecho

        // Constructor: inicializa el nodo con un valor y punteros nulos
        TreeNode(T value) : data(value), parent(nullptr), leftChild(nullptr), rightChild(nullptr) {}
    };

    TreeNode* root; // Puntero a la ra�z del �rbol
    int count;      // Cantidad de nodos en el �rbol

    // Constructor: inicializa �rbol vac�o
    BinarySearchTree() : root(nullptr), count(0) {}

    // Destructor: libera memoria de todos los nodos
    ~BinarySearchTree() {
        deleteSubtree(root);
    }

    // Agregar un valor al �rbol
    void Add(T value) {
        // Si el �rbol est� vac�o, creamos el primer nodo como ra�z
        if (!root) {
            root = new TreeNode(value);
            count++;
            return;
        }

        // Si no est� vac�o, recorremos para encontrar su lugar
        TreeNode* current = root;
        while (true) {
            if (value < current->data) { // Ir a la izquierda
                if (!current->leftChild) {
                    InsertNode(current, true, value); // Insertar como hijo izquierdo
                    return;
                }
                current = current->leftChild;
            }
            else if (value > current->data) { // Ir a la derecha
                if (!current->rightChild) {
                    InsertNode(current, false, value); // Insertar como hijo derecho
                    return;
                }
                current = current->rightChild;
            }
            else {
                return; // No insertar valores duplicados
            }
        }
    }

    // Buscar un valor de forma iterativa
    bool SearchIterative(T value) {
        TreeNode* current = root;
        while (current) {
            if (value == current->data) return true; // Encontrado
            if (value < current->data) current = current->leftChild; // Ir a izquierda
            else current = current->rightChild; // Ir a derecha
        }
        return false; // No encontrado
    }

    // Eliminar todos los nodos de un sub�rbol (postorden)
    void deleteSubtree(TreeNode* node) {
        if (!node) return;
        deleteSubtree(node->leftChild);  // Borra
