/*
Act 2.1 - Implementación de un ADT de estructura de datos lineales
Fidel Morales Briones A01198630
2 de octubre de 2023
*/
#include <iostream>
using namespace std;

template <class T>
class Node {
    private:
        T data;
        Node<T> *next;
        Node<T> *previous;
        int priority = 0;
    
    public:
        Node(T data) {
            this->data = data;
            previous = nullptr;
            next = nullptr;
        }

        T getData() {
            return data;
        }

        void setData(T data) {
            this->data = data;
        }

        Node<T> * getNext() {
            return next;
        }

        void setNext(Node<T> *next) {
            this->next = next;
        }

        Node<T> * getPrevious() {
            return previous;
        }

        void setPrevious(Node<T> *previous) {
            this->previous = previous;
        }

        int getPriority() {
            return priority;
        }

        void setPriority(int priority) {
            this->priority = priority;
        }
};

template <class T>
class priorityQueue {
    private:
        Node<T> *head;
        Node<T> *tail;

    public:
        priorityQueue() {
            head = nullptr;
            tail = nullptr;
        }

        //Create
        void push(T data, int priority) {
            Node<T> *new_node = new Node<T>(data);
            new_node->setPriority(priority);

            if (head == nullptr) {
                head = new_node;
                tail = new_node;
            } 
            else {
                Node<T> *current = tail;
                while (current != nullptr) {
                    if (current->getPriority() >= new_node->getPriority()) {
                        if (current == tail) {
                            new_node->setPrevious(current);
                            current->setNext(new_node);
                            tail = new_node;
                            break;
                        } else {
                            new_node->setPrevious(current);
                            new_node->setNext(current->getNext());
                            current->getNext()->setPrevious(new_node);
                            current->setNext(new_node);
                            break;
                        }
                    }
                    else if (current->getPrevious() == nullptr) {
                        new_node->setNext(head);
                        head->setPrevious(new_node);
                        head = new_node;
                        break;
                    }
                    current = current->getPrevious();
                }
            }
        }

        //Read
        void printList() {
            Node<T> *current = head;
            while (current != nullptr) {
                cout << current->getData() << ", prioridad: " << current->getPriority() << endl;
                current = current->getNext();
            }
        }

        //Delete
        void pop() {
            if (head == nullptr) {
                cout << "La lista está vacía" << endl;
            } 
            else {
                Node<T> *current = head;
                head = head->getNext();
                head->setPrevious(nullptr);
                delete current;
            }
        }
        
};

template <class T>
class deque {
    private:
        Node<T> *head;
        Node<T> *tail;

    public:
        deque() {
            head = nullptr;
            tail = nullptr;
        }

        //Create
        void pushFront(T data) {
            Node<T> *new_node = new Node<T>(data);
            if (head == nullptr) {
                head = new_node;
                tail = new_node;
            }
            else {
                head->setPrevious(new_node);
                new_node->setNext(head);
                head = new_node;
            }
        } 

        //Read
        void printList() {
            Node<T> *current = head;
            while (current != nullptr) {
                cout << current->getData() << endl;
                current = current->getNext();
            }
        }

        //Delete
        void popFront() {
            if (head == nullptr) {
                cout << "La lista está vacía" << endl;
            } 
            else {
                Node<T> *current = head;
                head = head->getNext();
                head->setPrevious(nullptr);
                delete current;
            }
        }

};

int main() {

    priorityQueue<int> *queue = new priorityQueue<int>();
    queue->push(9, 1);
    queue->push(2, 2);
    queue->push(4, 1);
    queue->push(10, 3);
    queue->push(1, 3);
    queue->printList();
    queue->pop();
    queue->printList();

    deque<int> *pruebaDeque = new deque<int>();
    pruebaDeque->pushFront(5);
    pruebaDeque->printList();
    pruebaDeque->pushFront(9);
    pruebaDeque->pushFront(11);
    pruebaDeque->printList();
    cout<<endl;
    pruebaDeque->popFront();
    pruebaDeque->printList();
};