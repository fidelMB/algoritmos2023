#include <iostream>
using namespace std;

template <class T>
class Node {
    private:
        T data;
        Node<T>* left;
        Node<T>* right;

    public:

        Node(T data) {
            this->data = data;
            this->left = nullptr;
            this->right = nullptr;
        }

        T getData() {
            return data;
        }

        Node<T>* getLeft() {
            return left;
        }

        void setLeft(Node<T>* left) {
            this->left = left;
        }

        Node<T>* getRight() {
            return right;
        }

        void setRight(Node<T>* right) {
            this->right = right;
        }

};

template <class T>
class BST {
    private:
        Node<T>* root;

    public:
        BST() {
            root = nullptr;
        }

        Node<T>* getRoot() {
            return root;
        }

        /*
        * insert, inserta un nuevo nodo en el árbol
        * 
        * Añade un nodo al árbol, utiliza el método recursivo
        * insertRec para encontrar la posición correcta
        * 
        * @param data: dato a insertar
        * @return: no tiene
        * Complejidad tiempo: O(log(n))
        * Complejidad espacio: O(n)
        */
        void insert(T data) {
            root = insertRec(root, data);
        }

        /*
        * insertRec, método recursivo para insertar un nuevo nodo en el árbol
        * 
        * El nodo se actualizará en cada recursión, hasta encontrar la posición
        * correcta para insertar el nuevo nodo, y se regresará el nodo actualizado
        * para definirlo en el método insert
        * 
        * @param data: dato a insertar
        * @param node: nodo actual
        * @return: *Nodo<T> a insertar
        * Complejidad tiempo: O(log(n))
        * Complejidad espacio: O(n)
        */
        Node<T> * insertRec(Node<T>* node, T data) {
            if (node == nullptr) {
                node = new Node<T>(data);
            }
            else {
                if (data < node->getData()) {
                    node->setLeft(insertRec(node->getLeft(), data));
                }
                else {
                    node->setRight(insertRec(node->getRight(), data));
                }
            }
            return node;
        }
};