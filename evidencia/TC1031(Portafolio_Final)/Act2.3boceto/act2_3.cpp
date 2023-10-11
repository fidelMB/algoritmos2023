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
        Node<T> *previous;
    
    public:
        Node(T data) {
            this->data = data;
            next = nullptr;
            previous = nullptr;
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

        void setPrevious(Node<T> *previous) {
            this->previous = previous;
        }

        Node<T> * getPrevious() {
            return previous;
        }
};

Node<int> *globalPtr = nullptr;

template <class T>
class linkedList {
    private:
        Node<T> *head;

    public:
        linkedList() {
            head = nullptr;
            
        }

        Node<T> * getHead() {
            return head;
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
        void addNode(Node<int> **head_ref, T data) {
            Node<T> *new_node = new Node<T>(data);
            if (head == nullptr) {
                head = new_node;
                *head_ref = head;
            }
            else {
                Node<T> *current = head;
                while (current->getNext() != nullptr) {
                    current = current->getNext();
                }
                current->setNext(new_node);
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
        void printList() {
            Node<T> *current = head;
            while (current != nullptr) {
                current->getData().printRowData();
                current = current->getNext();
            }
        }

        
};

/* sorts the linked list by changing next pointers (not data) */
template<typename T>
void MergeSort(Node<T>** headRef)
{
    Node<T> *head = *headRef;
    Node<T> *a;
    Node<T> *b;
 
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
 
/* See https:// www.geeksforgeeks.org/?p=3622 for details of this
function */
template<typename T>
Node<T> * SortedMerge(Node<T> *a, Node<T> *b)
{
    Node<T> *result = nullptr;
 
    /* Base cases */
    if (a == nullptr)
        return (b);
    else if (b == nullptr)
        return (a);
 
    /* Pick either a or b, and recur */
    if (a->getData() <= b->getData()) {
        result = a;
        result->getNext() = SortedMerge(a->getNext(), b);
    }
    else {
        result = b;
        result->getNext() = SortedMerge(a, b->getNext());
    }
    return (result);
}
 
/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
    and return the two lists using the reference parameters.
    If the length is odd, the extra node should go in the front list.
    Uses the fast/slow pointer strategy. */
template<typename T>
void FrontBackSplit(Node<T>* source, Node<T>** frontRef, Node<T>** backRef)
{
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
    slow->getNext() = nullptr;
}

template<typename T>
void printList(Node<T> *node)
{
    while (node != NULL) {
        cout << node->getData() << " ";
        node = node->getNext();
    }
}

int main() {
    // Se abre el archivo de la bitácora
    // ifstream bitacora;
    // bitacora.open("bitacoraelb.txt");
    // string line, date, IP, message;

    // /** Se crea una lista ligada, una lista doblemente ligada y una lista ligada circular
    //  *  para guardar los datos de la bitácora dentro de nodos
    //  */ 
    // linkedList<rowData> *list = new linkedList<rowData>();
    // while (getline(bitacora, line, ' ')) {
    //     getline(bitacora, date, '|');
    //     getline(bitacora, IP, '|');
    //     getline(bitacora, message, '\n');
    //     list->addNode(rowData(date, IP, message));
    // }

    // bitacora.close();
    // list->printList();

    linkedList<int> *lista = new linkedList<int>();
    cout<<lista->getHead();
    cout<<globalPtr->getData();
    lista->addNode(&globalPtr,5);
    lista->addNode(&globalPtr,519);
    lista->addNode(&globalPtr,58);
    lista->addNode(&globalPtr,50);
    printList(globalPtr);
    cout << endl;
    

};