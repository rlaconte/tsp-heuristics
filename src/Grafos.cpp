#include "Grafos.h"

using namespace std;

//----------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------QUICKSORT-------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------

void swap(Arista *a, Arista *b)
{
    Arista temp = *a;
    *a = *b;
    *b = temp;
}

int Partition(vector<Arista> &a, int low, int high)
{
    int pivot, index, i;
    index = low;
    pivot = high;

    for (i = low; i < high; i++)
    {
        if (a[i].costo < a[pivot].costo)
        {
            swap(&a[i], &a[index]);
            index++;
        }
    }

    swap(&a[pivot], &a[index]);

    return index;
}

// Random selection of pivot.
int RandomPivotPartition(vector<Arista> &a, int low, int high)
{
    int pivot, n;
    n = rand();

    pivot = low + n % (high - low + 1);

    swap(&a[high], &a[pivot]);

    return Partition(a, low, high);
}

int QuickSort(vector<Arista> &a, int low, int high)
{
    int pivotIndex;
    if (low < high)
    {

        pivotIndex = RandomPivotPartition(a, low, high);

        QuickSort(a, low, pivotIndex - 1);
        QuickSort(a, pivotIndex + 1, high);
    }
    return 0;
}



//Constructor del KGrafo
weightedGraph::weightedGraph(unsigned int cantidadVertices)
{
    _totalVertices = cantidadVertices;

    //Reserva n listas donde n es la cantidad de Vertices pasada por parametro
    adjLists = new list<Arista>[cantidadVertices];

    //Inicializo en 0 la cantidad de aristas ya que solo tenemos la cantidad de vertices
    _totalAristas = 0;
}

void weightedGraph::agregarArista(Arista &arista)
{

    //Reservo memoria para el nodo

    float costo = arista.costo;
    //Nodo *nodo = new Nodo(arista.dest, costo);

    //agrego a la lista del vertice, el nodo creado. Esto simula agregar un vertice desde el vertice source al vertice destino con un costo asociado
    (adjLists[arista.src]).push_back(arista);

    //Guardo en el vector de aristas la recientemente creada

    _aristas.push_back(arista);
    _totalAristas++;
}

vector<int> weightedGraph::DFS(KGrafo &grafo)
{
    float costo = 0;
    //Creo un vector de booleanos para indicar si ya recorri o no el nodo actual
    vector<bool> visited(_totalVertices, false);

    stack<int> stack;
    //Creo una lista para ir guardando el camino decidido por el algoritmo
    vector<int> caminoHamiltoneano;

    //Inicializo en 0, esto puede cambiar
    int Node = 0;

    //Inicializo el stack
    stack.push(Node);

    //La idea es que por cada nodo recorrido, se guarden sus vecinos en el stack. Luego de cada iteracion, analiza el contenido de la pila, se fija si se visito el nodo
    while (!stack.empty())
    {

        Node = stack.top();
        stack.pop();

        //Sino fue visitado, entonces lo agrego al camino y pongo true en el vector de booleanos, indicando que este nodo ya lo visite
        if (!visited[Node])
        {
            //cout << Node << " ";
            visited[Node] = true;
            caminoHamiltoneano.push_back(Node);
        }

        //Guardo los vecino en la pila en caso que no fueron visitados para evitar duplicaciones.
        for (auto i = adjLists[Node].begin(); i != adjLists[Node].end(); ++i)
            if (!visited[(*i).dest])
            {
                stack.push((*i).dest);
            }
    }
    //Completo el camino con el primer nodo asi queda hamiltoneano
    //caminoHamiltoneano.push_back(0);

    //Se puede sacar tranquilamente
    //imprimirCaminoYCosto(caminoHamiltoneano, grafo);

    return caminoHamiltoneano;


}

int weightedGraph::getCantVecinos(int src) {
    return (adjLists[src].size());
}


//---------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------KGrafo-------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------

Arista &Arista::operator=(Arista &aCopiar)
{
    this->src = aCopiar.src;
    this->dest = aCopiar.dest;
    this->costo = aCopiar.costo;
}

ostream& operator<<(ostream& os, const Arista &a){
    os << '(' << a.src << ',' << a.dest << ',' << a.costo << ')';
    return os;
}

//Constructor de la arista
Arista::Arista(int src, int dest, float &costo) : src(src), dest(dest), costo(costo) {}

//Devuelve el costo del vertice src y dest
float KGrafo::getCosto(int src, int dest)
{
    return (_matriz.get(src, dest));
}

//Constructor del KGrafo
KGrafo::KGrafo(unsigned int cantidadVertices)
        : _aristas(), _matriz(cantidadVertices)
{
    _totalVertices = cantidadVertices;

    //Reserva n listas donde n es la cantidad de Vertices pasada por parametro

    //Inicializo en 0 la cantidad de aristas ya que solo tenemos la cantidad de vertices
    _totalAristas = 0;
}


vector<Arista> KGrafo::getAristas()
{
    return _aristas;
}

void KGrafo::agregarArista(int src, int dest, float costo)
{

    //Agrego a la matriz, en la posicion [src][dest] el costo asociado
    _matriz.set(src, dest, costo);

    //Guardo en el vector de aristas la recientemente creada
    Arista arista(src, dest, costo);
    _aristas.push_back(arista);
    _totalAristas++;
}

unsigned int KGrafo::getCantidadVertices()
{
    return _totalVertices;
}

void KGrafo::imprimir(){
    _matriz.imprimir();
}

