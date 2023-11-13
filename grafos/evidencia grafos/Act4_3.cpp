/*
Act 4.3 - Actividad Integral de Grafos (Evidencia Competencia) 
Integrantes:
Andrés Emiliano de la Garza Rosales  a01384096
Rodrigo de Jesús Meléndez Molina a00831646
Fidel Morales Briones A01198630
13 de noviembre de 2023
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <fstream>

using namespace std;

/*
* loadGraph, se carga el grafo de un archivo de texto
*
* Se carga un archivo de texto y se lee línea por línea. Se crea una lista 
* de adyacencia. Se obtienen las aristas y se agregan a la lista de adyacencia
* de un grafo no dirigido.
*
* @param filename: nombre del archivo de texto
* @return: adjacencyList, lista de adyacencia de un grafo no dirigido
* Complejidad tiempo: O(v + e)
* Complejidad espacio: O(v + e)
*/
vector<vector<int>> loadGraph(string filename) {
	ifstream file(filename);
    string line, vertices, edges, u, v;

    getline(file, vertices, ' ');
	vector<vector<int>> adjacencyList(stoi(vertices));

	getline(file, edges, '\n');
    for (int i = 0; i < stoi(edges); i++) {
        getline(file, u, ' ');
		getline(file, v, '\n');
        adjacencyList[stoi(u)].push_back(stoi(v));
		adjacencyList[stoi(v)].push_back(stoi(u));
    }

	return adjacencyList;
}

/*
* BFS, búsqueda en anchura modficada
*
* Se realiza una búsqueda en anchura a partir de un vértice inicial. Se utiliza un vector de distancias para almacenar
* la distancia de cada vértice al vértice inicial. Se utiliza un contador para almacenar la cantidad
* de vértices infectados. Se recorre la lista de adyacencia del vértice actual y se agregan a la cola
* los vértices descendentes y se incrementa el contador de vértices infectados. Se repite el proceso hasta
* que la cola esté vacía o se alcance el límite de tiempo.
*
* @param adjacencyList: lista de adyacencia del grafo
* @param start: vértice inicial de la búsqueda
* @param limitDistance: cantidad de tiempo que se propaga el virus
* @return: totalInfected, cantidad de vertices infectados
* Complejidad tiempo: O(v + e)
* Complejidad espacio: O(v)
*/
int BFS(vector<vector<int>>& adjacencyList, int start, int limitDistance) {
	queue<int> q;
	vector<int> distance(adjacencyList.size(), -1);
	int totalInfected = 1, current, descendant;

	q.push(start);
	distance[start] = 0;

	while (!q.empty()) {
		current = q.front();
		q.pop();

		if (distance[current] == limitDistance) {
			break;
		}

		for (int i = 0; i < adjacencyList[current].size(); i++) {
			descendant = adjacencyList[current][i];
			if (distance[descendant] == -1) {
				q.push(descendant);
				distance[descendant] = distance[current] + 1;
				totalInfected++;
			}
		}
	}

	return totalInfected;
}

/*
* findMaxVirus, se encuentra la mayor propagación del virus
*
* Con el método BFS, se introducen todos los vértices de un grafo como el vértice inicial y se encuentra
* la cantidad de vértices infectados. Se guardan en un vector los vértices con mayor propagación. Se imprimen
* todos los vértices junto con la cantidad de vértices infectados y finalmente los vértices con mayor propagación.
*
* @param adjacencyList: lista de adyacencia del grafo
* @param time: tiempo de propagación del virus
* @return: impresión en la terminal de los vértices con mayor propagación
* Complejidad tiempo: O(v*(v + e))
* Complejidad espacio: O(v)
*/
void findMaxVirus(vector<vector<int>> &adjacencyList, int time) {
	int totalInfected = 0, source;
	vector<int> sources;

	cout << "Vertice  Infectados" << endl;
	for (int i = 0; i < adjacencyList.size(); i++) {
		int currentInfected = BFS(adjacencyList, i, time);
		cout << i << "            " << currentInfected << endl;
		if (currentInfected >= totalInfected) {
			totalInfected = currentInfected;
			sources.push_back(i);
		}
	}

	cout << "\nMayor propagacion:" << endl;
	for (int i = 0; i < sources.size(); i++) {
		cout << "Vertice: " << sources[i] << " Infectados: " << totalInfected << endl;
	}
}

int main() {
	int time;

	cout << "Grafo 1: " << endl;
	vector<vector<int>> graph1 = loadGraph("grafo1Evidencia.txt");
	cout << "Introduza el tiempo de infeccion: ";
	cin >> time;
	findMaxVirus(graph1, time);

	cout << "\nGrafo 2: " << endl;
	vector<vector<int>> graph2 = loadGraph("grafo2Evidencia.txt");
	cout << "Introduza el tiempo de infeccion: ";
	cin >> time;
	findMaxVirus(graph2, time);

	cout << "\nGrafo 3: " << endl;
	vector<vector<int>> graph3 = loadGraph("grafo3Evidencia.txt");
	cout << "Introduza el tiempo de infeccion: ";
	cin >> time;
	findMaxVirus(graph3, time);

	return 0;
}

/*
* Referencias:
* GeeksforGeeks. (2023, 9 junio). Breadth first search or BFS for a graph. 
* https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/
*/