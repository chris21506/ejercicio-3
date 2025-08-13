#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

int main() {
    // Crear un árbol binario de enteros
    BinarySearchTree<int> bst;

    // Insertar algunos valores
    bst.Add(50);
    bst.Add(30);
    bst.Add(70);
    bst.Add(20);
    bst.Add(40);
    bst.Add(60);
    bst.Add(80);

    // Buscar valores
    cout << "Buscando 40: " << (bst.SearchIterative(40) ? "Encontrado" : "No encontrado") << endl;
    cout << "Buscando 25: " << (bst.SearchIterative(25) ? "Encontrado" : "No encontrado") << endl;

    // Mostrar recorrido post-order iterativo
    cout << "Recorrido Post-order: ";
    bst.PostOrderIterative();

    // Borrar subárbol izquierdo del nodo raíz (ejemplo)
    if (bst.root && bst.root->leftChild) {
        bst.deleteSubtree(bst.root->leftChild);
        bst.root->leftChild = nullptr;
    }

    // Mostrar recorrido post-order después de borrar
    cout << "Post-order después de borrar subárbol izquierdo: ";
    bst.PostOrderIterative();

    // Altura mínima del árbol
    cout << "Altura mínima del árbol: " << bst.MinimaAltura() << endl;

    return 0;
}