void KGrafo::agregarArista(Arista &arista)
{

    //Agrego a la matriz, en la posicion [src][dest] el costo asociado
    _matriz.set(arista.src, arista.dest, arista.costo);

    //Guardo en el vector de aristas la recientemente creada
    _aristas.push_back(arista);
    _totalAristas++;
}

weightedGraph KGrafo::Kruskal()
{

    //Inicializacion
    int begin = 0;
    int end = _totalAristas - 1;
    vector<Arista> aristas = this->_aristas;
    weightedGraph grafoAGM(_totalVertices);

    //Ordeno las aristas de entrada segun su costo
    //Quicksor tomar 3 parametros, el vector, el indice inicial y al final
    QuickSort(aristas, begin, end);

    //Creo n conjuntos disjuntos donde n es la cantidad de vertices totales del grafo
    DisjointSets ds(_totalVertices);

    for (int i = 0; i < end; i++)
    {

        int u = aristas[i].src;
        int v = aristas[i].dest;

        //Busco si el src y el destination estan en conjuntos disjuntos.

        int setU = ds.find(u);
        int setV = ds.find(v);

        // Si lo estan, entonces significa que el vertice destination no lo recorri, con lo cual lo agrego a los ya recorridos.
        if (setU != setV)
        {
            //cout << u << " - " << v << " - " << endl;

            float costo = _matriz.get(u, v);
            Arista arista(u, v, costo);
            Arista arista2(v, u, costo);
            grafoAGM.agregarArista(arista);
            grafoAGM.agregarArista(arista2);
            ds.merge(setU, setV);
        }
    }
    return grafoAGM;
}

weightedGraph::~weightedGraph(){
    delete[] adjLists;

}

void KGrafo::completarConCeros(vector<int> &v){

    for (int i=0; i<v.size()-1; i++){
        v[i] = 0;
    }

}

vector<int> KGrafo::KruskalHeuristica() {

    //Inicializacion
    int begin = 0;
    int end = _totalAristas - 1;

    //Se toman las aristas del grafo para poder a ordenarlas de menor a mayor con respecto al costo
    vector<Arista> aristas = this->_aristas;
    QuickSort(aristas, begin, end);


    //Creo un arbol pesado para ir guardando el camino hamiltoneano
    weightedGraph grafoAGM(_totalVertices);

    //Creo n conjuntos disjuntos donde n es la cantidad de vertices totales del grafo
    DisjointSets ds(_totalVertices);

    //El vector tiene la finalidad de contar el grado de cada vertices para poder ser accedido de forma rapida. 
    vector<int> gradoVertices(_totalVertices);

    //Se procede a completar con 0 el vertice.
    completarConCeros(gradoVertices);


    for (int i = 0; i < end; i++) {

        int u = aristas[i].src;
        int v = aristas[i].dest;

        //Busco si el src y el destination estan en conjuntos disjuntos.

        int setU = ds.find(u);
        int setV = ds.find(v);

        // Si lo estan, entonces significa que el vertice destination no lo recorri, con lo cual lo agrego a los ya recorridos.
        if (setU != setV) {

            if (gradoVertices[u] < 2 && gradoVertices[v] < 2) {

                
                float costo = _matriz.get(u, v);

                Arista arista(u, v, costo);
                Arista arista2(v, u, costo);
                grafoAGM.agregarArista(arista);
                grafoAGM.agregarArista(arista2);

                //Aumento el grado de los vertices en el vector
                gradoVertices[u] = gradoVertices[u] + 1;
                gradoVertices[v] = gradoVertices[v] + 1;
                ds.merge(setU, setV);

            }
        }
    }

    int verticeSinConectarInicial = 0;
    int verticeSinConectarFinal   = 0;
    int count = 0;
    int j = 0;
    //Conecto los vertices con grado 1
    while (count != 2 || j < _totalVertices) {
         if (gradoVertices[j] == 1) {
           if (count == 0){
               verticeSinConectarInicial = j;
               count++;
           } else {
               verticeSinConectarFinal = j;
               count++;
           }
         
        }
         j++;
    }
  

    float costo = _matriz.get(verticeSinConectarInicial, verticeSinConectarFinal);
    
     Arista arista(verticeSinConectarInicial, verticeSinConectarFinal, costo);
    Arista arista2(verticeSinConectarFinal, verticeSinConectarInicial, costo);

    grafoAGM.agregarArista(arista);
    grafoAGM.agregarArista(arista2);

    vector<int> nuevocaminoHamiltoneano = grafoAGM.getCaminoHamiltoneano();

    return nuevocaminoHamiltoneano;
}

//PRECONDICION: Tiene que ser un arbol donde cada vertice tenga como maximo 2 grados.
vector<int> weightedGraph::getCaminoHamiltoneano() {

    vector<int> camino;
    camino.push_back(0);

    auto it = adjLists[0].begin();
    int verticeAVisitar = (*it).dest;
    camino.push_back(verticeAVisitar);

    while (verticeAVisitar != 0){

        it = adjLists[verticeAVisitar].begin();
        verticeAVisitar = (*it).dest;

        //Se tienen dos aristas, una con el vertice de donde se vino y el segundo a nuevo vertice, comprobamos que sea el nuevo.
        if (verticeAVisitar != camino[camino.size()-2]) {
            camino.push_back((*it).dest);

        } else {
            it++;
            camino.push_back((*it).dest);
            verticeAVisitar = (*it).dest;
        }

    }

    //Saco el ultimo vertice por que se repite
    camino.pop_back();
    return camino;
}


