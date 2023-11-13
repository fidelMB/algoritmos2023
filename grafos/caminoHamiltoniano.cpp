#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct Arista {
    int origen, destino;
};

class Grafo
{
public:
    vector<vector<int>> adyacencias;

    /*
     Construye un grafo de n vertices recibiendo un vector de aristas 
     @param vector<Arista> const& aristas: vecotor con aristas
     @param int n: cantidad de nodos
    */
    Grafo(vector<Arista> const& aristas, int n)
    {
        adyacencias.resize(n);
        for (Arista arista : aristas)
        {
            int origen = arista.origen;
            int destino = arista.destino;
            adyacencias[origen].push_back(destino);
            adyacencias[destino].push_back(origen);
        }
    }
};

/*
* Imprime ruta
*/
void imprimirRuta(vector<int> const& ruta)
{
    for (int i : ruta) {
        cout << i << ' ';
    }
    cout << endl;
}

void caminosHamiltonianos(Grafo const& grafo, int nodoActual, vector<bool>& visitados, vector<int>& ruta, int n) {

    if (ruta.size() == n) {
        imprimirRuta(ruta);
        return;
    }

    for(int i = 0; i < grafo.adyacencias[nodoActual].size(); i++) {
        if (visitados[i] == false) {
            ruta.push_back(grafo.adyacencias[nodoActual][i]);
            visitados[i] = true;
        }
    }

    for(int destino : grafo.adyacencias[nodoActual]) {
       if (destino){
            cout << "hola" << endl;
       }
    }

}

void GeneraCaminosHamiltonianos(Grafo const& grafo, int n)
{
    /*
    Considera que un camino hamiltoniano puede iniciar de diferentes nodos es por eso que
    debebos generar cada camino posible con todos los diferentes nodos iniciales
    */ 
    for (int i = 0; i < n; i++)
    {
        /*
        Inicializamos un vector que nos represente nuestra ruta actual y añadimos nodo inicia
        y lo marcamos como visitado
        */
        vector<int> ruta;
        ruta.push_back(i);
        vector<bool> visitados(n);
        visitados[i] = true;
        /*
         generar los caminos posibles a partir del nodo inicial
        */
        caminosHamiltonianos(grafo, i, visitados, ruta, n);
    }
}

int main()
{
    int n = 5;
    vector<Arista> aristas = {
        {0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 3},{4,3},{4,0}
    };
    Grafo grafo(aristas, n);
    GeneraCaminosHamiltonianos(grafo, n);

    vector<Arista> aristas2 = {
        {0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 3}
    };

    Grafo grafo2(aristas2, 4);
    GeneraCaminosHamiltonianos(grafo2, 4);

    return 0;
}