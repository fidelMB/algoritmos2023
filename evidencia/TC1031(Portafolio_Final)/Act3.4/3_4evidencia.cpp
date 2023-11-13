/*
Act 3.4 - Actividad Integral de BST (Evidencia Competencia)
Integrantes:
Andrés Emiliano de la Garza Rosales A01384096
Rodrigo de Jesús Meléndez Molina A00831646
Fidel Morales Briones A01198630
19 de octubre de 2023
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

/*
* Convertir ip's a tipo de variable long long
*
* Función que se utiliza para convertir la dirección IP
* representada por strings a un número largo representado por
* un valor numérico
* 
* @param ip1 ip2 ip3 ip4: cuatro strings con los valores de una IP
* @return una IP en tipo de variable long long
* Tiempo: O(1)
* Espacio: O(1)
*/
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

/*
* timeTest, se utiliza para los casos de prueba de los árboles
* 
* Se escoge el árbol en donde se van a realizar las búsquedas, se lee el archivo 
* que contiene una lista de ips que se van a buscar, las ips se convierten a long long
* y se realiza la búsqueda de cada una dentro del árbol correspondiente. También se iprime el tiempo que tardó
* en completarse la búsqueda.
* 
* @param tree: árbol en donde se van a realizar las búsquedas
* @param filename: nombe del archivo txt
* @param treeName: nombre del árbol
* @return: no tiene
* Complejidad tiempo: O(nlog(n))
* Complejidad espacio: O(1)
*/     
template <class T>
void timeTest(T tree, string fileName, string treeName) {
    clock_t time;
    fstream bitacora;
    string line, ip1, ip2, ip3, ip4;
    long long ipGenerada;

    bitacora.open(fileName, ios::in);

    time = clock();
    while (getline(bitacora, line, 'P')) {
        getline(bitacora, line, ' ');
        getline(bitacora, ip1, '.');
        getline(bitacora, ip2, '.');
        getline(bitacora, ip3, '.');
        getline(bitacora, ip4, ' ');
        ipGenerada = ipToLong(ip1, ip2, ip3, ip4);
        getline(bitacora, line, '\n');
        
        tree.search(ipGenerada);
    }
    time = clock() - time;
    cout << treeName << (float)time / CLOCKS_PER_SEC << " segundos" << endl;

    bitacora.close();
}

template <class T>
class Node {
private:
    T data;
    Node<T>* left;
    Node<T>* right;
    Node<T>* parent;
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

    int getAccess() {
        return access;
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

};

template <class T>
class ArbolBiselado {
private:
    Node<T>* root;

