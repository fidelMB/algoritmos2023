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

int main () {
    fstream bitacora;
    string year, month, day, hour, IP, ip1, ip2, ip3, ip4, message;

    while (getline(bitacora, year, ' ')) {
            getline(bitacora, month, ' ');
            getline(bitacora, day, ' ');
            getline(bitacora, hour, '|');
            getline(bitacora, ip1, '.');
             getline(bitacora, ip1, '.');

            getline(bitacora, ip1, '.');
            getline(bitacora, ip1, '.');

            getline(bitacora, message, '\n');
            list->addNode(&ptr, RowData(year, month, day, hour, IP, message));
        }
}