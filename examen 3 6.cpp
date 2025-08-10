#include <iostream>
#include <vector>
#include <list>

using namespace std;

// Nodo para BST
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

// Binary Search Tree
class BinarySearchTree {
private:
    Node* root;

    // InsertRec con error intencional (<= en vez de <)
    Node* InsertRec(Node* node, int value) {
        if (node == nullptr)
            return new Node(value);
        if (value <= node->data)   // ERROR intencional aquí
            node->left = InsertRec(node->left, value);
        else
            node->right = InsertRec(node->right, value);
        return node;
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void Insert(int value) {
        root = InsertRec(root, value);
    }

    // Search iterativo
    Node* Search(int value) {
        Node* current = root;
        while (current != nullptr) {
            if (value == current->data)
                return current;
            else if (value < current->data)
                current = current->left;
            else
                current = current->right;
        }
        return nullptr;
    }

    // Método para imprimir InOrder (útil para probar)
    void InOrder(Node* node) {
        if (node == nullptr) return;
        InOrder(node->left);
        cout << node->data << " ";
        InOrder(node->right);
    }

    void PrintInOrder() {
        InOrder(root);
        cout << endl;
    }
};

// Clase base HashTableChaining simplificada para ejemplo
class HashTableChaining {
protected:
    static const int SIZE = 10;
    vector<list<int>> table;

public:
    HashTableChaining() {
        table.resize(SIZE);
    }

    virtual void Insert(int key) {
        int index = key % SIZE;
        table[index].push_back(key);
    }

    virtual bool Contains(int key) {
        int index = key % SIZE;
        for (int val : table[index]) {
            if (val == key) return true;
        }
        return false;
    }

    virtual void Remove(int key) {
        int index = key % SIZE;
        table[index].remove(key);
    }

    int Size() {
        int count = 0;
        for (auto& chain : table)
            count += chain.size();
        return count;
    }
};

// HashSet que hereda HashTableChaining y evita duplicados
class HashSet : public HashTableChaining {
public:
    HashSet() : HashTableChaining() {}

    void Insert(int key) override {
        if (!Contains(key)) {
            HashTableChaining::Insert(key);
        }
    }
};

int main() {
    cout << "Binary Search Tree con error intencional en Insert:" << endl;
    BinarySearchTree bst;
    bst.Insert(10);
    bst.Insert(5);
    bst.Insert(15);
    bst.Insert(5); // duplicado se inserta a la izquierda (por el error intencional)
    bst.Insert(20);
    bst.PrintInOrder();

    Node* found = bst.Search(15);
    if (found)
        cout << "Valor 15 encontrado en BST." << endl;
    else
        cout << "Valor 15 NO encontrado en BST." << endl;

    cout << "\nHashSet que evita duplicados:" << endl;
    HashSet set;
    set.Insert(5);
    set.Insert(10);
    set.Insert(5);  // No se inserta
    set.Insert(15);

    cout << "Tamaño del HashSet: " << set.Size() << endl;  // Debe ser 3

    cout << "Contiene 10? " << (set.Contains(10) ? "Sí" : "No") << endl;
    cout << "Contiene 7? " << (set.Contains(7) ? "Sí" : "No") << endl;

    return 0;
}
