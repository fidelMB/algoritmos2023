/*
Act 2.3 - Actividad Integral estructura de datos lineales (Evidencia Competencia)
Integrantes:
Andrés Emiliano de la Garza Rosales  a01384096
Rodrigo de Jesús Meléndez Molina a00831646
Fidel Morales Briones A01198630
5 de octubre de 2023
*/
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

        string getRowData() {
            string rowData = year + " " + month + " " + day + " " + hour + "|" + IP + "|" + message + "\n";
            return rowData;
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
                cout << node->getData().getRowData();
                node = node->getNext();
            }
        }
};

template <class T>
int length(Node<T> *current) {
    int count = 0;
    while (current != nullptr) {
        current = current->getNext();
        count++;
    }
    return count;
}
 
/* Merge function of Merge Sort to Merge the two sorted parts
   of the Linked List. We compare the next value of start1 and 
   current value of start2 and insert start2 after start1 if 
   it's smaller than next value of start1. We do this until
   start1 or start2 end. If start1 ends, then we assign next 
   of start1 to start2 because start2 may have some elements
   left out which are greater than the last value of start1. 
   If start2 ends then we assign end2 to end1. This is necessary
   because we use end2 in another function (mergeSort function) 
   to determine the next start1 (i.e) start1 for next
   iteration = end2->next */
template <class T>
void merge(Node<T> **start1, Node<T> **end1, Node<T> **start2, Node<T> **end2) {
 
    // Making sure that first node of second
    // list is higher.
    Node<T> *temp = nullptr;
    if ((*start1)->getData().getDate() > (*start2)->getData().getDate()) {
        swap(*start1, *start2);
        swap(*end1, *end2);
    }
 
    // Merging remaining nodes
    Node<T> *astart = *start1, *aend = *end1;
    Node<T> *bstart = *start2, *bend = *end2;
    Node<T> *bendnext = (*end2)->getNext();
    while (astart != aend && bstart != bendnext) {
        if (astart->getNext()->getData().getDate() > bstart->getData().getDate()) {
            temp = bstart->getNext();
            bstart->setNext(astart->getNext());
            astart->setNext(bstart);
            bstart = temp;
        }
        astart = astart->getNext();
    }
    if (astart == aend)
        astart->setNext(bstart);
    else
        *end2 = *end1;
}
 
/* MergeSort of Linked List
   The gap is initially 1. It is incremented as 
   2, 4, 8, .. until it reaches the length of the 
   linked list. For each gap, the linked list is 
   sorted around the gap. 
   The prevend stores the address of the last node after
   sorting a part of linked list so that it's next node
   can be assigned after sorting the succeeding list. 
   temp is used to store the next start1 because after 
   sorting, the last node will be different. So it 
   is necessary to store the address of start1 before 
   sorting. We select the start1, end1, start2, end2 for 
   sorting. start1 - end1 may be considered as a list 
   and start2 - end2 may be considered as another list 
   and we are merging these two sorted list in merge 
   function and assigning the starting address to the 
   previous end address. */
template <class T>
void mergeSort(Node<T> **head)
{
    if (*head == NULL)
        return;
    Node<T> *start1 = nullptr, *end1 = nullptr;
    Node<T> *start2 = nullptr, *end2 = nullptr;
    Node<T> *prevend = nullptr;
    int len = length(*head);
 
    for (int gap = 1; gap < len; gap = gap * 2) {
        start1 = *head;
        while (start1) {
 
            // If this is first iteration
            bool isFirstIter = 0;
            if (start1 == *head)
                isFirstIter = 1;
 
            // First part for merging
            int counter = gap;
            end1 = start1;
            while (--counter && end1->getNext())
                end1 = end1->getNext();
 
            // Second part for merging
            start2 = end1->getNext();
            if (!start2)
                break;
            counter = gap;
            end2 = start2;
            while (--counter && end2->getNext())
                end2 = end2->getNext();
 
            // To store for next iteration.
            Node<T> *temp = end2->getNext();
 
            // Merging two parts.
            merge(&start1, &end1, &start2, &end2);
 
            // Update head for first iteration, else
            // append after previous list
            if (isFirstIter)
                *head = start1;
            else
                prevend->setNext(start1);
 
            prevend = end2;
            start1 = temp;
        }
        prevend->setNext(start1);
    }
}

template <class T>
void toTxtFile(Node<T> *node, string fileName) {
	fstream bitacora;
	
	bitacora.open(fileName, ios::out);

	while (node != nullptr) {
        bitacora << node->getData().getRowData();
        node = node->getNext();
	}

	bitacora.close();
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
    mergeSort(&globalPtr);
    toTxtFile(globalPtr, "bitacoraelbOrdenada.txt");
    list->printList(globalPtr);
    return 0;
};