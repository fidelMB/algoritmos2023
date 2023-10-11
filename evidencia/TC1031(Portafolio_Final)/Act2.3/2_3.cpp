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

/*
* Clase que representa los datos de una línea de la bitacora
*/
class RowData {
private:
    string year, month, day, hour, IP, message;

public:
	/*
	* Constructor
	* @return Instancia de la clase RowData
	* Complejidad tiempo O(1)
	* Complejidad espacio O(1)
    */
    RowData() {
        year = "";
        month = "";
        day = "";
        hour = "";
        IP = "";
        message = "";
    }
	
	/*
	* Constructor con parámetros
	* @param year
	* @param month
	* @param day
	* @param hour
	* @param IP
	* @param message
	* @return Instancia de RowData
	* Complejidad tiempo O(1)
	* Complejidad espacio O(1)
	*/
    RowData(string year, string month, string day, string hour, string IP, string message) {
        this->year = year;
        this->month = month;
        this->day = day;
        this->hour = hour;
        this->IP = IP;
        this->message = message;
    }

	/*
	 * Regresa los datos de la fila en un string
	 * @return string con los datos de la fila
	 * Complejidad tiempo: O(1)
	 * Complejidad espacio: O(1)
	*/
    string getRowData() {
        string RowData = year + " " + month + " " + day + " " + hour + "|" + IP + "|" + message + "\n";
        return RowData;
    }

    /*
	* Método que da formato al mes y lo combina con las demás partes de la fecha
	* @return string con la fecha formateada
	* Complejidad tiempo O(1)
	* Complejidad espacio O(1)
    */
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
};

/*
* Clase que representa un nodo de una lista ligada
*/
template <class T>
class Node {
private:
    T data;
    Node<T>* next;

public:
	/*
	* Constructor
	* @return Instancia de la clase Node
	* Complejidad tiempo O(1)
	* Complejidad espacio O(1)
	*/
    Node(T data) {
        this->data = data;
        next = nullptr;
    }

	/*
	* Getter de la data del nodo
	* @return data
	* Complejidad tiempo O(1)
	* Complejidad espacio O(1)
	*/
    T getData() {
        return data;
    }

	/*
	* Recibe un puntero y lo asigna como el que sigue de este nodo
	* @param next
	* Complejidad tiempo O(1)
	* Complejidad espacio O(1)
	*/
	void setNext(Node<T>* next) {
		this->next = next;
	}

	/*
	* Getter del puntero al siguiente nodo
	* @return next
	* Complejidad tiempo O(1)
	* Complejidad espacio O(1)
	*/
    Node<T>* getNext() {
        return next;
    }

};

// Puntero global que apunta a la cabeza de la lista ligada
Node<RowData>* globalPtr;

/*
* Clase que representa una lista ligada
*/
template <class T>
class linkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:

	/*
	* Constructor
	* @return Instancia de la clase linkedList
	* Complejidad tiempo O(1)
	* Complejidad espacio O(1)
	*/
    linkedList() {
        head = nullptr;
        tail = nullptr;
    }

    /*
	* Destructor de la clase linkedList
	* Complejidad tiempo O(n)
	* Complejidad espacio O(1)
    */
	~linkedList() {
		Node<T>* curr = head;
		Node<T>* next;
		while (curr != nullptr) {
			next = curr->getNext();
			delete curr;
			curr = next;
		}
	}
	
    /*
	* Añade un nodo a la lista como la cabeza
    *
    * Si no hay nodos, se crea el primero, y si ya hay nodos, se
    * agrega un nodo al inicio de la lista
    *
	* @param data: dato del nodo
	* @param head_ref puntero al puntero de la cabeza de la lista
    * Complejidad tiempo: O(1)
    * Complejidad espacio: O(1)
    */
    void addNode(Node<T>** head_ref, T data) {
        Node<T>* new_node = new Node<T>(data);
        if (*head_ref == nullptr) {
            *head_ref = new_node;
            globalPtr = *head_ref;
        }
        else {
            (*head_ref)->setNext(new_node);
            *head_ref = new_node;
        }
    }

    /*
	* Imprime la lista ligada
    *
    * Se imprimen los datos de todos los nodos
    * dentro la lista recorriendo toda la lista
    *
	* @param node: la cabeza de la lista
    * Complejidad tiempo: O(n)
    * Complejidad espacio: O(1)
    */
    void printList(Node<T>* node) {
        while (node != nullptr) {
            cout << node->getData().getRowData();
            node = node->getNext();
        }
    }
};

