#include "heuristicas.h"



vector<int> heuristicaAGM(KGrafo &grafo)
{

	//Se realiza Kruskal para obtener el AGM
	weightedGraph arbolAGM = grafo.Kruskal();

	//Se realiza DFS e imprime un camino hamiltoneano con el costo
	vector<int> vec = arbolAGM.DFS(grafo);
	return vec;
}

vector<int> heuristicaFalsa(KGrafo &grafo){
	vector<int> res;
	int n = grafo.getCantidadVertices();
	for (int i = 0; i < n-2; ++i)
	{
		res.push_back(i);
	}
	res.push_back(n-1);
	res.push_back(n-2);
	return res;
}


vector<int> heuristicaAMC(KGrafo &grafo)
{
	return grafo.KruskalHeuristica();
}

vector<int> heuristicaNN(KGrafo &grafo)
{
    unsigned int n = grafo.getCantidadVertices();
    vector<int> res;

    // Conjunto de vertices del camino recorrido definido por un arreglo de booleanos
    vector<bool> adentro(n, false);

    // Elijo aleatoriamente un vértice como inicial
    //random_device rd; // Proporciona la semilla
    //mt19937 gen(rd()); // Generador aleatorio
    /*
    uniform_int_distribution<> distribucion(0, n-1);    // Distribucion de la cantidad de objetos
    unsigned int inicial = distribucion(gen);
*/
    int inicial = 0;
    adentro[inicial] = true;
    //cout << 0 << " ";
    res.push_back(inicial);

    unsigned int actual = inicial;
    unsigned int count = 1;
    //float costo = 0;

    unsigned int min = actual;
	float costoActual = INFINITY;
	float costoMin = INFINITY;
    while (count < n)
    {
		costoMin = INFINITY;
        for (size_t i = 0; i < n; i++)
        {
			if(actual != i){
				costoActual = grafo.getCosto(actual, i);
				// Actualizamos el mas cercano chequeando que no este en el camino todavia, y que no sea el mismo
				if (/*(min==actual && !adentro[i]) || (i != actual &&*/ !adentro[i] && (costoActual < costoMin))
				{
					min = i;
					costoMin = grafo.getCosto(actual, min);
				}
			}
        }
        // Acumulamos el costo del camino
        //costo += grafo.getCosto(actual, min);

        // Agregamos el vertice al conjunto
        adentro[min] = true;
        res.push_back(min);

        actual = min;
        count++;
        //cout << min << " ";
    }
    // Imprimo el vértice inicial al final porque es un camino
    //res.push_back(inicial);
    //cout << " " << endl;
    //cout << costo << endl;
    return res;
}

float costoCiclo(KGrafo &grafo, vector<int> &ciclo)
{
	float costo = 0;
	if(ciclo.size()<2)
	    return costo;
	for (int i = 0; i < ciclo.size() - 1; ++i)
	{
	    float temp = grafo.getCosto(ciclo[i], ciclo[i + 1]);
		costo += temp;
	}
	costo += grafo.getCosto(ciclo[ciclo.size() - 1], ciclo[0]);

	return costo;
}


vector<pair<int, int>> definirVecindad(unsigned int cantVertices, float porcentajeVecindad)
{
	// Vamos a formar la vecindad, y la porción de la misma trabajando con índices. Cada par de índices se referirá a los vertices que participarán de las modificaciones en la búsqueda local de 2-opt.
	vector<pair<int, int>> indices;
	for (int i = 0; i < cantVertices - 1; ++i)
	{
		for (int j = i + 1; j < cantVertices - 1; ++j)
		{
			pair<int, int> tupla(i, j);
			indices.push_back(tupla);
		}
	}

	// Tomamos de manera aleatoria una porcion de la vecindad
	random_shuffle(indices.begin(), indices.end()); // AGREGAR EL GENERADOR DEL NUMERO RANDOM <-----------------------------
	vector<pair<int, int>> porcion = slice(indices, 0, int(indices.size() * porcentajeVecindad)-1);
	return porcion;
}

vector<int> buscarMejorVecino(KGrafo &grafo, vector<int> const ciclo, vector<pair<int, int>> vecindad, pair<int, int> indices)
{
	vector<int> mejorCicloVecino = ciclo;
	for (auto par = vecindad.begin(); par != vecindad.end(); ++par)
	{

		int i = par->first;
		int j = par->second;

		if (grafo.getCosto(ciclo[i], ciclo[i + 1]) + grafo.getCosto(ciclo[j], ciclo[j + 1]) >
			grafo.getCosto(ciclo[i], ciclo[j]) + grafo.getCosto(ciclo[i + 1], ciclo[j + 1]))
		{

			vector<int> comienzo = slice(ciclo, 0, i);
			vector<int> medio = darVuelta(slice(ciclo, i + 1, j));

			// primera concatenacion
			comienzo.insert(comienzo.end(), medio.begin(), medio.end());
			vector<int> final = slice(ciclo, j + 1, ciclo.size() - 1);

			//segunda concatenacion
			comienzo.insert(comienzo.end(), final.begin(), final.end());

			if (costoCiclo(grafo, comienzo) < costoCiclo(grafo, mejorCicloVecino))
			{
				indices = *par;
				// comienzo representa el vector final luego de las concatenaciones
				mejorCicloVecino = comienzo;
			}
		}
	}
	return mejorCicloVecino;
}

