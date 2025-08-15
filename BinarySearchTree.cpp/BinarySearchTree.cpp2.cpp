// PASO 0: Incluimos iostream para imprimir y nuestro árbol binario de búsqueda
#include <iostream>
#include "BinarySearchTree.h"

int main() {
    // PASO 1: Crear un BST de enteros
    BinarySearchTree<int> bst;

    // PASO 2: Insertar varios valores (con Add iterativo)
    //         Este patrón crea un árbol con ramas a izquierda y derecha
    bst.Add(50);
    bst.Add(30);
    bst.Add(70);
    bst.Add(20);
    bst.Add(40);
    bst.Add(60);
    bst.Add(80);

    // PASO 3: Mostrar recorrido In-Order (recursivo) — debe salir ordenado
    std::cout << "InOrder (recursivo): ";
    bst.InOrderWithRecursive();
    std::cout << "\n";

    // PASO 4: Buscar de forma iterativa (Search)
    std::cout << "Search(40): " << (bst.Search(40) ? "encontrado" : "no encontrado") << "\n";
    std::cout << "Search(99): " << (bst.Search(99) ? "encontrado" : "no encontrado") << "\n";

    // PASO 5: Recorrido Post-Order (iterativo con 2 pilas)
    std::cout << "PostOrder (iterativo): ";
    bst.PostOrderIterative();
    std::cout << "\n";

    // PASO 6: Probar borrados (cubre casos hoja, un hijo y dos hijos)
    //  - hoja
    bst.Delete(20);
    //  - un hijo (según cómo hayan quedado los enlaces)
    bst.Delete(60);
    //  - dos hijos (50 tiene 30 y 70)
    bst.Delete(50);

    std::cout << "InOrder tras borrados: ";
    bst.InOrderWithRecursive();
    std::cout << "\n";

    // PASO 7: Borrar todo el árbol en postorden (Clear -> DeleteSubtree recursiva)
    bst.Clear();
    std::cout << "Arbol limpiado. MinimaAltura(): " << bst.MinimaAltura() << "\n";

    return 0;
}
