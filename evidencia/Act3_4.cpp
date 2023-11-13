#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

long long ipToLong(string ip1, string ip2, string ip3, string ip4) {
	string current, ip = "";
	vector<string> ips = { ip1, ip2, ip3, ip4 };

	if (ips[0][0] == ' ')
		ips[0].erase(0, 1);

	for (int i = 0; i < 4; i++)
	{
		current = ips[i];

		if (current.length() == 1) {
			ip += "00" + current;
		}
		else if (current.length() == 2) {
			ip += "0" + current;
		}
		else {
			ip += current;
		}
	}
	
	return stoll(ip);
}

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
        * inorder, recorrido en inorder del árbol
        * 
        * Con recursión, se imprimen los datos del árbol en orden ascendente.
        * Recorre el subárbol izquierdo, después la raíz, y finalmente el subárbol derecho
        * 
        * @param node: nodo raíz del árbol
        * @return: en la terminal, se imprimirá el recorrido
        * Complejidad tiempo: O(n)
        * Complejidad espacio: O(n)
        */
        void inorder(Node<T>* node) {
            if (node != nullptr) {
                inorder(node->getLeft());
                cout << node->getData() << " ";
                inorder(node->getRight());
            }
        }

        // search if a node already exists inside the binary tree
        bool search(T data) {
            Node<T>* current = root;

            while (current != nullptr) {
                if (current->getData() == data) {
                    return true;
                }
                else if (data < current->getData()) {
                    current = current->getLeft();
                }
                else {
                    current = current->getRight();
                }
            }
            return false;
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

        void fileToBst(string fileName) {
            fstream bitacora;
            string line, ip1, ip2, ip3, ip4;
            long long ipGenerada;
            
            bitacora.open(fileName, ios::in);

            while (getline(bitacora, line, 'P')) {
                getline(bitacora, line, ' ');
                getline(bitacora, ip1, '.');
                getline(bitacora, ip2, '.');
                getline(bitacora, ip3, '.');
                getline(bitacora, ip4, ' ');
                ipGenerada = ipToLong(ip1, ip2, ip3, ip4);
            // convierte las partes de la ip en un valor numerico
                getline(bitacora, line, '\n');
            // agrega “temp” al vector “v”
                if(!search(ipGenerada)) {
                    insert(ipGenerada);
                }
            }

            bitacora.close();

        }



};

int main() {

    BST<long long> bst;
    bst.fileToBst("prueba.txt");

    bst.inorder(bst.getRoot());
    return 0;
}

