#ifndef TP_ALGO_III_KGrafoS_H
#define TP_ALGO_III_KGrafoS_H

#include <list>
#include <vector>
#include <type_traits>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <stack>
#include <queue>
#include "auxiliar.cpp"

using namespace std;

struct Arista;
class KGrafo;
class weightedGraph;


struct Arista
{
    int src;
    int dest;
    float costo;
    Arista(int src, int dest, float &costo);
    Arista &operator=(Arista &aCopiar);
};

ostream& operator<<(ostream& os, const Arista &a);

class KGrafo
{
private:
    unsigned int _totalVertices;
    unsigned int _totalAristas;
    TMatrix<float> _matriz;
    vector<Arista> _aristas;

    void completarConCeros(vector<int> &v);
    
public:

    // Constructor del grafo completo, toma la cantidad de vertices para asignar el espacio para la matriz
    KGrafo(unsigned int cantidadVertices);

    // Devuelve la cantidad de vertices
    unsigned int getCantidadVertices();

    //Agrega una arista al grafo en formato arista
    void agregarArista(Arista &arista);
    //Mismo que el de arriba, pero no en formato arista
    void agregarArista(int src, int dest, float costo);

    void imprimir();

    //El buen Kruskal, devuelve un arbol generador minimo con representacion de lista
    weightedGraph Kruskal();
    vector<int> KruskalHeuristica();

    //Dado un vertice a y b, devuelve el costo entre ellos
    vector<Arista> getAristas();
    float getCosto(int src, int dest);


};

class weightedGraph
{
private:

    int _totalVertices;
    int _totalAristas;
    list<Arista> *adjLists;
    vector<Arista> _aristas;



    
    //void imprimirCaminoYCosto(list<int> &caminoHamiltoneano, KGrafo &grafo);

public:
    weightedGraph(unsigned int cantidadVertices);
    void agregarArista(Arista &arista);
    vector<int> DFS(KGrafo &grafo);
    int getCantVecinos(int src);
    vector<int> getCaminoHamiltoneano();
     ~weightedGraph();
};

#endif //TP_ALGO_III_KGrafoS_H
