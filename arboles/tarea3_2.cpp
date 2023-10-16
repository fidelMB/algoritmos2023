/*
Act 3.2 - Árbol Heap: Implementando una fila priorizada
Fidel Morales Briones A01198630
16 de octubre de 2023
*/
#include <iostream>
using namespace std;

class priorityQueue {
public:
    int heapArray[1000];
    int size = 0;

    priorityQueue() {
    }

    /*
    * push, inserta un nuevo valor dentro del arreglo heap
    * 
    * Se agrega un valor dentro del arreglo heap, y se utiliza el método swiftUp para acomodar el arreglo
    * para que el valor recién agregado se encuentre en la posición correcta
    * 
    * @param value: dato a insertar
    * @return: no tiene
    * Complejidad tiempo: O(log(n))
    * Complejidad espacio: O(1)
    */
    void push(int value) {
            heapArray[size] = value;
            size++;
            if (size > 1) {
                swiftUp((size / 2) - 1);
            }
    }

    /*
    * pop, elimina el valor con mayor prioridad dentro del arreglo heap
    * 
    * El valor de mayor prioridad del heap se va hasta el final del arreglo, y se 
    * utiliza el método swiftDown para acomodar el arreglo
    * 
    * @param: no tiene
    * @return: no tiene
    * Complejidad tiempo: O(log(n))
    * Complejidad espacio: O(1)
    */
    void pop() {
        
        int temp = heapArray[size - 1];
        heapArray[size-1] = heapArray[0];
        heapArray[0] = temp;
        size--;
        if (size > 1) {
            swiftDown(0);
        }
    }

    /*
    * top, regresa el valor con mayor prioridad dentro del arreglo heap
    * 
    * regresa el valor en la posición 0 del arreglo
    * 
    * @param: no tiene
    * @return: el entero que está en la posición 0 del arreglo
    * Complejidad tiempo: O(1)
    * Complejidad espacio: O(1)
    */
    int top() {
        return heapArray[0];
    }

    /*
    * empty, regresa si el arreglo heap está vacío o no
    * 
    * regresa true si el arreglo está vacío, false si no
    * 
    * @param: no tiene
    * @return: valor booleano que indica si el arreglo está vacío o no
    * Complejidad tiempo: O(1)
    * Complejidad espacio: O(1)
    */
    bool empty() {
        return size == 0;
    }

    /*
    * size, regresa el tamaño del arreglo heap
    * 
    * regresa el atributo size de la clase, que indica el tamaño del arreglo heap
    * 
    * @param: no tiene
    * @return: entero que indica el tamaño del arreglo heap
    * Complejidad tiempo: O(1)
    * Complejidad espacio: O(1)
    */
    int Size() {
        return size;
    }

    /*
    * swap, intercambia dos valores dentro del arreglo heap
    * 
    * dos valores se interacambian dentro del arreglo heap, se utiliza dentro de los métodos
    * swiftUp y swiftDown. Se crea una variable temporal para completar el intercambio
    * 
    * @param y: entero que indica la posición del primer valor a intercambiar
    * @param x: entero que indica la posición del segundo valor a intercambiar
    * @return: no tiene
    * Complejidad tiempo: O(1)
    * Complejidad espacio: O(1)
    */
    void swap(int x, int y) {
        int temp = heapArray[x];
        heapArray[x] = heapArray[y];
        heapArray[y] = temp;

    }

    /*
    * swiftUp, ordena el arreglo cuando un valor se agrega al final del arreglo
    * 
    * revisa si el valor recién agregado es mayor que su padre, si es así, se intercambian,
    * así hasta que todos los valores dentor del arreglo estén ordenados y cumplan con la 
    * condicion de un heap
    * 
    * @param rootIndex: índice del último nodo que tiene por lo menos un hijo
    * @return: no tiene
    * Complejidad tiempo: O(log(n))
    * Complejidad espacio: O(1)
    */
    void swiftUp(int rootIndex) {
        int max = rootIndex;
        int left = (2 * rootIndex) + 1;
        int right = (2 * rootIndex) + 2;

        if (left < size && heapArray[max] < heapArray[left]) {
            max = left;
        }
        if (right < size && heapArray[max] < heapArray[right]) {
            max = right;
        }

        if (max != rootIndex) {
            swap(max, rootIndex);
            swiftUp((rootIndex-1)/2);
        }
    }

    /*
    * swiftDown, ordena el arreglo cuando un valor se elimina del inicio del arreglo y el último valor se coloca en el inicio
    * 
    * revisa si el valor recién agregado es menor que su hijo, si es así, se intercambian,
    * así hasta que todos los valores dentor del arreglo estén ordenados y cumplan con la 
    * condicion de un heap
    * 
    * @param rootIndex: índice del nodo con mayor prioridad
    * @return: no tiene
    * Complejidad tiempo: O(log(n))
    * Complejidad espacio: O(1)
    */
    void swiftDown(int rootIndex) {
        int max = rootIndex;
        int left = (2 * rootIndex) + 1;
        int right = (2 * rootIndex) + 2;

        if (left < size && heapArray[max] < heapArray[left]) {
            max = left;
        }
        if (right < size && heapArray[max] < heapArray[right]) {
            max = right;
        }

        if (max != rootIndex) {
            swap(max, rootIndex);
            swiftDown(max);
        }
    }

    /*
    * print, imprime el arreglo heap
    * 
    * imprime todos los valores dentro del heap
    * 
    * @param: no tiene
    * @return: se imprimen los valores en la terminal
    * Complejidad tiempo: O(n)
    * Complejidad espacio: O(1)
    */    
    void print() {
        for (int i = 0; i < size; i++) {
            cout << heapArray[i] << " ";
        }
        cout << endl;
    }

    /*
    * print, imprime sola una parte del arreglo heap
    * 
    * dependiendo del parámetro fullSize, imprime esa cantidad de valores del arreglo heap
    * 
    * @param fullSize: cantidad de valores que se quieren imprimir
    * @return: se imprimen los valores en la terminal
    * Complejidad tiempo: O(n)
    * Complejidad espacio: O(1)
    */ 
    void print(int fullSize) {
        for (int i = 0; i < fullSize; i++) {
            cout << heapArray[i] << " ";
        }
        cout << endl;
    }

};

int main()
{
    priorityQueue *listaPrioridadHeap = new priorityQueue();
    listaPrioridadHeap->push(5);
    listaPrioridadHeap->push(7);
    listaPrioridadHeap->push(8);
    listaPrioridadHeap->push(9);
    listaPrioridadHeap->push(10);
    listaPrioridadHeap->push(12);
    listaPrioridadHeap->push(5);
    listaPrioridadHeap->push(14);
    listaPrioridadHeap->push(11);
    listaPrioridadHeap->print();

    listaPrioridadHeap->pop();
    listaPrioridadHeap->print();
    listaPrioridadHeap->pop();
    listaPrioridadHeap->print();
    listaPrioridadHeap->pop();
    listaPrioridadHeap->print();
    listaPrioridadHeap->pop();
    listaPrioridadHeap->print();
    listaPrioridadHeap->pop();
    listaPrioridadHeap->print();
    listaPrioridadHeap->pop();
 

    listaPrioridadHeap->print();
    listaPrioridadHeap->print(7);


}