/*
Act 2.1 - Implementación de un ADT de estructura de datos lineales
Fidel Morales Briones A01198630
28 de septiembre de 2023
*/
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

template <class T>
class linkedList {
    private:
        Node<T> *head;

    public:
        linkedList() {
            head = nullptr;
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
        void addNode(T data) {
            Node<T> *new_node = new Node<T>(data);
            if (head == nullptr) {
                head = new_node;
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
        
        /**
         * Update, actualizar dato de nodo
         *
         * Se introduce el dato a actualizar y el nuevo dato. Se recorre la lista
         * hasta encontrar el dato a actualizar y se actualiza con el nuevo dato
         *
         * Entrada: dato a actualizar y nuevo dato
         * Salida: no tiene
         * Complejidad tiempo: O(n)
         * Complejidad espacio: O(1)
         */
        void updateNode(T oldData, T newData) {
            Node<T> *current = head;
            while (current != nullptr) {
                if (current->getData() == oldData) {
                    current->setData(newData);
                    break;
                }
                current = current->getNext();
            }
        }

        /**
         * Delete, se borra un nodo
         *
         * El siguiente nodo al nodo a borrar se vuelve el siguiente del nodo anterior,
         * y se borra el nodo a borrar
         *
         * Entrada: nodo a borrar
         * Salida: no tiene
         * Complejidad tiempo: O(n)
         * Complejidad espacio: O(1)
         */
        void deleteNode(T data) {
            Node<T> *current = head;
            Node<T> *previous = nullptr;
            while (current != nullptr) {
                if (current->getData() == data) {
                    if (previous == nullptr) {
                        head = current->getNext();
                    }
                    else {
                        previous->setNext(current->getNext());
                    }
                    delete current;
                    break;
                }
                previous = current;
                current = current->getNext();
            }
        }

};

template <class T>
class doublyLinkedList {
    private:
        Node<T> *head;
        Node<T> *tail;

    public:
        doublyLinkedList() {
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
         * Complejidad tiempo: O(1)
         * Complejidad espacio: O(1)
         */
        void addNode(T data) {
            Node<T> *new_node = new Node<T>(data);
            if (head == nullptr) {
                head = new_node;
                tail = new_node;
            }
            else {
                tail->setNext(new_node);
                new_node->setPrevious(tail);
                tail = new_node;
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

        
        /**
         * Update, actualizar dato de nodo
         *
         * Se introduce el dato a actualizar y el nuevo dato. Se recorre la lista
         * hasta encontrar el dato a actualizar y se actualiza con el nuevo dato
         *
         * Entrada: dato a actualizar y nuevo dato
         * Salida: no tiene
         * Complejidad tiempo: O(n)
         * Complejidad espacio: O(1)
         */
        void updateNode(T oldData, T newData) {
            Node<T> *current = head;
            while (current != nullptr) {
                if (current->getData() == oldData) {
                    current->setData(newData);
                    break;
                }
                current = current->getNext();
            }
        }

        /**
         * Delete, se borra un nodo
         *
         * El siguiente nodo al nodo a borrar se vuelve el siguiente del nodo anterior,
         * y se borra el nodo a borrar, y también se actualiza el nodo anterior
         *
         * Entrada: nodo a borrar
         * Salida: no tiene
         * Complejidad tiempo: O(n)
         * Complejidad espacio: O(1)
         */
        void deleteNode(T data) {
            Node<T> *current = head;
            Node<T> *previous = nullptr;
            while (current != nullptr) {
                if (current->getData() == data) {
                    if (previous == nullptr) {
                        head = current->getNext();
                        head->setPrevious(nullptr);
                    }
                    else {
                        previous->setNext(current->getNext());
                        current->getNext()->setPrevious(previous);
                    }
                    delete current;
                    break;
                }
                previous = current;
                current = current->getNext();
            }

        }
};

template <class T>
class circularLinkedList {
    private:
        Node<T> *head;
        Node<T> *tail;


    public:
        circularLinkedList() {
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
         * Complejidad tiempo: O(1)
         * Complejidad espacio: O(1)
         */
        void addNode(T data) {
            Node<T> *new_node = new Node<T>(data);
            if (head == nullptr) {
                head = new_node;
                tail = new_node;
                tail->setNext(head);
            }
            else {
                tail->setNext(new_node);
                new_node->setNext(head);
                tail = new_node;
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

                if (current == head) {
                    break;
                }
            }
        }

        
        /**
         * Update, actualizar dato de nodo
         *
         * Se introduce el dato a actualizar y el nuevo dato. Se recorre la lista
         * hasta encontrar el dato a actualizar y se actualiza con el nuevo dato
         *
         * Entrada: dato a actualizar y nuevo dato
         * Salida: no tiene
         * Complejidad tiempo: O(n)
         * Complejidad espacio: O(1)
         */
        void updateNode(T oldData, T newData) {
            Node<T> *current = head;
            while (current != nullptr) {
                if (current->getData() == oldData) {
                    current->setData(newData);
                    break;
                }
                current = current->getNext();
            }
        }

        /**
         * Delete, se borra un nodo
         *
         * El siguiente nodo al nodo a borrar se vuelve el siguiente del nodo anterior,
         * y se borra el nodo a borrar, y también se actualiza el nodo anterior
         *
         * Entrada: nodo a borrar
         * Salida: no tiene
         * Complejidad tiempo: O(n)
         * Complejidad espacio: O(1)
         */
            void deleteNode(T data) {
            Node<T> *current = head;
            Node<T> *previous = nullptr;
            while (current != nullptr) {
                if (current->getData() == data) {
                    if (previous == nullptr) {
                        head = current->getNext();
                        tail->setNext(head);
                    }
                    else {
                        previous->setNext(current->getNext());
                    }
                    delete current;
                    break;
                }
                previous = current;
                current = current->getNext();
            }
        }

};

int main() {
    // Se abre el archivo de la bitácora
    ifstream bitacora;
    bitacora.open("bitacoraelb.txt");
    string line, date, IP, message;

    /** Se crea una lista ligada, una lista doblemente ligada y una lista ligada circular
     *  para guardar los datos de la bitácora dentro de nodos
     */ 
    linkedList<rowData> *list = new linkedList<rowData>();
    doublyLinkedList<rowData> *list2 = new doublyLinkedList<rowData>();
    circularLinkedList<rowData> *list3 = new circularLinkedList<rowData>();
    while (getline(bitacora, line, ' ')) {
        getline(bitacora, date, '|');
        getline(bitacora, IP, '|');
        getline(bitacora, message, '\n');
        list->addNode(rowData(date, IP, message));
        list2->addNode(rowData(date, IP, message));
        list3->addNode(rowData(date, IP, message));
    }

    bitacora.close();
    
    // Impresión de las listas
    list->printList();
    cout << "Impresion de lista ligada terminada" << endl;
    system("pause");

    list2->printList();
    cout << "Impresion de lista doblemente ligada terminada" << endl;
    system("pause");
    
    list3->printList();
    cout << "Impresion de lista ligada circular terminada" << endl;
    system("pause");

    return 0;
}