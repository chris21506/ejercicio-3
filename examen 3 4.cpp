#include <iostream>
#include <stack>

using namespace std;

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

class BinarySearchTree {
private:
    Node* root;

    // Función auxiliar InsertRec (con error intencional)
    Node* InsertRec(Node* node, int value) {
        if (node == nullptr)
            return new Node(value);
        // ERROR intencional: debería ser value < node->data
        if (value <= node->data)
            node->left = InsertRec(node->left, value);
        else
            node->right = InsertRec(node->right, value);
        return node;
    }

public:
    BinarySearchTree() {
        root = nullptr;
    }

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
        return nullptr;  // No encontrado
    }

    // Recorrido Post-order iterativo usando dos pilas
    void PostOrderIterative() {
        if (root == nullptr)
            return;

        stack<Node*> stack1, stack2;
        stack1.push(root);

        while (!stack1.empty()) {
            Node* node = stack1.top();
            stack1.pop();
            stack2.push(node);

            if (node->left != nullptr)
                stack1.push(node->left);
            if (node->right != nullptr)
                stack1.push(node->right);
        }

        while (!stack2.empty()) {
            Node* node = stack2.top();
            stack2.pop();
            cout << node->data << " ";
        }
        cout << endl;
    }
};

int main() {
    BinarySearchTree bst;

    // Insertar valores (con duplicados para ver el efecto del error intencional)
    bst.Insert(10);
    bst.Insert(5);
    bst.Insert(15);
    bst.Insert(5);  // Duplicado, se insertará a la izquierda debido al error intencional
    bst.Insert(20);

    // Buscar un valor
    Node* found = bst.Search(15);
    if (found != nullptr)
        cout << "Valor 15 encontrado" << endl;
    else
        cout << "Valor 15 no encontrado" << endl;

    // Recorrido postorder iterativo
    cout << "Recorrido postorder iterativo: ";
    bst.PostOrderIterative();

    return 0;
}