/*
* Regresa la longitud de una lista ligada
* 
* @param current: cabeza de la lista
* @return longitud de la lista
* Complejidad tiempo: O(n)
* Complejidad espacio: O(1)
*/
template <class T>
int length(Node<T>* current) {
    int count = 0;
    while (current != nullptr) {
        current = current->getNext();
        count++;
    }
    return count;
}

/*
* merge para unir dos partes ordenadas de una lista ligada
* 
* Se obtienen dos sublistas, se ordenan, y se unen al final. No se crea una nueva lista ligada, 
* se modifican los punteros de los nodos de las listas ligadas que se están uniendo por lo que no se 
* utiliza memoria extra
*
* @param start1: nodo inicial de la primera lista
* @param end1: nodo final de la primera lista
* @param start2: nodo inicial de la segunda lista
* @param end2: nodo final de la segunda lista
* Complejidad tiempo: O(n)
* Complejidad espacio: O(1)
*/
template <class T>
void merge(Node<T>** start1, Node<T>** end1, Node<T>** start2, Node<T>** end2) {

    /* Comparar el primer nodo de cada lista, e intercambiarlos en 
    caso de que el primer nodo de la lista 1 sea mayor que el de la lista 2
    */
    Node<T>* temp = nullptr;
    if ((*start1)->getData().getDate() > (*start2)->getData().getDate()) {
        swap(*start1, *start2);
        swap(*end1, *end2);
    }

    /* Crear nodos temporales, y comparar los nodos después del nodo inicial de cada lista
    que se está comparando, e intercambiarlos en caso de que el nodo de la lista 1 sea mayor que el de la lista 2. 
    Se va a iterar por cada nodo de las listas y al final va a quedar una sola lista ligada ordenada
    */
    Node<T>* astart = *start1, *aend = *end1;
    Node<T>* bstart = *start2, *bend = *end2;
    Node<T>* bendnext = (*end2)->getNext();
    while (astart != aend && bstart != bendnext) {
        if (astart->getNext()->getData().getDate() > bstart->getData().getDate()) {
            temp = bstart->getNext();
            bstart->setNext(astart->getNext());
            astart->setNext(bstart);
            bstart = temp;
        }
        astart = astart->getNext();
    }
    if (astart == aend) {
        astart->setNext(bstart);
    }
    else {
        *end2 = *end1;
    }
}

/*
* mergeSort, ordena una lista ligada de menor a mayor
* 
* Se ingresa el puntero que apunta al puntero de la cabeza de la lista ligada, y se ordena la lista ligada con
* el algoritmo merge sort. En esta versión se crean sublistas y gaps, el tamaño del gap define la cantidad de nodos que va
* a tener cada sublista, se van a ordenar y unir las sublistas de menor a mayor con el método merge() hasta que se unan todas
* las sublistas y quede una sola lista ligada ordenada
*
* @param head: puntero al puntero de la cabeza de la lista
* @return 
* Complejidad tiempo: O(n*log(n))
* Complejidad espacio: O(1)
*/
template <class T>
void mergeSort(Node<T>** head)
{
    // No se hace nada si la lista está vacía o tiene un solo nodo
    if (*head == NULL || (*head)->getNext() == nullptr) {
        return;
    }

    /*
    * Se definen 4 nodos para los grupos de nodos que se van a unir dependiendo del gap
    * y se obtiene la longitud de la lista para saber cuántas iteraciones hacer
    */
    Node<T>* start1 = nullptr, * end1 = nullptr;
    Node<T>* start2 = nullptr, * end2 = nullptr;
    Node<T>* prevend = nullptr;
    int len = length(*head);

    // Se va a crear un espacio entre los nodos, este va ir incrementando de 1 a 2, 4, 8, 16 etc.	
    for (int gap = 1; gap < len; gap = gap * 2) {
        start1 = *head;
        while (start1 != nullptr) {

            // Solo para la primera iteración
            bool isFirstIter = 0;
            if (start1 == *head) {
                isFirstIter = 1;
            }

            // Se encuentra el nodo final de la primera sublista
            int counter = gap;
            end1 = start1;
            while (--counter && end1->getNext() != nullptr) {
                end1 = end1->getNext();
            }

            // Se define el nodo inicial de la segunda sublista
            start2 = end1->getNext();
            if (start2 == NULL) {
                break;
            }

            // Se encuentra el nodo final de la primera sublista
            counter = gap;
            end2 = start2;
            while (--counter && end2->getNext() != nullptr) {
                end2 = end2->getNext();
            }

            // Se utilizará para definir el primer nodo en la siguiente iteración
            Node<T>* temp = end2->getNext();

            // Se ordenan las dos sublistas
            merge(&start1, &end1, &start2, &end2);

            // Se define el primer nodo de la siguiente iteración
            if (isFirstIter) {
                *head = start1;
            }
            else {
                prevend->setNext(start1);
            }
            prevend = end2;
            start1 = temp;
        }
        prevend->setNext(start1);
    }
}

