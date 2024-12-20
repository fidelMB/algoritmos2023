/*  
Act 3.3 - Árbol Desplegado: Implementando un Splay Tree
Fidel Morales Briones A01198630
17 de octubre de 2023
*/
#include <iostream>
#include <locale.h>
#include <stack>
using namespace std;

class Nodo {
public:
    Nodo(long long valor ) {
        accesos = 0;
        ip = valor;
        progenitore = NULL;
        izquierdo = NULL;
        derecho = NULL;
    }
    long long ip=0; 
    int accesos = 0; 
    Nodo* progenitore; 
    Nodo* izquierdo; 
    Nodo* derecho; 
};

typedef Nodo* NodoPtr;

class ArbolBiselado {
private:
    NodoPtr raiz;
    int tamanio = 0;
 
    /*
    * find, búsqueda de un nodo en el árbol
    * 
    * Se realiza una búsqueda binaria hasta encontrar el nodo solicitado, se regresa el nodo encontrado
    * 
    * @param nodo: nodo a buscar
    * @param ip: valor de la ip del nodo a buscar
    * @return: NodoPtr, nodo encontrado
    * Complejidad tiempo: O(log(n))
    * Complejidad espacio: O(n)
    */   
    NodoPtr find(NodoPtr nodo, long long ip) {
        if (nodo == nullptr || ip ==nodo->ip) {
            return nodo;
        }

        if (ip < nodo->ip) {
            return find(nodo->izquierdo, ip);
        }
        return find(nodo->derecho, ip);
    }


    /*
    * del, elimina un nodo del árbol
    * 
    * Se realiza una búsqueda binaria hasta encontrar el nodo a eliminar
    * se bisela el nodo hasta la raíz, se eliminan los enlaces a los dos subárboles
    * y se une el subárbol izquierdo con el derecho
    * 
    * @param nodo: nodo a eliminar
    * @param ip: valor de la ip a eliminar
    * @return: no tiene
    * Complejidad tiempo: O(log(n))
    * Complejidad espacio: O(1)
    */    
    void del(NodoPtr nodo, long long ip) {
        NodoPtr eliminado = nullptr;
        NodoPtr t, s;
        while (nodo != nullptr) {
            if (nodo->ip == ip) {
                eliminado = nodo;
            }

            if (nodo->ip <= ip) {
                nodo = nodo->derecho;
            }
            else {
                nodo = nodo->izquierdo;
            }
        }

        if (eliminado == nullptr) {
            cout << "No se encontró la IP" << endl;
            return;
        }
        divide(eliminado, s, t); 
        if (s->izquierdo) { // elimina el nodo
            s->izquierdo->progenitore = nullptr;
        }
        //une los dos subárboles
        raiz = une(s->izquierdo, t);
        //libera memoria
        delete(s);
        s = nullptr;
    }
    
    /*
    * printIp, imprime una ip
    * 
    * Le da el formato correcto a una ip para imprimirla en la terminal con la ayuda de un stack
    * 
    * @param value: ip a imprimir
    * @return: se imprime la ip en la terminal
    * Complejidad tiempo: O(1)
    * Complejidad espacio: O(1)
    */   
    void printIp(long long value) {
        string valorAImprimir = "";
        int contador = 0;
        stack<int>*s = new  stack<int>();
        while (value > 0) {
            s->push(value % 256);
            value = value / 256;
            contador++;
        }
        int contador2 = contador;
        while (contador < 4) {
            cout << "0.";
            contador++;
        }
        while (!s->empty() ){
            cout << s->top();
            if (contador2 > 1) {
                cout << ".";
            }
            s->pop();
            contador2--;
        }
    }

