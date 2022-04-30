
const std::string col_red("\033[0;31m");
const std::string col_no("\033[0m");

void printHelp(){
    cout << "\033[4;39m" <<"MODO DE USO:"<< col_no << " ./ejec heur file <tam> <iter> <percent_vecinos>" << endl;
    cout << "heur: heurística a utilizar [AGM, AMC, NN, TSU, TSA]" << endl;
    cout << "      + AGM: heurística AGM" << endl;
    cout << "      + AMC: heurística arista más corta" << endl;
    cout << "      + NN: heurística vecino más cercano" << endl;
    cout << "      + TSU: Taboo Search con soluciones en la lista tabú" << endl;
    cout << "          - Requiere:" << endl;
    cout << "          - <tam> tamaño de la lista" << endl;
    cout << "          - <iter> cantidad máx de iteraciones" << endl;
    cout << "          - <percent_vecinos> (entre 0 y 1) procentaje de la vecindad a tomar" << endl;
    cout << "      + TSA: Taboo Search con aristas en la lista tabú" << endl;
    cout << "          - Requiere:" << endl;
    cout << "          - <tam> tamaño de la lista" << endl;
    cout << "          - <iter> cantidad máx de iteraciones" << endl;
    cout << "          - <percent_vecinos> (entre 0 y 1) procentaje de la vecindad a tomar" << endl;
    cout << "file: path al archivo con el grafo, requerido por todas las heurísticas" << endl;
    cout << endl << "FORMATO DE LA SALIDA:" << endl;
    cout << "<cant_vertices> <costo_solución> <tiempo insumido>" << endl;
    cout << "[<vértices del circuito solución sin el primero repetido>]" << endl;
    cout << "Para ayuda de los generadores de instancias random usar "<< col_red << "./ejec Random" << col_no << endl;
    cout << "./ejec Falsa <instancia> devuelve el mejor camino para las instancias generadas con RandomNN" << endl;
}

void printHelpRandom(){
//TuboMasGrande(stoi(cantidadArchivos), stoi(cantidadVertices), stoi(nStart), stoi(nEnd));	
	cout << "\033[4;39m" <<"MODO DE USO:"<< col_no << " ./ejec Random <cantArchivos> <n> <nStart> <nEnd>" << endl;
    cout << "\033[4;39m" <<"MODO DE USO:"<< col_no << " ./ejec RandomEuclideo <cantArchivos> <n> <nStart> <nEnd>" << endl;
	cout << "    + cantArchivos: cantidad de archivos a generar" << endl;
	cout << "    + n: cantidad de vértices de los grafos a generar" << endl;
	cout << "    + nStart: costo mínimo a asignar a las aristas" << endl;
	cout << "    + nEnd: costo máximo a asignar a las aristas" << endl;
    cout << "\033[4;39m" <<"MODO DE USO:"<< col_no << " ./ejec RandomNN <n> " << endl;
    cout << "    + n: cantidad de vértices de los grafos a generar" << endl;
	cout << "FORMATO DE LA SALIDA:" << endl;
	cout << "Mismo de las instancias procesadas por el parser, tener en cuenta que la cantidad de aristas impresa es n*(n-1)/2. ";
	cout << "Es decir, las aristas del vértice a sí mismo no se cuentan" << endl;
}