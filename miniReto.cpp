#include <iostream>
#include <string>
#include <fstream>
using namespace std;

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
                cout << current->getData() << " ";
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

        void eliminarPalabrasRepetidas() {
            Node<T> *tempWord =  nullptr;
            Node<T> *tempDelete = nullptr;
            Node<T> *current = head;
            
            while(current->getNext() != nullptr) {
                if (current->getData() == current->getNext()->getData()) {
                    tempWord = current;
                    while ((current->getData() == current->getNext()->getData())) {
                        
                        tempDelete = current->getNext()->getNext();
                        deleteNode(current->getData());
                        deleteNode(current->getNext()->getData());
                        current = tempDelete;

                    }
                }
                else {
                current = current->getNext();
                }
            }  


        //     do {
        //         if (tempWord == nullptr) {

        //             if (current->getData() == current->getNext()->getData()) {
        //                 deleteNode(current->getNext()->getData());
        //                 tempDelete = current;
        //                 deleteNode(current->getData());
        //                 current = tempDelete;
        //             }
        //             else {
        //                 current = current->getNext();
        //             }
        //         }
        //         else if (tempWord != nullptr) {
                    

        //             tempWord = current;
        //         }
        //     }
        //     while (current->getNext() != nullptr);
        }
};

int main() {

    ifstream mensajesAlien;
    mensajesAlien.open("pruebas.txt");
    
    string line;
    doublyLinkedList<string> *lista = new doublyLinkedList<string>();
    while (getline(mensajesAlien, line, ' ')) {
        lista->addNode(line);
    }

    lista->eliminarPalabrasRepetidas();
    lista->printList();    
};