    /*
    * print, imprime el árbol
    * 
    * Imprime todos los nodos del árbol en la terminal con un formato especial
    * 
    * @param raiz: raiz del árbol
    * @param relleno: strings para dar formato al árbol en la terminal
    * @param ultimo: booleano para saber si es el último nodo de la rama
    * @return: se imprime el árbol en la terminal
    * Complejidad tiempo: O(n)
    * Complejidad espacio: O(n)
    */       
    void print(NodoPtr raiz, string relleno, bool ultimo) {
        if (raiz != nullptr) {
            cout << relleno;
            if (ultimo) {
                cout << "L----";
                relleno += "     ";
            }
            else {
                cout << "L----";
                relleno += "|    ";

            }
            printIp(raiz->ip);
            cout <<  "," << raiz->accesos << endl;
            print(raiz->izquierdo, relleno, false);
            print(raiz->derecho, relleno, true);
        }
    }

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
    void rotarIzquierda(NodoPtr nodo) {
        NodoPtr y = nodo->derecho;
        nodo->derecho = y->izquierdo;
        if (y->izquierdo != nullptr) {
            y->izquierdo->progenitore = nodo;
        }
        y->progenitore = nodo->progenitore;
        if (nodo->progenitore == nullptr) {
            this->raiz = y;
        }
        else if (nodo == nodo->progenitore->izquierdo) {
            nodo->progenitore->izquierdo = y;
        }
        else {
            nodo->progenitore->derecho = y;
        }
        y->izquierdo = nodo;
        nodo->progenitore = y;
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
    void rotarDerecha(NodoPtr nodo) {
        NodoPtr y = nodo->izquierdo;
        //y es igual al hijo izquierdo
        nodo->izquierdo = y->derecho;
        //l izquierdo del nodo rotado apunta al derecho del hijo izquierdo, balanceo
        if (y->derecho != nullptr) {
            y->derecho->progenitore = nodo;
        }
        // si se hizo el balanceo el progenitor es el nuevo padre

        y->progenitore = nodo->progenitore;
        // si es raiz actualizar raíz
        if (nodo->progenitore == nullptr) {
            this->raiz = y;
        }
        else if (nodo == nodo->progenitore->derecho) {
            // el hijo derecho del padre del nodo es y
            nodo->progenitore->derecho = y;
        }
        else {
            //el  hijo izquierdo del padre del nodo es y
            nodo->progenitore->izquierdo = y;
        }
        // establece lado derecho
        y->derecho = nodo;
        // establece padre

        nodo->progenitore = y;
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
    void biselar(NodoPtr nodo) {
        while (nodo->progenitore) {
            if (!nodo->progenitore->progenitore) {
                if (nodo == nodo->progenitore->izquierdo) {
                    // zig
                    rotarDerecha(nodo->progenitore);
                }
                else {
                    // zag 
                    rotarIzquierda(nodo->progenitore);
                }
            }
            else if (nodo == nodo->progenitore->izquierdo && nodo->progenitore == nodo->progenitore->progenitore->izquierdo) {
                // zig-zig 
                rotarDerecha(nodo->progenitore->progenitore);
                rotarDerecha(nodo->progenitore);
            }
            else if (nodo == nodo->progenitore->derecho && nodo->progenitore == nodo->progenitore->progenitore->derecho) {
                // zag-zag
                rotarIzquierda(nodo->progenitore->progenitore);
                rotarIzquierda(nodo->progenitore);
            }
            else if (nodo == nodo->progenitore->derecho && nodo->progenitore == nodo->progenitore->progenitore->izquierdo) {
                // zig-zag 
                rotarIzquierda(nodo->progenitore);
                rotarDerecha(nodo->progenitore);
            }
            else {
                // zag-zig 
                rotarDerecha(nodo->progenitore);
                rotarIzquierda(nodo->progenitore);
            }
        }
    }

    /*
    * une, une dos subárboles después de borrar un nodo
    * 
    * Se utiliza para unir dos subárboles después de borrar un nodo, se bisela el nodo de valor más grande
    * 
    * @param s: nodo del subárbol izquierdo
    * @param t: nodo del subárbol derecho
    * @return: NodoPtr, nuevo nodo raíz
    * Complejidad tiempo: O(log(n))
    * Complejidad espacio: O(1)
    */      
    NodoPtr une(NodoPtr s, NodoPtr t) {
        if (!s) {
            return t;
        }

        if (!t) {
            return s;
        }
        NodoPtr x = maximo(s);
        biselar(x);
        x->derecho = t;
        t->progenitore = x;
        return x;
    }

    /*
    * divide, se divide el árbol en dos subárboles
    * 
    * Se utiliza cuando se elimina un nodo del árbol, se bisela el nodo hasta la raíz y se eliminan los enlaces
    * para dejar dos subárboles
    * 
    * @param x: nodo a borrar
    * @param s: nodo del subárbol izquierdo
    * @param t: nodo del subárbol derecho
    * @return: no tiene
    * Complejidad tiempo: O(log(n))
    * Complejidad espacio: O(n)
    */ 
    void divide(NodoPtr& x, NodoPtr& s, NodoPtr& t) {
        biselar(x);
        if (x->derecho) {
            t = x->derecho;
            t->progenitore = nullptr;
        }
        else {
            t = nullptr;
        }
        s = x;
        s->derecho = nullptr;
        x = nullptr;
    }

public:

    ArbolBiselado() {
        raiz = nullptr;
    }

    /*
    * find, búsqueda de un nodo en el árbol
    * 
    * Se realiza una búsqueda binaria hasta encontrar el nodo solicitado, se regresa el nodo encontrado,
    * se incrementa el contador de accesos y se bisela el nodo hasta la raíz
    * 
    * @param k: valor de la ip del nodo a buscar
    * @return: NodoPtr, nodo encontrado
    * Complejidad tiempo: O(log(n))
    * Complejidad espacio: O(n)
    */   
    NodoPtr find(long long k) {
        NodoPtr x = find(this->raiz, k);
        if (x) {
            x->accesos++;
            biselar(x);
        }
        return x;
    }

    /*
    * maximo, encuentra el nodo con valor máximo del árbol
    * 
    * Se realiza una búsqueda binaria hasta encontrar el nodo máximo del árbol
    * 
    * @param nodo: nodo raíz del árbol
    * @return: NodoPtr, nodo encontrado
    * Complejidad tiempo: O(log(n))
    * Complejidad espacio: O(1)
    */  
    NodoPtr maximo(NodoPtr nodo) {
        while (nodo->derecho != nullptr) {
            nodo = nodo->derecho;
        }
        return nodo;
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
    void insert(long long key) {
        NodoPtr nodo = new Nodo(key);
        nodo->progenitore = nullptr;
        nodo->izquierdo = nullptr;
        nodo->derecho = nullptr;
        nodo->ip = key;
        NodoPtr y = nullptr;
        NodoPtr x = this->raiz;

        while (x != nullptr) {
            y = x;
            if (nodo->ip < x->ip) {
                x = x->izquierdo;
            }
            else {
                x = x->derecho;
            }
        }

        // si  nunca se asignó y  AB vacío
        nodo->progenitore = y;
        if (y == nullptr) {
            raiz = nodo;
        }// Si es menor el valor a insertar es hijo izquierdo
        else if (nodo->ip < y->ip) {
            y->izquierdo = nodo;
        }// Si es mayor el valor a insertar es hijo derecho
        else {
            y->derecho = nodo;
        }
        //Biselar el nodo hasta la raíz
        biselar(nodo);
        tamanio++;
    }

    /*
    * del, elimina un nodo del árbol
    * 
    * Se realiza una búsqueda binaria hasta encontrar el nodo a eliminar
    * se bisela el nodo hasta la raíz, se eliminan los enlaces a los dos subárboles
    * y se une el subárbol izquierdo con el derecho
    * 
    * @param ip: valor de la ip a eliminar
    * @return: no tiene
    * Complejidad tiempo: O(log(n))
    * Complejidad espacio: O(1)
    */    
    void del(long long ip) {
        del(this->raiz, ip);
        tamanio--;
    }

    /*
    * print, imprime el árbol
    * 
    * Imprime todos los nodos del árbol en la terminal con un formato especial
    * 
    * @param: no tiene
    * @return: se imprime el árbol en la terminal
    * Complejidad tiempo: O(n)
    * Complejidad espacio: O(n)
    */   
    void printArbol() {
        print(this->raiz, "", true);
    }

    /*
    * size, regresa la cantidad de nodos dentro del árbol
    * 
    * regresa el atributo tamanio de la clase, que indica la cantidad de nodos del árbol
    * 
    * @param: no tiene
    * @return: entero que indica la cantidad de nodos que contiene al árbol
    * Complejidad tiempo: O(1)
    * Complejidad espacio: O(1)
    */
    int size() {
        return tamanio;
    }

};

int main() {
    // splay tree 1
    ArbolBiselado bst1;
    cout << "Splay Tree 1:" << endl;

    // insert
    bst1.insert(3232235778);
    bst1.insert(3232235779);
    bst1.insert(3232235780);
    bst1.insert(123);
    bst1.insert(41);
    bst1.insert(1);
    bst1.insert(43);

    // print
    bst1.printArbol();

    // del
    bst1.del(3232235778);

    // find
    cout << "Find: " << bst1.find(3232235779)->ip << endl;

    // size
    cout << "Size: " << bst1.size() << endl;

    bst1.printArbol();

    // splay tree 2
    ArbolBiselado bst2;
    cout << "\nSplay Tree 2:" << endl;

    // insert
    bst2.insert(542345);
    bst2.insert(545454);
    bst2.insert(11222);
    bst2.insert(11);
    bst2.insert(1);
    bst2.insert(90);
    bst2.insert(1043);

    // print
    bst2.printArbol();

    // del
    bst2.del(1);

    // find
    cout << "Find: " << bst2.find(11)->ip << endl;

    // size
    cout << "Size: " << bst2.size() << endl;

    bst2.printArbol();

    // splay tree 3
    ArbolBiselado bst3;
    cout << "\nSplay Tree 3:" << endl;

    // insert
    bst3.insert(0001);
    bst3.insert(0005);
    bst3.insert(004);
    bst3.insert(44);
    bst3.insert(43);

    // print
    bst3.printArbol();

    // del
    bst3.del(004);

    // find
    cout << "Find: " << bst3.find(43)->ip << endl;

    // size
    cout << "Size: " << bst3.size() << endl;

    bst3.printArbol();

    // splay tree 4
    ArbolBiselado bst4;
    cout << "\nSplay Tree 4:" << endl;

    // insert
    bst4.insert(0001);
    bst4.insert(0005);
    bst4.insert(0001);
    bst4.insert(0005); 
    bst4.insert(561234);
    bst4.insert(10897123);

    // print
    bst4.printArbol();

    // del
    bst4.del(0005);

    // find
    cout << "Find: " << bst4.find(0005)->ip << endl;

    // size
    cout << "Size: " << bst4.size() << endl;

    bst4.printArbol();   


    return 0;
}

/*
Bibliografía:
GeeksforGeeks. (2023). Introduction to Splay Tree Data Structure. GeeksforGeeks. 
https://www.geeksforgeeks.org/introduction-to-splay-tree-data-structure/
*/