    /*
    * rotateLeft, operación zig en un árbol
    *
    * El hijo izquierdo del nodo se convierte en el nuevo padre, el hijo derecho del nuevo padre
    * se convierte en el hijo izquierdo del padre anterior.
    *
    * @param node: nodo a rotar
    * @return: no tiene
    * Complejidad tiempo: O(1)
    * Complejidad espacio: O(1)
    */
    void rotateLeft(Node<T>* node) {
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
    * rotateRight, operación zag en un árbol
    *
    * El hijo derecho del nodo se convierte en el nuevo padre, el hijo izquierdo del nuevo padre
    * se convierte en el hijo derecho del padre anterior.
    *
    * @param node: nodo a rotar
    * @return: no tiene
    * Complejidad tiempo: O(1)
    * Complejidad espacio: O(1)
    */
    void rotateRight(Node<T>* node) {
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
    * splay, se bisela un nodo hasta la raíz del árbol
    *
    * Un nodo se bisela hasta llegar a la raíz. La biselación se logra con las operaciones
    * rotateRight y rotateLeft, que pueden biselarlo de las maneras:  zig, zag, zig-zag, zag-zig,
    * zig-zig y zag-zag.
    *
    * @param node: nodo a biselar
    * @return: no tiene
    * Complejidad tiempo: O(log(n))
    * Complejidad espacio: O(1)
    */
    void splay(Node<T>* node) {
        while (node->getParent()) {
            if (!node->getParent()->getParent()) {
                if (node == node->getParent()->getLeft()) {
                    // zig
                    rotateRight(node->getParent());
                }
                else {
                    // zag 
                    rotateLeft(node->getParent());
                }
            }
            else if (node == node->getParent()->getLeft() && node->getParent() == node->getParent()->getParent()->getLeft()) {
                // zig-zig 
                rotateRight(node->getParent()->getParent());
                rotateRight(node->getParent());
            }
            else if (node == node->getParent()->getRight() && node->getParent() == node->getParent()->getParent()->getRight()) {
                // zag-zag
                rotateLeft(node->getParent()->getParent());
                rotateLeft(node->getParent());
            }
            else if (node == node->getParent()->getRight() && node->getParent() == node->getParent()->getParent()->getLeft()) {
                // zig-zag 
                rotateLeft(node->getParent());
                rotateRight(node->getParent());
            }
            else {
                // zag-zig 
                rotateRight(node->getParent());
                rotateLeft(node->getParent());
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

    /*
    * search, búsqueda de un nodo en el árbol biselado
    * 
    * Se realiza una búsqueda binaria hasta encontrar el nodo solicitado, se regresa true si se encuentra
    * y se bisela hasta la raíz, si no se encuentra, se regresa false.
    * 
    * @param data: dato a buscar
    * @return: booleano, true si se encuentra, false si no
    * Complejidad tiempo: O(log(n))
    * Complejidad espacio: O(1)
    */ 
    bool search(T data) {   
        if (root->getData() == data) {
            root->addAccess();
            return true;
        }

        Node<T>* current = root;

        while (current != nullptr) {
            if (current->getData() == data) {
                splay(current);
                current->addAccess();
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
    * insert, inserta un nuevo nodo al árbol
    *
    * Añade un nodo al árbol de la misma forma que un BST, cuando se
    * llega a su posición correcta, se bisela hasta llegar a la raíz.
    *
    * @param key: valor de la ip a instertar
    * @return: no tiene
    * Complejidad tiempo: O(log(n))
    * Complejidad espacio: O(1)
    */
    void insert(T key) {
        Node<T>* node = new Node<T>(key);

        Node<T>* y = nullptr;
        Node<T>* x = this->root;

        while (x != nullptr) {
            y = x;
            if (node->getData() < x->getData()) {
                x = x->getLeft();
            }
            else if (node->getData() > x->getData()) {
                x = x->getRight();
            }
            else {
                x->addAccess();
                splay(x);
                return;
            }
        }

        // si  nunca se asignó y  AB vacío
        node->setParent(y);
        if (y == nullptr) {
            root = node;
        }// Si es menor el valor a insertar es hijo izquierdo
        else if (node->getData() < y->getData()) {
            y->setLeft(node);
        }// Si es mayor el valor a insertar es hijo derecho
        else {
            y->setRight(node);
        }
        //Biselar el nodo hasta la raíz
        splay(node);
        // tamanio++;
    }

    /*
    * fileToSplayTree, se cargan los datos de un txt a un árbol biselado
    * 
    * Se leen las ips del archivo y se insertan a un árbol BST, se utiliza el método
    * ipToLong para convertir las ips a un tipo de dato long long
    * 
    * @param filename: nombe del archivo txt
    * @return: no tiene
    * Complejidad tiempo: O(nlog(n))
    * Complejidad espacio: O(1)
    */    
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
            insert(ipGenerada);

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
    * search, búsqueda de un nodo en el árbol
    * 
    * Se realiza una búsqueda binaria hasta encontrar el nodo solicitado.
    * 
    * @param data: dato a buscar
    * @return: booleano, true si se encuentra, false si no
    * Complejidad tiempo: O(log(n))
    * Complejidad espacio: O(1)
    */ 
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
    * Añade un nodo al árbol y se revisa si el nodo ya existe, si ya existe, no se inserta.
    * 
    * @param value: dato a insertar
    * @return: no tiene
    * Complejidad tiempo: O(log(n))
    * Complejidad espacio: O(1)
    */
    void insert(T value) {
        Node<T>* current = root;

        if (current == nullptr) {
            root = new Node<T>(value);
            return;
        }

        while (current != nullptr) {
            if (value < current->getData()) {
                if (current->getLeft() == nullptr) {
                    current->setLeft(new Node<T>(value));
                    return;
                }
                else {
                    current = current->getLeft();
                }
            }
            else if (value > current->getData()) {
                if (current->getRight() == nullptr) {
                    current->setRight(new Node<T>(value)) ;
                    return;
                }
                else {
                    current = current->getRight();
                }
            }
            else {
                return;
            }
        }
    }

    /*
    * fileToBst, se cargan los datos de un txt a un árbol BST
    * 
    * Se leen las ips del archivo y se insertan a un árbol BST, se utiliza el método
    * ipToLong para convertir las ips a un tipo de dato long long.
    * 
    * @param filename: nombre del archivo txt
    * @return: no tiene
    * Complejidad tiempo: O(nlog(n))
    * Complejidad espacio: O(1)
    */     
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
            insert(ipGenerada);
        }
        bitacora.close();
    }

};

int main() {
    clock_t time;
    BST<long long> bst;
    ArbolBiselado<long long> splayTree;
    ArbolBiselado<long long> splayTreeUnchanged;

    // Lectura de archivo
    bst.fileToBst("bitacoraelb.txt");
    splayTreeUnchanged.fileToSplayTree("bitacoraelb.txt");
    
    // Caso de prueba 1, buscar 100000000 veces la misma ip
    cout << "Caso prueba 1: 100000000 busquedas de la misma ip" << endl;

    //BST
    time = clock();
    for (int i = 0; i <= 100000000; i++) {
        bst.search(41243152151);
    }
    time = clock() - time;
    cout << "BST: " << (float)time/CLOCKS_PER_SEC << " segundos" << endl;

    splayTree = splayTreeUnchanged;
    //Splay Tree
    time = clock();
    for (int i = 0; i <= 100000000; i++) {
        splayTree.search(41243152151);
    }
    time = clock() - time;
    cout << "Splay Tree: " << (float)time / CLOCKS_PER_SEC << " segundos" << endl;

    // Caso de prueba 2, busqueda de 12006 ips ascendentes
    cout << "\nCaso prueba 2: busqueda de ips ascendentes" << endl; 

    // BST
    timeTest(bst, "ipsAsc.txt", "BST: ");
    
    splayTree = splayTreeUnchanged;
    // Splay Tree
    timeTest(splayTree, "ipsAsc.txt", "Splay Tree: ");

    // Caso de prueba 3, busqueda de 12006 ips descendentes
    cout << "\nCaso prueba 3: busqueda de ips descendentes" << endl; 
    
    // BST
    timeTest(bst, "ipsDesc.txt", "BST: ");

    splayTree = splayTreeUnchanged;    
    // Splay Tree
    timeTest(splayTree, "ipsDesc.txt", "Splay Tree: ");

    // Caso de prueba 4, hay dos ips que se repiten mucho dentro del .txt, pero también hay ips aleatorias entre ellas
    cout << "\nCaso prueba 4: busqueda de dos ips repetidas con ips aleatorias" << endl;

    // BST
    timeTest(bst, "ipsDosRepetidas.txt", "BST: ");

    splayTree = splayTreeUnchanged;
    // Splay Tree
    timeTest(splayTree, "ipsDosRepetidas.txt", "Splay Tree: ");

    return 0;
}

/*
Bibliografía:
GeeksforGeeks. (2023a). Insertion in Binary Search Tree BST. GeeksforGeeks. 
https://www.geeksforgeeks.org/insertion-in-binary-search-tree/

GeeksforGeeks. (2023b). Introduction to Splay Tree Data Structure. GeeksforGeeks. 
https://www.geeksforgeeks.org/introduction-to-splay-tree-data-structure/
*/