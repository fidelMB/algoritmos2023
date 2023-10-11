/*
Act 3.1 - Operaciones avanzadas en un BST
Fidel Morales Briones A01198630
11 de octubre de 2023
*/

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

        void setData(T data) {
            this->data = data;
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
        * Descripción corta...
        * 
        * @param current: cabeza de la lista
        * @return longitud de la lista
        * Complejidad tiempo: O(n)
        * Complejidad espacio: O(1)
        */
        void insert(T data) {
            root = insertRec(root, data);
        }

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

        // visit
        void visit(int option) {
            // 1. Preorder
            // 2. Inorder
            // 3. Postorder
            // 4. Level by level
            switch (option) {
                case 1:
                    preorder(root);
                    break;
                case 2:
                    inorder(root);
                    break;
                case 3:
                    postorder(root);
                    break;
                case 4:
                    levelbylevel(root);
                    break;
                default:
                    cout << "Invalid option" << endl;
                    break;
            }

        }

        // preorder
        void preorder(Node<T>* node) {
            if (node != nullptr) {
                cout << node->getData() << " ";
                preorder(node->getLeft());
                preorder(node->getRight());
            }
        }

        // inorder
        void inorder(Node<T>* node) {
            if (node != nullptr) {
                inorder(node->getLeft());
                cout << node->getData() << " ";
                inorder(node->getRight());
            }
        }

        // postorder
        void postorder(Node<T>* node) {
            if (node != nullptr) {
                postorder(node->getLeft());
                postorder(node->getRight());
                cout << node->getData() << " ";
            }
        }

        // level by level
        void levelbylevel(Node<T> *node) {
            int h = height(node);
            for (int i = 1; i <= h; i++) {
                printCurrentLevel(node, i);
            }
        }
        
        // Print nodes at a current level
        void printCurrentLevel(Node<T> *node, int level) {
            if (node == nullptr) {
                return;
            }
            if (level == 1) {
                cout << node->getData() << " ";
            }
            else if (level > 1) {
                printCurrentLevel(node->getLeft(), level - 1);
                printCurrentLevel(node->getRight(), level - 1);
            }
        }
        

        // height
        int height(Node<T> *node) {
            if (node == nullptr) {
                return 0;
            }
            else {
                int leftHeight = height(node->getLeft());
                int rightHeight = height(node->getRight());

                if (leftHeight > rightHeight) {
                    return (leftHeight + 1);
                }
                else {
                    return (rightHeight + 1);
                }
            }
        }

        // print ancestors of a node
        bool printAncestors(Node<T> *node, T data) {
            if (node == nullptr) {
                return false;
            }
            if (node->getData() == data) {
                return true;
            }
            if (printAncestors(node->getLeft(), data) || printAncestors(node->getRight(), data)) {
                cout << node->getData() << " ";
                return true;
            }
            return false;
        }

        int getLevelUtil(Node<T> *node, T data, int level)
        {
            if (node == nullptr) {
                return 0;
            }
            if (node->getData() == data) {
                return level;
            }
            int downlevel = getLevelUtil(node->getLeft(), data, level + 1);
            if (downlevel != 0) {
                return downlevel;
            }
            downlevel = getLevelUtil(node->getRight(), data, level + 1);
            return downlevel;
        }
        
        /* Returns level of given data value */
        int getLevel(Node<T>* node, T data)
        {
            return getLevelUtil(node, data, 1);
        }

};

int main() {
    BST<int> bst;
    bst.insert(5);
    bst.insert(3);
    bst.insert(2);
    bst.insert(1);
    bst.insert(0);
    bst.insert(6);
   
  
    bst.visit(4);

    
    return 0;
}


//bibliografia 
//https://www.geeksforgeeks.org/insertion-in-binary-search-tree/
//https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
//https://www.geeksforgeeks.org/get-level-of-a-node-in-a-binary-tree/
// https://www.geeksforgeeks.org/level-order-tree-traversal/
