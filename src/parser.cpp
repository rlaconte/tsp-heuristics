#include "parser.h"
using namespace std;

//Se encarga de crear un objeto, que en su primer coordenada tiene el peso y en la segunda la resistencia
Arista crearArista(string str)
{
    // Used to split string around spaces.
    istringstream ss(str);
    int src;
    int dst;
    float costo;
    ss >> src;
    ss >> dst;
    ss >> costo;
    Arista arista(src, dst, costo);
    return arista;
}

// Parser PIDE MEMORIA CON NEW que el programador DEBE liberar
KGrafo* parser(string file) {
    KGrafo* res = nullptr;
    uint32_t cant_vertices;

    ifstream archivo(file);
    //Precondicion: el archivo tiene el formato valido (cantidad de productos y resistencia y al menos un producto)
    if (archivo.is_open()) {
        //La primera linea toma la cantidad de vertices primero y luego la cantidad de aristas
        archivo >> cant_vertices;
        uint32_t aristas;
        archivo >> aristas;       //innecesario
        //res.agregarVertices(cant_vertices);
        res = new KGrafo(cant_vertices);

        //Agrega aristas
        string obj;
        while (getline(archivo, obj)) {
            if(obj != "") {
                Arista ar = crearArista(obj);
                res->agregarArista(ar);
            }
        }
        archivo.close();
    }

    //KGrafo res2 = *res;
    return res;
}