/*
* Escribe los datos de una lista ligada en un archivo de texto
* @param node: cabeza de la lista
* @param filename: nombre del archivo
* Complejidad tiempo: O(n)
* Complejidad espacio: O(1)
*/
template <class T>
void toTxtFile(Node<T>* node, string fileName) {
    fstream bitacora;

    bitacora.open(fileName, ios::out);

    while (node != nullptr) {
        bitacora << node->getData().getRowData();
        node = node->getNext();
    }

    bitacora.close();
}

/*
* Imprime los datos de una lista ligada entre 2 fechas dadas por el usuario
* Complejidad tiempo: O(n)
* Complejidad espacio: O(1)
*/
void printListBetweenDates() {
	string day, month, year, hour;
    Node<RowData>* current = globalPtr;
	cout << "Date of the start of the search " << endl;
	cout << "Day: ";
	cin >> day;
	cout << "Month (3 letters): ";
	cin >> month;
	cout << "Year: ";
	cin >> year;
	cout << "Hour: (hh:mm:ss) ";
	cin >> hour;
    
	RowData initialRowData(year, month, day, hour, "0","0");
	string initialDate = initialRowData.getDate();
	cout << "Date of the end of the search " << endl;
    cout << "Day: ";
    cin >> day;
    cout << "Month (3 letters): ";
    cin >> month;
    cout << "Year: ";
    cin >> year;
    cout << "Hour: (hh:mm:ss) ";
    cin >> hour;
    RowData finalRowData(year,month, day, hour, "0", "0");
    string finalDate = finalRowData.getDate();

	while (current != nullptr) {
		if (current->getData().getDate() >= initialDate && current->getData().getDate() <= finalDate) {
			cout << current->getData().getRowData();
		}
		current = current->getNext();
	}
	
	delete current;
}

int main() {
    // Se abre el archivo de la bitácora
    ifstream bitacora;
    bitacora.open("bitacoraelb.txt");
    string line, year, month, day, hour, IP, message;
    int option = 1;

    linkedList<RowData>* list = new linkedList<RowData>();
    Node<RowData>* ptr = nullptr;

    // Se lee el archivo y se agregan los nodos con la información de las filas a la lista ligada
    while (getline(bitacora, year, ' ')) {
        getline(bitacora, month, ' ');
        getline(bitacora, day, ' ');
        getline(bitacora, hour, '|');
        getline(bitacora, IP, '|');
        getline(bitacora, message, '\n');
        list->addNode(&ptr, RowData(year, month, day, hour, IP, message));
    }

    // Se cierra el archivo, se ordena la lista ligada, y se guardan los datos en un archivo .txt
    bitacora.close();
    mergeSort(&globalPtr);
    toTxtFile(globalPtr, "bitacoraelbOrdenada.txt");

	// Menu
    while (option != 3) {
		cout << "What do you want to do?" << endl;
		cout << "1. Print data between two dates " << endl;
		cout << "2. Print all data ordered by date" << endl;
		cout << "3. Exit" << endl;
		
		cin >> option;
		
        if (option == 1) {
            printListBetweenDates();
            cout << endl;
        }
		else if (option == 2) {
            list->printList(globalPtr);
		}
		else if (option == 3) {
			break;
		}
		else {
			cout << "Invalid option" << endl;
		}
    }
	
	delete list;
    return 0;
};

/* Bibliografía:
    GeeksforGeeks. (2022). Iterative merge sort for linked list. GeeksforGeeks. 
        https://www.geeksforgeeks.org/iterative-merge-sort-for-linked-list/

*/
