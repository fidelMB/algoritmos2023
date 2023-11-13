/*
Act 1.3 - Actividad Integral de Conceptos Básicos y Algoritmos Fundamentales
Integrantes:
Andrés Emiliano de la Garza Rosales  a01384096
Rodrigo de Jesús Meléndez Molina a00831646
Fidel Morales Briones A01198630
7 de septiembre de 2023
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct message {
    int year;
    string month;
    int day;
    string time;
    long long ip;
    string info;
};

/*
Combinar dos vectores ordenados en uno solo

Toma 3 argumentos, un vector un indice izquierdo
y un indice derecho, si el indice l es igual al indice r
entonces no hay elementos por combinar.

@param un vector con n valores enteros
@return se modifica el vector dado directamente, no se regresa ningun valor
Tiempo: O(n)
Espacio: O(n)
*/
void merge(vector<message>& v, int l, int r) {
    if (l == r) {
        return;
    }

    int mid = l + (r - l) / 2;
	// calculo para obtener un indice a la mitad del vector
    int rIndex = 0, lIndex = 0, lSize = mid - l + 1, rSize = r - mid;
    int vIndex = l;
	/* 
    crea un indice para rastrear la posición en el vector original
	mientras se realiza la combinacion 
	*/
    vector<message> leftV(lSize);
    vector<message> rightV(rSize);
	// almacenamiento temporal de los subvectores

    for (int i = l; i <= mid; i++) {
        leftV[i - l] = v[i];
    }
	// Ciclo para crear el subvector izquierdo
    for (int i = mid + 1; i <= r; i++) {
        rightV[i - mid - 1] = v[i];
    }
	// Ciclo para crear el subvector derecho

    while (lIndex < lSize && rIndex < rSize) {
        if (leftV[lIndex].ip < rightV[rIndex].ip) {
            v[vIndex] = leftV[lIndex];
            lIndex++;
        }
        else {
            v[vIndex] = rightV[rIndex];
            rIndex++;
        }
        vIndex++;
    }

    while (lIndex < lSize) {
        v[vIndex] = leftV[lIndex];
        lIndex++;
        vIndex++;
    }

    while (rIndex < rSize) {
        v[vIndex] = rightV[rIndex];
        rIndex++;
        vIndex++;
    }
}

/*
MergeSort con los ip's de un vector de estructuras message

Se ordena una seccion de un vector de n valores con el metodo de merge
funcion encargada de ordenar la “ip”
@param un vector con n message
@param el primer indice de la seccion a ordenar
@param el ultimo indice de la seccion a ordenar
@return se modifica el vector dado directamente, no se regresa ningun valor

Tiempo: O(n*log(n))
Espacio: O(n)
*/
void mergeSortByIp(vector<message>& v, int l, int r) {
    if (l >= r) {
        return;
    }

    int mid = l + (r - l) / 2;
	// calculo para obtener un indice a la mitad del vector
    mergeSortByIp(v, l, mid);
    mergeSortByIp(v, mid + 1, r);
	/*
	llamada recursiva para ordenar la mitad l y r del rango 
	respectivamente y ordena los subvectoes
	*/
    merge(v, l, r);
	// funcion merge para combinar los subvectores ordenados

    return;
}

/*
Convertir ip's a tipo de variable long long

funcion que se utiliza para convertir la direccion IP
representada por strings a un número largo representado por
un valor numerico

@param cuatro strings con los valores de una IP
@return una IP en tipo de variable long long
Tiempo: O(1)
Espacio: O(1)
*/
long long ipToLong(string ip1, string ip2, string ip3, string ip4) {
    string current, ip = "";
	// construir la ip a formato de vector
    vector<string> ips = { ip1, ip2, ip3, ip4 };
	// almacena las 4 partes del ip en un un vector “ips"
   
    if (ips[0][0] == ' ') {
        ips[0].erase(0, 1);
    }
	/*
	verifica si el primer indice de la ip es un espacio en blanco
	para saber si la ip se encuentra en el formato esperado
	*/

    for (int i = 0; i < 4; i++) {
        current = ips[i];

        if (current.length() == 1) {
            ip += "00" + current;
        }
        else if (current.length() == 2) {
            ip += "0" + current;
        }
        else {
            ip += current;
        }
    }
	
	//Se asegura de que cada parte de ip tenga 3 digitos
    return stoll(ip);
}

