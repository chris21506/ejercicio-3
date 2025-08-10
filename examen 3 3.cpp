#include <iostream>
using namespace std;

class Nodo {
public:
    int dato;
    Nodo* izquierdo;
    Nodo* derecho;

    Nodo(int valor) {
        dato = valor;
        izquierdo = nullptr;
        derecho = nullptr;
    }
};

class BinarySearchTree {
private:
    Nodo* raiz;

    Nodo* insertarNodo(Nodo* nodo, int valor) {
        if (nodo == nullptr) {
            return new Nodo(valor);
        }
        if (valor < nodo->dato) {
            nodo->izquierdo = insertarNodo(nodo->izquierdo, valor);
        }
        else if (valor > nodo->dato) {
            nodo->derecho = insertarNodo(nodo->derecho, valor);
        }
        return nodo;
    }

    Nodo* encontrarMinimo(Nodo* nodo) {
        while (nodo->izquierdo != nullptr) {
            nodo = nodo->izquierdo;
        }
        return nodo;
    }

    Nodo* borrarNodo(Nodo* nodo, int valor) {
        if (nodo == nullptr) return nullptr;

        if (valor < nodo->dato) {
            nodo->izquierdo = borrarNodo(nodo->izquierdo, valor);
        }
        else if (valor > nodo->dato) {
            nodo->derecho = borrarNodo(nodo->derecho, valor);
        }
        else {
            // Caso 1: sin hijos
            if (nodo->izquierdo == nullptr && nodo->derecho == nullptr) {
                delete nodo;
                return nullptr;
            }
            // Caso 2: un hijo
            if (nodo->izquierdo == nullptr) {
                Nodo* temp = nodo->derecho;
                delete nodo;
                return temp;
            }
            if (nodo->derecho == nullptr) {
                Nodo* temp = nodo->izquierdo;
                delete nodo;
                return temp;
            }
            // Caso 3: dos hijos
            Nodo* sucesor = encontrarMinimo(nodo->derecho);
            nodo->dato = sucesor->dato;
            nodo->derecho = borrarNodo(nodo->derecho, sucesor->dato);
        }
        return nodo;
    }

public:
    BinarySearchTree() {
        raiz = nullptr;
    }

    void Insertar(int valor) {
        raiz = insertarNodo(raiz, valor);
    }

    Nodo* BuscarIterativo(int valor) {
        Nodo* actual = raiz;
        while (actual != nullptr) {
            if (valor == actual->dato) return actual;
            else if (valor < actual->dato) actual = actual->izquierdo;
            else actual = actual->derecho;
        }
        return nullptr;
    }

    void Borrar(int valor) {
        raiz = borrarNodo(raiz, valor);
    }

    void InOrden(Nodo* nodo) {
        if (nodo != nullptr) {
            InOrden(nodo->izquierdo);
            cout << nodo->dato << " ";
            InOrden(nodo->derecho);
        }
    }

    void Mostrar() {
        InOrden(raiz);
        cout << endl;
    }
};

int main() {
    BinarySearchTree bst;
    bst.Insertar(50);
    bst.Insertar(30);
    bst.Insertar(70);
    bst.Insertar(20);
    bst.Insertar(40);
    bst.Insertar(60);
    bst.Insertar(80);

    cout << "Arbol en orden: ";
    bst.Mostrar();

    bst.Borrar(70);
    cout << "Tras borrar 70: ";
    bst.Mostrar();

    return 0;
}

