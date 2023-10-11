#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class rowData {
    private:
       string year, month, day, hour, IP, message;

    public:
        rowData() {
            year = "";
            month = "";
            day = "";
            hour = "";
            IP = "";
            message = "";
        }

        rowData(string year, string month, string day, string hour, string IP, string message) {
            this->year = year;
            this->month = month;
            this->day = day;
            this->hour = hour;
            this->IP = IP;
            this->message = message;

        }
        
        string getDate() {
            if (month == "Jan") {
                month = "01";
            }
            else if (month == "Feb") {
                month = "02";
            }
            else if (month == "Mar") {
                month = "03";
            }
            else if (month == "Apr") {
                month = "04";
            }
            else if (month == "May") {
                month = "05";
            }
            else if (month == "Jun") {
                month = "06";
            }
            else if (month == "Jul") {
                month = "07";
            }
            else if (month == "Aug") {
                month = "08";
            }
            else if (month == "Sep") {
                month = "09";
            }
            else if (month == "Oct") {
                month = "10";
            }
            else if (month == "Nov") {
                month = "11";
            }
            else if (month == "Dec") {
                month = "12";
            }
            string date = year + month + day + hour;
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
            cout << year << " " << month << " " << day << " " << hour << "|" << IP << "|" << message << endl;
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

Node<rowData> *globalPtr;

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
         * agrega un nodo
         *
         * Entrada: dato a añadir al nodo
         * Salida: no tiene
         * Complejidad tiempo: O(1)
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
                node->getData().printRowData();
                node = node->getNext();
            }
        }  
};

template <class T>
void FrontBackSplit(Node<T> *source, Node<T> **frontRef, Node<T> **backRef) {
    Node<T> *fast;
    Node<T> *slow;
    slow = source;
    fast = source->getNext();
 
    while (fast != nullptr) {
        fast = fast->getNext();
        if (fast != nullptr) {
            slow = slow->getNext();
            fast = fast->getNext();
        }
    }
 
    *frontRef = source;
    *backRef = slow->getNext();
    slow->setNext(nullptr);
}

template<class T>
Node<T> * SortedMerge(Node<T> *a, Node<T>* b) {
    Node<T> *result = nullptr;
 
    if (a == nullptr) {
        return (b);
    }
    else if (b == nullptr) { 
        return (a);
    }

    if (a->getData().getDate() <= b->getData().getDate()) {
        result = a;
        result->setNext(SortedMerge(a->getNext(), b));
    }
    else {
        result = b;
        result->setNext(SortedMerge(a, b->getNext()));
    }

    return (result);
}

int i = 0;
template<class T>
void MergeSort(Node<T> **headRef) {
    Node<T> *head = *headRef;
    Node<T> *a;
    Node<T> *b;
 
    if ((head == nullptr) || (head->getNext() == nullptr)) {
        return;
    }
 
    FrontBackSplit(head, &a, &b);
 
    MergeSort(&a);
    MergeSort(&b);
 
    *headRef = SortedMerge(a, b);
    cout<< i << endl;
    i++;
}
 
int main() {
    // Se abre el archivo de la bitácora
    ifstream bitacora;
    bitacora.open("bitacoraelb.txt");
    string line, year, month, day, hour, IP, message;

    /** Se crea una lista ligada, una lista doblemente ligada y una lista ligada circular
     *  para guardar los datos de la bitácora dentro de nodos
     */ 
    linkedList<rowData> *list = new linkedList<rowData>();
    Node<rowData> *ptr = nullptr;

    while (getline(bitacora, year, ' ')) {
        getline(bitacora, month, ' ');
        getline(bitacora, day, ' ');
        getline(bitacora, hour, '|');
        getline(bitacora, IP, '|');
        getline(bitacora, message, '\n');
        list->addNode(&ptr, rowData(year, month, day, hour, IP, message));
    }

    bitacora.close();    
    MergeSort(&globalPtr);
    list->printList(globalPtr);
    return 0;
};