vector<int> tabuSearch_ultimasSoluciones(KGrafo &grafo, unsigned int tam_mem, int iterMax, float porcentajeVecindad)
{
	
	unsigned int n = grafo.getCantidadVertices();

	// Deberiamos tomar una solucion inicial, de cualquiera de las otras heuristicas
	vector<int> ciclo = heuristicaAMC(grafo);
	cout << "Costo solución inicial:"<< costoCiclo(grafo,ciclo) << endl;
	vector<int> mejorCiclo = ciclo;

	//La memoria va a guardar las últimas soluciones consideradas en la forma de vectores de enteros, inicia vacía
	vector<vector<int>> memoria;

	int i = 0;
	while (i < iterMax)
	{
		vector<pair<int, int>> vecindad = definirVecindad(n, porcentajeVecindad);

		vector<int> mejorVecino = buscarMejorVecino(grafo, ciclo, vecindad, make_pair(0, 0));
		
		// Manejo de lista tabu
		if (!pertenece(memoria, mejorVecino) /* || aspiracion(mejorVecino) */) // CAPAZ CONSIDERAR SI SE PIDE MUCHO UNA SOLUCION EN PARTICULAR, A PESAR DE RECHAZARLA
		{
			ciclo = mejorVecino;

			// Recordar el ciclo en la lista tabú, si no esta en la misma
			// Es necesario mantener el tamaño de la lista, si se supera se elimina el primer elemento
			// para entender el erase-remove que se usa aca abajo -> https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
			memoria.erase(remove(memoria.begin(), memoria.end(), ciclo), memoria.end());
			if (memoria.size() == tam_mem)
			{
				memoria.erase(memoria.begin());
			}
			memoria.push_back(ciclo);

			// Verificamos si tenemos que actualizar el mejor ciclo
			if (costoCiclo(grafo, ciclo) < costoCiclo(grafo, mejorCiclo))
			{
				mejorCiclo = ciclo;
			}
		}

		i++;
	}

	return mejorCiclo;
	
}

vector<int> tabuSearch_aristas(KGrafo &grafo, unsigned int tam_mem, int iterMax, float porcentajeVecindad)
{
	

	unsigned int n = grafo.getCantidadVertices();

	// Deberiamos tomar una solucion inicial, de cualquiera de las otras heuristicas
	vector<int> ciclo = heuristicaAMC(grafo);
    cout << "Costo solución inicial:" << costoCiclo(grafo,ciclo) << endl;
	vector<int> mejorCiclo = ciclo;

	//La memoria va a guardar las últimas aristas utilizadas, inicia vacía
	vector<pair<int, int>> memoria;

	int i = 0;
	while (i < iterMax)
	{
		vector<pair<int, int>> vecindad = definirVecindad(n, porcentajeVecindad);

		pair<int, int> indices;
		vector<int> mejorVecino = buscarMejorVecino(grafo, ciclo, vecindad, indices);

		pair<int, int> arista1 = make_pair(ciclo[indices.first], ciclo[indices.second]);
		pair<int, int> arista2 = make_pair(ciclo[indices.first + 1], ciclo[indices.second + 1]);

		// funcion de aspiracion -> true si el ciclo en cuestion tiene un costo menor que el optimo parcial
		if ((!pertenece(memoria, arista1) && !pertenece(memoria, arista2)) || costoCiclo(grafo, mejorVecino) < costoCiclo(grafo, mejorCiclo))
		{
			ciclo = mejorVecino;

			// Recordar las aristas en la lista tabú
			// Es necesario mantener el tamaño de la lista, si se supera se elimina el primer elemento
			// para entender el erase-remove que se usa aca abajo -> https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
			memoria.erase(remove(memoria.begin(), memoria.end(), arista1), memoria.end());
			memoria.erase(remove(memoria.begin(), memoria.end(), arista2), memoria.end());
			if (memoria.size() == tam_mem)
			{
				memoria.erase(memoria.begin());
			}
			memoria.push_back(arista1);
			if (memoria.size() == tam_mem)
			{
				memoria.erase(memoria.begin());
			}
			memoria.push_back(arista2);

			// Verificamos si tenemos que actualizar el mejor ciclo
			if (costoCiclo(grafo, ciclo) < costoCiclo(grafo, mejorCiclo))
			{
				mejorCiclo = ciclo;
			}
		}

		i++;
	}

	return mejorCiclo;
	
}
