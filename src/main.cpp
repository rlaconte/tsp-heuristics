#include "Grafos.h"
#include "help.h"
#include "heuristicas.h"
#include "randomGenerator.h"
#include "parser.h"

#include <iostream>
#include <map>
#include <time.h>    // For time()
#include <cstdlib>  // For srand
#include <chrono>

using namespace chrono;
using namespace std;

int modo2int(string modo){
    map<string,int> mymap;

    mymap["AGM"]=1;
    mymap["AMC"]=2;
    mymap["NN"]=3;
    mymap["TSU"]=4;
    mymap["TSA"]=5;
    mymap["Random"]=6;
    mymap["RandomNN"]=7;
    mymap["RandomEuclideo"]=8;
    mymap["Falsa"]=9;

    map<string,int>::iterator it;
    it = mymap.find(modo);
    if (it != mymap.end())
        // Parámetro válido
        return it->second;

    // Parámetro inválido 
    return -1;    
}

template <typename T> 
ostream& operator<<(ostream& os, const vector<T>& v) 
{ 
    os << "["; 
    for (int i = 0; i < v.size(); ++i) { 
        os << v[i]; 
        if (i != v.size() - 1) 
            os << ", "; 
    } 
    os << "]\n"; 
    return os; 
} 

int main(int argc, char** argv) {


    high_resolution_clock::time_point t0, t1;
    unsigned long long int start, end, cant_ciclos;

    if(argc<2){
    	printHelp();
        return -1;
    }
    string modo(argv[1]);
    if(modo=="Random" and argc<3){
    	printHelpRandom();
        return -1;
    }

    if(argc < 3){
        printHelp();
        return -1;
    }
    string instancia(argv[2]);
    
    // Randomizo en nanosegundos
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);



    // Parseo la instancia
    // parser PIDE MEMORIA CON NEW que el programador DEBE liberar
    KGrafo* g = parser(instancia);
    //g->imprimir();
        int caso = modo2int(modo);
        switch(caso){
            case 1:
            {

                t0 = high_resolution_clock::now();
                vector<int> res = heuristicaAGM(*g);
                t1 = high_resolution_clock::now();
                duration<double> tiempo = t1-t0;

                
                cout << g->getCantidadVertices() << " " << costoCiclo(*g,res) << " " << tiempo.count() << endl;
                cout << res;
                break;
            }
            case 2:
            {

                t0 = high_resolution_clock::now();
                vector<int> res = heuristicaAMC(*g);
                t1 = high_resolution_clock::now();
                duration<double> tiempo = t1-t0;

                cout << g->getCantidadVertices() << " " << costoCiclo(*g,res) << " " << tiempo.count() << endl;
                cout << res;
                cout << res.size();
                break;
            }
            case 3:
            {

                t0 = high_resolution_clock::now();
                vector<int> res = heuristicaNN(*g);
                t1 = high_resolution_clock::now();
                duration<double> tiempo = t1-t0;

                cout << g->getCantidadVertices() << " " << costoCiclo(*g,res) << " " << tiempo.count() << endl;
                cout << res;
                break;
            }
            case 4:
            {

                if(argc < 6){
                    // No tiene alguno de los parámetros "opcionales" (aun no son opcionales xD)
                    printHelp();
                    return -1;
                }
                string tam(argv[3]);
                string iter(argv[4]);
                string vecin(argv[5]);
                float vecindad = stof(vecin);

                if(vecindad<0 || vecindad>1){
                    cout<< col_red << "Vecinos debe ser un porcentaje entre 0 y 1" << col_no << endl << endl;
                    printHelp();
                }

                t0 = high_resolution_clock::now();
                vector<int> res = tabuSearch_ultimasSoluciones(*g, stoi(tam), stoi(iter), stof(vecin));
                t1 = high_resolution_clock::now();
                duration<double> tiempo = t1-t0;

                cout << g->getCantidadVertices() << " " << costoCiclo(*g,res) << " " << tiempo.count() << endl;
                cout << res;
                break;
            }
            case 5:
            {

                if(argc < 6){
                    // No tiene alguno de los parámetros "opcionales" (aun no son opcionales xD)
                    printHelp();
                    return -1;
                }
                string tam(argv[3]);
                string iter(argv[4]);
                string vecin(argv[5]);
                float vecindad = stof(vecin);
                if(vecindad<0 || vecindad>1){
                    cout<< col_red << "Vecinos debe ser un porcentaje entre 0 y 1" << col_no << endl << endl;
                    printHelp();
                }

                t0 = high_resolution_clock::now();
                vector<int> res = tabuSearch_aristas(*g, stoi(tam), stoi(iter), stof(vecin));
                t1 = high_resolution_clock::now();
                duration<double> tiempo = t1-t0;

                cout << g->getCantidadVertices() << " " << costoCiclo(*g,res)  << " " << tiempo.count() << endl;
                cout << res;
                break;
            }
            case 6:
            {
            	if(argc < 6){
                    // No tiene alguno de los parámetros "opcionales" (aun no son opcionales xD)
                    printHelpRandom();
                    return -1;
                }
                string cantidadArchivos(argv[2]);
                string cantidadVertices(argv[3]);
                string nStart(argv[4]);
                string nEnd(argv[5]);
                system("mkdir ../data/dataGenerada");
                TuboMasGrande(stoi(cantidadArchivos), stoi(cantidadVertices), stoi(nStart), stoi(nEnd));
                break;
            }
           	case 7:
            {

                string cantidadArchivos(argv[2]);
                string cantidadVertices(argv[3]);
                system("mkdir ../data/dataGenerada");
                GeneradorNN(stoi(cantidadArchivos), stoi(cantidadVertices));
                break;
            }
            case 8:
            {
                string cantidadArchivos(argv[2]);
                string cantidadVertices(argv[3]);
                string nStart(argv[4]);
                string nEnd(argv[5]);
                system("mkdir ../data/dataGenerada/euc");
                randomEuclideo(stoi(cantidadArchivos), stoi(cantidadVertices), stoi(nStart), stoi(nEnd));
                break;
            }
            case 9:
            {
                vector<int> res = heuristicaFalsa(*g);
                cout << g->getCantidadVertices() << " " << costoCiclo(*g,res) << " " << 999 << endl;
                cout << res;
                break;
            }
            case -1:
            {
                printHelp();
                cout << "Debug"<< endl;
                cout << g->getAristas();
                break;
            }
            default:
            {
                //no debería caer aca, pero x las dudas
                //Futuro Easter Egg? (?)
                cout << "default" << endl;
                printHelp();
                break;
            }
        }
        //heuristicaAGM(g);
        //vector<Arista<float,float>> vecg = g->getAristas();

        
    delete(g);
}