/*
Trasnferir datos un txt a un vector de messages

Lee el archivo y almacena la información en una estructura message
para después condensar la información en un vector de messages

@param vector con n messages, nombre del archivo
@return un vector con n messages con todos los datos del archivo
Tiempo: O(n)
Espacio: O(n)
*/
void fileToVector(vector<message>& v, string fileName) {
    fstream bitacora;
	//instancia de fstream para manejar el archivo
    message temp;
	//almacenamiento temporal de los datos
    string line, ip1, ip2, ip3, ip4;
	
    bitacora.open(fileName, ios::in);

    while (getline(bitacora, line, ' ')) {
        temp.year = stoi(line);
        getline(bitacora, temp.month, ' ');
        getline(bitacora, line, ' ');
        temp.day = stoi(line);
	/*
	leer cada linea del archivo separando los valores con espacios
	en blanco y lo guarda en temp.year, temp.month y temp.day
	respectivamente
	*/
        getline(bitacora, temp.time, ' ');
       
        getline(bitacora, line, ':');
        getline(bitacora, ip1, '.');
        getline(bitacora, ip2, '.');
        getline(bitacora, ip3, '.');
        getline(bitacora, ip4, ' ');
	// lee las partes de la ip separadas por puntos
        temp.ip = ipToLong(ip1, ip2, ip3, ip4);
    // convierte las partes de la ip en un valor numerico


        getline(bitacora, line, ':');
	// lee hasta encontrar “:” en “line”
        getline(bitacora, line);
	// almacena el resto de la linea en “line”
        line.erase(0, 1);
	// elimina el espacio en blanco
        temp.info = line;
	// almacena el contenido en la variable temp.info
       
        v.push_back(temp);  
	// agrega “temp” al vector “v”
    }
}

/*
Trasnferir datos dentro de un vector de messages a un txt

Manda los datos ya ordenados dentro de un vector que contiene messages a un archivo .txt. 
Se logra con un ciclo for y se va imprimiendo la información en cada fila de manera ordenada.

@param un vector con n messages y el nombre del archivo nuevo
@return un archivo .txt con los datos del vector de messages
Tiempo: O(n)
Espacio: O(n)
*/
void toTxtFile(vector<message> v, string fileName) {
	fstream bitacora;
	string ipString;
	
	bitacora.open(fileName, ios::out);

	for (int i = 0; i < v.size(); i++) {
		bitacora << v[i].year << " " << v[i].month << " ";
        // escribe el año y mes separado por espacios
		if (v[i].day < 10) {
			bitacora << '0';
		}
        // si el día es menor a 10 entonces agrega un 0
		bitacora << v[i].day << " " << v[i].time << " | IP: ";
		
		ipString = to_string(v[i].ip);
		while (ipString.length() != 12) {
			ipString = "0" + ipString;
		}
        // revisar que la longitud de ip sea de 12 sino, se agregan 0
		bitacora << stoi(ipString.substr(0, 3)) << '.' << stoi(ipString.substr(3, 3)) << '.' << stoi(ipString.substr(6, 3)) << '.' << stoi(ipString.substr(9, 3));
		bitacora << " | INFO: " << v[i].info << endl;
        // dividir la ip en partes para obtenerla en el formato correcto
	}

	bitacora.close();
}

