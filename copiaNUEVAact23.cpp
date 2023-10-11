#include <iostream>
#include <fstream>
using namespace std;

class rowData {
    private:
       string date, IP, message;

    public:
        rowData() {
            date = "";
            IP = "";
            message = "";
        }

        rowData(string date, string IP, string message) {
            this->date = date;
            this->IP = IP;
            this->message = message;
        }

        void setDate(string date) {
            this->date = date;
        }

        string getDate() {
            return date;
        }

        void setIP(string IP) {
            this->IP = IP;
        }

        string getIP() {
            return IP;
        }

        void setMessage(string message) {
            this->message = message;
        }

        string getMessage() {
            return message;
        }

        /**
         * Imprimir datos de la fila
         *
         * Con el mismo formato de la bitácora, se imprimen todos los atributos de la fila
         *
         * Entrada: no tiene
         * Salida: se imprime la fecha, IP y mensaje de la fila
         * Complejidad tiempo: O(1)
         * Complejidad espacio: O(1)
         */
        void printRowData() {
            cout << date << "|" << IP << "|" << message << endl;
        }
};

template <class T>
class Node {
    private:
        T data;
        Node<T> *next;
    
    public:
        Node(T data) {
            this->data = data;
            next = nullptr;
        }

        void setData(T data) {
            this->data = data;
        }

        T getData() {
            return data;
        }

        void setNext(Node<T> *next) {
            this->next = next;
        }

        Node<T> * getNext() {
            return next;
        }

};

Node<int> *globalPtr;

template <class T>
class linkedList {
    private:
        Node<T> *head;
        Node<T> *tail;

    public:

        linkedList() {
            head = nullptr;
            tail = nullptr;
        }

        /**
         * Create, añadir nodo
         *
         * Si no hay nodos, se crea el primero, y si ya hay nodos, se 
         * recorre la lista hasta llegar al último nodo y se añade el nuevo nodo al final
         *
         * Entrada: dato a añadir al nodo
         * Salida: no tiene
         * Complejidad tiempo: O(n)
         * Complejidad espacio: O(1)
         */
        void addNode(Node<T> **head_ref, T data) {
            Node<T> *new_node = new Node<T>(data);
            if (*head_ref == nullptr) {
                *head_ref = new_node;
                globalPtr = *head_ref;
            }
            else {
                (*head_ref)->setNext(new_node);
                *head_ref = new_node;
            }
        } 
        

        /**
         * Read, imprimir lista
         *
         * Se imprimen los datos de todos los nodos
         * dentro la lista recorriendo toda la lista
         *
         * Entrada: no
         * Salida: imprimir datos de todos los nodos
         * Complejidad tiempo: O(n)
         * Complejidad espacio: O(1)
         */
        void printList(Node<T> *node) {
            while (node != nullptr) {
                cout << node->getData() << " ";
                node = node->getNext();
            }
        }

        
};

/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
    and return the two lists using the reference parameters.
    If the length is odd, the extra node should go in the front list.
    Uses the fast/slow pointer strategy. */
template <class T>
void FrontBackSplit(Node<T> *source, Node<T> **frontRef, Node<T> **backRef) {
    Node<T> *fast;
    Node<T> *slow;
    slow = source;
    fast = source->getNext();
 
    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != nullptr) {
        fast = fast->getNext();
        if (fast != nullptr) {
            slow = slow->getNext();
            fast = fast->getNext();
        }
    }
 
    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *frontRef = source;
    *backRef = slow->getNext();
    slow->setNext(nullptr);
}

/* See https:// www.geeksforgeeks.org/?p=3622 for details of this
function */
template<class T>
Node<T>* SortedMerge(Node<T> *a, Node<T>* b) {
    Node<T>* result = nullptr;
 
    /* Base cases */
    if (a == nullptr) {
        return (b);
    }
    else if (b == nullptr) { 
        return (a);
    }

    /* Pick either a or b, and recur */
    if (a->getData() <= b->getData()) {
        result = a;
        result->setNext(SortedMerge(a->getNext(), b));
    }
    else {
        result = b;
        result->setNext(SortedMerge(a, b->getNext()));
    }

    return (result);
}
 
/* sorts the linked list by changing next pointers (not data) */
template<class T>
void MergeSort(Node<T> **headRef) {
    Node<T>* head = *headRef;
    Node<T>* a;
    Node<T>* b;
 
    /* Base case -- length 0 or 1 */
    if ((head == nullptr) || (head->getNext() == nullptr)) {
        return;
    }
 
    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b);
 
    /* Recursively sort the sublists */
    MergeSort(&a);
    MergeSort(&b);
 
    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b);
}
 

int main() {
    // // Se abre el archivo de la bitácora
    // ifstream bitacora;
    // bitacora.open("bitacoraelb.txt");
    // string line, date, IP, message;

    // /** Se crea una lista ligada, una lista doblemente ligada y una lista ligada circular
    //  *  para guardar los datos de la bitácora dentro de nodos
    //  */ 
    linkedList<int> *lista = new linkedList<int>();
    Node<int> *ptr = nullptr;

    // while (getline(bitacora, line, ' ')) {
    //     getline(bitacora, date, '|');
    //     getline(bitacora, IP, '|');
    //     getline(bitacora, message, '\n');
    //     list->addNode(&ptr, rowData(date, IP, message));
    // }
    // list->printList(globalPtr);
    // bitacora.close();
    lista->addNode(&ptr,5);
    lista->addNode(&ptr,519);
    lista->addNode(&ptr,58);
    lista->addNode(&ptr,50);
    lista->printList(globalPtr);
    cout << endl;
    MergeSort(&globalPtr);
    lista->printList(globalPtr);
    


};