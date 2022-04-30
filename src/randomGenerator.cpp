#include "randomGenerator.h"
using namespace std;


void TuboMasGrande(uint32_t cantidadArchivos, uint32_t cantidadVertices, uint32_t nStart, uint32_t nEnd) {
    std::random_device rd; // Proporciona la semilla
    std::mt19937 gen(rd()); // Generador aleatorio

    // Distribuciones uniformes
    std::uniform_int_distribution<> disRangoCosto(nStart, nEnd);    // Distribucion del rango de
   

    string primeraParte = "../data/dataGenerada/generada";
    string ultimaParte  = ".tsp";
    ofstream testFile;
    string archivo;
    string snake = "_";
    for (int i=0;i<cantidadArchivos;i++) {
        if (i<10){
            string agregado = "0";
            archivo = primeraParte + snake + agregado + to_string(i) + snake + to_string(cantidadVertices) + ultimaParte;
        } else {
            archivo = primeraParte + snake + to_string(i) + snake + to_string(cantidadVertices) + ultimaParte;
        }

        testFile.open(archivo, std::ofstream::out | std::ofstream::trunc); //cambiar

        //Cantidad de aristas
        int cant_aristas = cantidadVertices*(cantidadVertices-1)/2;
        
        testFile << cantidadVertices << ' ' << cant_aristas << "\n"; // Lo guardo en el archivo
        //std::cout << cant << ' ' << disTubo(gen) << "\n"; // Imprimo en pantalla

     for (int m = 0; m < cantidadVertices; m++){
        for (int n = m; n < cantidadVertices; n++) {
           int disObjeto1;
           //Si la arista se conecta consigo mismo, entonces tiene costo 0
            if (n == m){
                disObjeto1 = 0;
            } else {
                //En otro caso, coloca un costo random.
                disObjeto1 = disRangoCosto(gen);
            }             
            testFile << m << ' ' << n << ' ' << disObjeto1 << "\n";  // Guardo en el archivo
           
        }  
   	 }
      testFile.close();
   }
}


void randomEuclideo(uint32_t cantidadArchivos, uint32_t cantidadVertices, uint32_t nStart, uint32_t nEnd) {
    std::random_device rd; // Proporciona la semilla
    std::mt19937 gen(rd()); // Generador aleatorio

    // Distribuciones uniformes
    std::uniform_int_distribution<> disRangoCosto(nStart, nEnd);    // Distribucion del rango de
   

    string primeraParte = "../download_data/temp/generada";
    string ultimaParte  = ".tsp";
    ofstream testFile;
    string archivo;
    string snake = "_";
    string euc   = "_EUC";
    string nombre;
    for (int i=0; i<cantidadArchivos; i++) {
        if (i<10){
            string agregado = "0";
            archivo = primeraParte + euc + to_string(cantidadVertices) +  snake + agregado + to_string(i)   + ultimaParte;
            nombre  = euc + to_string(cantidadVertices) +  snake + agregado + to_string(i)  ;
        } else {
            archivo = primeraParte + euc + to_string(cantidadVertices) +  snake + to_string(i)   + ultimaParte;
            nombre  = euc + to_string(cantidadVertices) +  snake + to_string(i);
        }

        testFile.open(archivo, std::ofstream::out | std::ofstream::trunc); //cambiar


        testFile << "NAME : " << nombre << "\n";  
        testFile << "DIMENSION: " << ' ' << cantidadVertices << "\n";
        testFile << "EDGE_WEIGHT_TYPE : EUC_2D" << "\n";
        testFile << "TYPE : TSP" << "\n";
        testFile << "NODE_COORD_SECTION"  << "\n";

     for (int m = 0; m < cantidadVertices; m++){
        int disObjeto1 = disRangoCosto(gen);
        int disObjeto2 = disRangoCosto(gen);            
        testFile << m << ' ' << disObjeto1 << ' ' << disObjeto2 << "\n";  // Guardo en el archivo
           
        
     }
      testFile.close();
   }
   system("../2_parsear_instancias_euclidianas_propias.sh");
}

void GeneradorNN(uint32_t cantidadArchivos, uint32_t cantidadVertices) {
  

    string primeraParte = "../data/dataGenerada/NNMejorCaso";
    string ultimaParte  = ".tsp";
    ofstream testFile;
    string archivo;
    string snake = "_";

      for (int i=0; i<cantidadArchivos; i++) {
        if (i<10){
            string agregado = "0";
            archivo = primeraParte + agregado + to_string(i) + snake + to_string(cantidadVertices) + ultimaParte;
        } else {
            archivo = primeraParte + to_string(i) + snake + to_string(cantidadVertices) + ultimaParte;
        }


    testFile.open(archivo, std::ofstream::out | std::ofstream::trunc); //cambiar

    //Cantidad de aristas
    int cant_aristas = cantidadVertices*(cantidadVertices-1)/2;
    
    testFile << cantidadVertices << ' ' << cant_aristas << "\n"; // Lo guardo en el archivo
    //std::cout << cant << ' ' << disTubo(gen) << "\n"; // Imprimo en pantalla

    // Quiero que las aristas queden ordenadas de menor a mayor tal que queden: 1->2, 2->3, 3->4, 4->5 ... n-1 -> n 

    for (int m = 0; m < cantidadVertices; m++){
        for (int n = m; n < cantidadVertices; n++) {
           int disObjeto1;
           //Si la arista se conecta consigo mismo, entonces tiene costo 0
            if (n == m){
                disObjeto1 = 0;
            } else {
                // si estoy en el caso 1->2 por ejemplo quiero que el costo sea chico pero que vaya creciendo para que al 
                // ordenar las aristas 1->2 quede antes que 2->3 
                if (m+1 == n) {
                    disObjeto1 = m; 
                } else {
                    // me aseguro que si no queremos que la arista quede primera tenga mayor costo que la arista n->n+1
                    if(m==0 and n==cantidadVertices-1){
                        disObjeto1 = cantidadVertices*cantidadVertices;
                    } else {
                        disObjeto1 = cantidadVertices+1 ;
                    }
                }
            }             
            testFile << m << ' ' << n << ' ' << disObjeto1 << "\n";  // Guardo en el archivo
           
        }  
    }
   

/*
    string primeraParte2 = "../data/dataGenerada/NNPeorCaso";
    ofstream testFile2;
    string archivo2;
    
    archivo = primeraParte2 + snake + to_string(cantidadVertices) + ultimaParte;

    testFile2.open(archivo, std::ofstream::out | std::ofstream::trunc); //cambiar

    //Cantidad de aristas
    int cant_aristas = cantidadVertices*(cantidadVertices-1)/2;
    
    testFile2 << cantidadVertices << ' ' << cant_aristas << "\n"; // Lo guardo en el archivo
    //std::cout << cant << ' ' << disTubo(gen) << "\n"; // Imprimo en pantalla

    for (int m = 0; m < cantidadVertices; m++){
        for (int n = m; n < cantidadVertices; n++) {
           int disObjeto1;
           //Si la arista se conecta consigo mismo, entonces tiene costo 0
            if (n == m){
                disObjeto1 = 0;
            } else {
                //En otro caso, coloca un costo random.
            }             
            testFile2 << m << ' ' << n << ' ' << disObjeto1 << "\n";  // Guardo en el archivo
           
        }  
    }
    testFile2.close();*/
   
 testFile.close();
}
}