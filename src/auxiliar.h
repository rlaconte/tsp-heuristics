#ifndef TP_ALGO_III_AUXILIAR_H
#define TP_ALGO_III_AUXILIAR_H

#include <list>
#include <vector>
#include <type_traits>
#include <algorithm>
#include <iostream>
#include <cstdlib>

using namespace std;


template<typename T>
class TMatrix {
private:
    T* matrix;
    unsigned int _cantidadVertices;
    unsigned int matrizSize();
    unsigned int posicionReal(unsigned int x, unsigned int y);
public:
    TMatrix();
    TMatrix(unsigned int N);
    ~TMatrix();
    T get(unsigned int x, unsigned int y);
    void set(unsigned int x, unsigned int y, T value);
    void imprimir();

    T operator()(unsigned int x, unsigned int y) { return get(x,y); }
    void operator()(unsigned int x, unsigned int y, T value) { set(x,y,value); }


};


struct DisjointSets
{
    int *parent, *rank;
    int n;

    // Constructor.
    DisjointSets(int n)
    {
        this->n = n;
        parent = new int[n+1];
        rank = new int[n+1];

        for (int i = 0; i <= n; i++)
        {
            rank[i] = 0;

            parent[i] = i;
        }
    }

    int find(int u)
    {

        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }


    void merge(int x, int y)
    {
        x = find(x), y = find(y);


        if (rank[x] > rank[y])
            parent[y] = x;
        else
            parent[x] = y;

        if (rank[x] == rank[y])
            rank[y]++;
    }
    ~DisjointSets(){
        delete[] parent;
        delete[] rank;
    }
};






#endif //TP_ALGO_III_AUXILIAR_H
