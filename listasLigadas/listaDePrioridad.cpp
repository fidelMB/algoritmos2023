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
class Node
{
public:
    T data;
    int priority=0;
    Node<T>* next;
    Node<T>* previous;
    Node(T dataValue,int p) {
        data = dataValue;
        priority = p;
        next = nullptr;
        previous = nullptr;
    }  

};


template <class T>
class PriorityQueue {
private:

    Node<T>* head;
    Node<T>* tail;

public:
    PriorityQueue() {
        head = nullptr;
        tail = nullptr;
    }
    ~PriorityQueue() {
        while (head != NULL) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = NULL;


    }
 
    void add(T data, int p) {
        Node<T> *new_node = new Node<T>(data, p);
    
    }
    void remove()
    {
        if (head == nullptr) {
            return;
        }
        else {

            Node<T>* temp = head;
            Node<T>* new_head = head->next;
            if (new_head == nullptr) {
                delete temp;
                tail = nullptr;
                head = nullptr;

            }
            else {
                head = new_head;
                head->previous = nullptr;
                delete temp;
            }

        }
    }


    T peek()
    {
        if (head == nullptr) {
            return NULL;
        }
        else {
            return head->data;
        }
    }

    void printList()
    {
        Node<T>* current = head;
        while (current != NULL) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << "\n";
    }


};

 


int main()
{
    PriorityQueue <int>* pqueue = new PriorityQueue<int>();
    pqueue->add(2, 3);
 
}
