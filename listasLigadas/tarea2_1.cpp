/*
Act 2.1 - Implementación de un ADT de estructura de datos lineales
Fidel Morales Briones A01198630
28 de septiembre de 2023
*/
#include <iostream>
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
class linkedList {
    private:
        Node<T> *head;

    public:
        linkedList() {
            head = nullptr;
        }

        
        /**
         * título breve
         *
         * Con el uso de un ciclo for, se suma de manera iterativa desde 1 hasta el número n. / descrpción más detallada
         *
         * Entrada:
         * Salida:
         * Complejidad tiempo:
         * Complejidad espacio:
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

        //Read
        void printNodeInfo(T data) {
            Node<T> *current = head;
            while (current != nullptr) {
                if (current->getData() == data) {
                    cout << "Data: " << current->getData() << endl;
                    cout << "Next address: " << current->getNext() << endl;
                    break;
                }
                current = current->getNext();
            }
        }
        
        //Update
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

        //Delete
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

        //Create
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

        //Read
        void printNodeInfo(T data) {
            Node<T> *current = head;
            while (current != nullptr) {
                if (current->getData() == data) {
                    cout << "Data: " << current->getData() << endl;
                    cout << "Previous address: " << current->getPrevious() << endl;
                    cout << "Next address: " << current->getNext() << endl;
                    break;
                }
                current = current->getNext();
            }
        }

        //Update
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

        //Delete
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

        //Create
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

        //Read
        void printNodeInfo(T data) {
            Node<T> *current = head;
            while (current != nullptr) {
                if (current->getData() == data) {
                    cout << "Data: " << current->getData() << endl;
                    cout << "Previous address: " << current->getPrevious() << endl;
                    cout << "Next address: " << current->getNext() << endl;
                    break;
                }
                current = current->getNext();
            }
        }

        //Update
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

        //Delete
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
  
    


    return 0;
}