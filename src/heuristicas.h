#ifndef TP_ALGO_III_HEURISTICAS_H
#define TP_ALGO_III_HEURISTICAS_H

#include "Grafos.h"
#include <random>
#include "templates.h"

vector<int> heuristicaAGM(KGrafo &grafo);

vector<int> heuristicaFalsa(KGrafo &grafo);

vector<int> heuristicaAMC(KGrafo &grafo);

vector<int> heuristicaNN(KGrafo &grafo);

vector<int> tabuSearch_ultimasSoluciones(KGrafo &grafo, unsigned int tam_mem, int iterMax, float porcentajeVecindad);

vector<int> tabuSearch_aristas(KGrafo &grafo, unsigned int tam_mem, int iterMax, float porcentajeVecindad);

float costoCiclo(KGrafo &grafo, vector<int> &ciclo);

vector<pair<int, int>> definirVecindad(unsigned int cantVertices, float porcentajeVecindad);

vector<int> buscarMejorVecino(KGrafo &grafo, vector<int> ciclo, vector<pair<int, int>> vecindad, pair<int, int> indices);

#endif //TP_ALGO_III_HEURISTICAS_H
