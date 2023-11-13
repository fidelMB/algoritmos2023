#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

// Función para convertir 4 digitos string de una ip a un número long long
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
        Node<T>* left = nullptr;
        Node<T>* right = nullptr;
        Node<T>* parent = nullptr;
        int access = 0;

    public:
        Node(T data) {
            this->data = data;
            this->left = nullptr;
            this->right = nullptr;
            this->parent = nullptr;
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

        Node<T>* getParent() {
            return parent;
        }

        void setParent(Node<T>* parent) {
            this->parent = parent;
        }

        void addAccess() {
            access++;
        }

        void setData(T data) {
            this->data = data;
        }  

};

template <class T>
class ArbolBiselado {
private:
    Node<T>* root;

    /*
    * rotarIzquierda, operación zig en un árbol
    * 
    * El hijo izquierdo del nodo se convierte en el nuevo padre, el hijo derecho del nuevo padre 
    * se convierte en el hijo izquierdo del padre anterior.
    * 
    * @param nodo: nodo a rotar
    * @return: no tiene
    * Complejidad tiempo: O(1)
    * Complejidad espacio: O(1)
    */   
    void rotarIzquierda(Node<T>* node) {
        Node<T>* y = node->getRight();
        node->setRight(y->getLeft());
        if (y->getLeft() != nullptr) {
            y->getLeft()->setParent(node);
        }
        y->setParent(node->getParent());
        if (node->getParent() == nullptr) {
            this->root = y;
        }
        else if (node == node->getParent()->getLeft()) {
            node->getParent()->setLeft(y);
        }
        else {
            node->getParent()->setRight(y);
        }
        y->setLeft(node);
        node->setParent(y);
    }

    /*
    * rotarDerecha, operación zag en un árbol
    * 
    * El hijo derecho del nodo se convierte en el nuevo padre, el hijo izquierdo del nuevo padre 
    * se convierte en el hijo derecho del padre anterior.
    * 
    * @param nodo: nodo a rotar
    * @return: no tiene
    * Complejidad tiempo: O(1)
    * Complejidad espacio: O(1)
    */   
    void rotarDerecha(Node<T>* node) {
        Node<T>* y = node->getLeft();
        //y es igual al hijo izquierdo
        node->setLeft(y->getRight());
        //l izquierdo del nodo rotado apunta al derecho del hijo izquierdo, balanceo
        if (y->getRight() != nullptr) {
            y->getRight()->setParent(node);
        }
        // si se hizo el balanceo el progenitor es el nuevo padre

        y->setParent(node->getParent());
        // si es raiz actualizar raíz
        if (node->getParent() == nullptr) {
            this->root = y;
        }
        else if (node == node->getParent()->getRight()) {
            // el hijo derecho del padre del nodo es y
            node->getParent()->setRight(y);
        }
        else {
            //el  hijo izquierdo del padre del nodo es y
            node->getParent()->setLeft(y);
        }
        // establece lado derecho
        y->setRight(node);
        // establece padre

        node->setParent(y);
    }

    /*
    * biselar, se bisela un nodo hasta la raíz del árbol
    * 
    * Un nodo se bisela hasta llegar a la raíz. La biselación se logra con las operaciones
    * rotarDerecha y rotarIzquierda, que pueden biselarlo de las maneras:  zig, zag, zig-zag, zag-zig, 
    * zig-zig y zag-zag.
    * 
    * @param nodo: nodo a biselar
    * @return: no tiene
    * Complejidad tiempo: O(log(n))
    * Complejidad espacio: O(1)
    */      
    void biselar(Node<T>* node) {
        while (node->getParent()) {
            if (!node->getParent()->getParent()) {
                if (node == node->getParent()->getLeft()) {
                    // zig
                    rotarDerecha(node->getParent());
                }
                else {
                    // zag 
                    rotarIzquierda(node->getParent());
                }
            }
            else if (node == node->getParent()->getLeft() && node->getParent() == node->getParent()->getParent()->getLeft()) {
                // zig-zig 
                rotarDerecha(node->getParent()->getParent());
                rotarDerecha(node->getParent());
            }
            else if (node == node->getParent()->getRight() && node->getParent() == node->getParent()->getParent()->getRight()) {
                // zag-zag
                rotarIzquierda(node->getParent()->getParent());
                rotarIzquierda(node->getParent());
            }
            else if (node == node->getParent()->getRight() && node->getParent() == node->getParent()->getParent()->getLeft()) {
                // zig-zag 
                rotarIzquierda(node->getParent());
                rotarDerecha(node->getParent());
            }
            else {
                // zag-zig 
                rotarDerecha(node->getParent());
                rotarIzquierda(node->getParent());
            }
        }
    }

public:

    ArbolBiselado() {
        root = nullptr;
    }

    Node<T>* getRoot() {
        return root;
    }

    // search if an element exists inside of the tree
    bool search(T data) {
        Node<T>* current = root;

        while (current != nullptr) {
            if (current->getData() == data) {
                return true;
                biselar(current);
                current->addAccess();
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
    * insert, inserta un nuevo nodo al árbol
    * 
    * Añade un nodo al árbol de la misma forma que un BST, cuando se
    * llega a su posición correcta, se bisela hasta llegar a la raíz
    * 
    * @param key: valor de la ip a instertar
    * @return: no tiene
    * Complejidad tiempo: O(log(n))
    * Complejidad espacio: O(1)
    */
    void insert(T key) {
        Node<T>* node = new Node(key);
        node->setLeft(nullptr);
        node->setRight(nullptr);
        node->setParent(nullptr);
        node->setData(key);
        Node<T>* y = nullptr;
        Node<T>* x = this->root;

        while (x != nullptr) {
            y = x;
            if (node->getData() < x->getData()) {
                x = x->getLeft();
            }
            else {
                x = x->getRight();
            }
        }

        // si  nunca se asignó y  AB vacío
        node->setParent(y);
        if (y == nullptr) {
            root = node;
        }// Si es menor el valor a insertar es hijo izquierdo
        else if (node->getData() < y->getData()) {
            y->setParent(node);
        }// Si es mayor el valor a insertar es hijo derecho
        else {
            y->setRight(node);
        }
        //Biselar el nodo hasta la raíz
        biselar(node);
        // tamanio++;
    }

    void fileToSplayTree(string fileName) {
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
            getline(bitacora, line, '\n');
            if(!search(ipGenerada)) {
                insert(ipGenerada);
            }
    }
        bitacora.close();
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
                cout << node->getData() << " " << endl;
                inorder(node->getRight());
            }
        }

        // busca si existe o no un nodo dentro del árbol
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

        // metodo para cargar las ips al BST
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
                getline(bitacora, line, '\n');
                if(!search(ipGenerada)) {
                    insert(ipGenerada);
                }
            }

            bitacora.close();

        }



};

int main() {

    BST<long long> bst;
    ArbolBiselado<long long> splayTree;
    // bst.fileToBst("bitacoraelb.txt");
    // splayTree.fileToSplayTree("bitacoraelb.txt");
    splayTree.insert(201059175055);
    splayTree.insert(119153136208);
    cout << "BST: " << endl;
    
    clock_t time = clock();
    for (int i = 0; i <= 1000; i++) {
        if (bst.search(255247113032)){
            cout << "Encontrado" << endl;
        }
        else {
            cout << "No encontrado" << endl;
        }
    }
    time = clock() - time;
    cout << "BST: " << (float)time/CLOCKS_PER_SEC << endl;


    


    return 0;
}