/*
Busqueda binaria para encontrar el siguiente elemento menor

Versión modificada de la búsqueda binaria. Va a buscar el siguiente 
elemento menor al que se le indique en la entrada

@param un vector con n messages y el número objetivo
@return el índice del número objetivo
Tiempo: O(log(n))
Espacio: O(1)
*/
int binarySearchNextSmallest(vector<message> v, long long target) {
    int start = 0, end = v.size()-1;
	// indices de inicio y fin del vector
    int ans = end+1;
	// variable que almacena el resultado deseado
   
    while (start <= end) {
        int mid = (start + end) / 2;

        if (v[mid].ip >= target) {
            start = mid + 1;
        }
        else {
            ans = mid;
            end = mid - 1;
        }
	/*
	compara el valor de la ip de la mitad con la ip que se busca
	si el valor de la mitad del vector es mayor o igual al objetivo
	entonces actualiza la variable start para buscar en la parte
	derecha del vector, sino busca en la mitad izquierda
	*/
    }
    return ans;
}

/*
Imprime los campos de inforación de un message

Se imprimen en la terminal con el mismo formato del archivo .txt original 
para tener consistencia en la legibilidad de los datos

@param un message
@return se imprimen los datos en la terminal 
Tiempo: O(1)
Espacio: O(1)
*/
void printFormattedInfo(message m) {
    string ipString;

    cout << m.year << " " << m.month << " ";
    if (m.day < 10) {
        cout << '0';
    }
    // imprime el año mes y día

    cout << m.day << " " << m.time << " | IP: ";
      // imprime el día y hora 
    ipString = to_string(m.ip);

    while (ipString.length() != 12) {
        ipString = "0" + ipString;
    }
	// aseguramos que ip tenga longitud de 12, sino se agregan 0

    cout << stoi(ipString.substr(0, 3)) << '.' << stoi(ipString.substr(3, 3)) << '.' << stoi(ipString.substr(6, 3)) << '.' << stoi(ipString.substr(9, 3));
	// imprime el formato de la ip correcto separado por puntos
    cout << " | INFO: " << m.info << endl;
}

int main() {
    vector<message> messages;
    string ipStart, ipEnd;
    long long ipS, ipE;
    int ip, endIndex, startIndex;
    string ipString;
    vector<string> ipDivided;
   
    fileToVector(messages, "bitacoraelb.txt");
    mergeSortByIp(messages, 0, messages.size() - 1);
   
    cout << "Introduzca IP mayor: ";
    cin >> ipStart;
    cout << "Introduzca IP menor: ";
    cin >> ipEnd;
   
   //se cambia el formato de la ip's para buscarlas en el vector de messages
    ipString = "";
    for (int i = 0; i < ipStart.length(); i++) {
        if (ipStart.at(i) == '.') {
            ipDivided.push_back(ipString);
            ipString = "";
        }
        else {
            ipString += ipStart.at(i);
        }
    }

    ipDivided.push_back(ipString);
    ipString = "";

    ipS = ipToLong(ipDivided[0], ipDivided[1], ipDivided[2], ipDivided[3]);
    ipDivided.clear();

    for (int i = 0; i < ipEnd.length(); i++) {
        if (ipEnd.at(i) == '.') {
            ipDivided.push_back(ipString);
            ipString = "";
        }
        else {
            ipString += ipEnd.at(i);
        }
    }

    ipDivided.push_back(ipString);

    ipE = ipToLong(ipDivided[0], ipDivided[1], ipDivided[2], ipDivided[3]);

    startIndex = binarySearchNextSmallest(messages, ipS+1);
    endIndex = binarySearchNextSmallest(messages, ipE+1);

    //se imprimen los datos solicitados
    for (int i = startIndex; i <= endIndex; i++) {
        printFormattedInfo(messages[i]);
    }

    /*
    se crea un nuevo archivo .txt con los datos ordenados por
    orden descendente de ip
    */
    toTxtFile(messages, "bitacoraelbSorted.txt");

    return 0;
}





