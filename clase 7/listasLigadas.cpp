/*
Demostración de listas ligadas con template
Autor MTI Eduardo Lopez Benítez
19/09/2022
v 2.0
*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

template <class T>
class Node {
    public:
        T data;
        Node<T> *next;
        Node(T dataValue) {
            data = dataValue;
            next = nullptr;
        }
};

template <class T>
class LinkedList {
    private:

        Node<T> *head;
    public:
        LinkedList() {
            head = nullptr;
        }
        /*
        Añade  T value a la lista
        @Param T value: elemento añadir del tipo T T
        */
        void add(T value) {
            Node<T> *new_node = new Node<T>(value);
            if (head == nullptr) {
                head = new_node;
            }
            else {
                Node<T> *current = head;
                while (current->next != nullptr) {
                    current = current->next;
                }
                current->next = new_node;
            }
        }
};

 


int main()
{
    LinkedList <int> *lista = new LinkedList<int>();
}
