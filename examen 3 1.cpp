#include <iostream> // Necesario para std::cout y std::endl
using namespace std;

// Clase Nodo para el árbol binario de búsqueda
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

// Clase BinarySearchTree
class BinarySearchTree {
private:
    Node* root;

public:
    BinarySearchTree() {
        root = nullptr;
    }

    // -------- (1) Función con error intencional corregido --------
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
        return node; // no insertar duplicados
    }

    void Insert(int value) {
        root = insertNode(root, value);
    }

    // -------- (2) Search iterativo --------
    Node* Search(int value) {
        Node* current = root;
        while (current != nullptr) {
            if (value == current->data) {
                return current; // encontrado
            }
            else if (value < current->data) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        return nullptr; // no encontrado
    }

    // -------- (3) Viaje al subárbol izquierdo recursivamente --------
    void TravelLeft(Node* node) {
        if (node == nullptr) {
            return;
        }
        TravelLeft(node->left); // subárbol izquierdo
        print(node->data);      // nodo actual
        TravelLeft(node->right); // subárbol derecho
    }

    void TravelLeftFromRoot() {
        TravelLeft(root);
    }

    void print(int value) {
        cout << value << " ";
    }
};

int main() {
    BinarySearchTree bst;

    // Insertar algunos valores
    bst.Insert(50);
    bst.Insert(30);
    bst.Insert(70);
    bst.Insert(20);
    bst.Insert(40);
    bst.Insert(60);
    bst.Insert(80);

    // Buscar un valor
    Node* found = bst.Search(40);
    if (found != nullptr) {
        cout << "Encontrado: " << found->data << endl;
    }
    else {
        cout << "No encontrado" << endl;
    }

    // Recorrido por el subárbol izquierdo
    cout << "Recorrido in-order: ";
    bst.TravelLeftFromRoot();
    cout << endl;

    return 0;
}
