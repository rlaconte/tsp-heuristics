#include "auxiliar.h"


//----------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------TMATRIX-------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------


template<class T>
TMatrix<T>::TMatrix(unsigned int cantidadVertices) {
    this->_cantidadVertices = cantidadVertices;
    matrix = new T[matrizSize()];

}

template<class T>
TMatrix<T>::TMatrix() {
}

/*
template<class T>
TMatrix<T>::TMatrix(unsigned int N, T value) {
    this->N=N;
    unsigned int size = matrizSize();
    matrix = new T[size];
    std::fill(matrix,matrix+size,value);
}
*/


template<class T>
TMatrix<T>::~TMatrix() {
    delete [] matrix;
}


template<class T>
unsigned int TMatrix<T>::matrizSize() {
    return (_cantidadVertices*_cantidadVertices+_cantidadVertices)/2;
}

template<class T>
unsigned int TMatrix<T>::posicionReal(unsigned int x, unsigned int y) {
    if (y > x) {
        unsigned int aux = x;
        x = y;
        y = aux;
    }
    unsigned int posicion = (x*x+x)/2+y;
    return posicion;
}


template<class T>
T TMatrix<T>::get(unsigned int x, unsigned int y) {
    return matrix[posicionReal(x,y)];
}

template<class T>
void TMatrix<T>::set(unsigned int x, unsigned int y, T value) {
    matrix[posicionReal(x,y)] = value;
}

template<class T>
void TMatrix<T>::imprimir(){
    for(int i=0;i<_cantidadVertices;i++){
        for(int j=0;j<=i;j++){
            float hola = get(i,j);
            cout << hola << " ";
        }
         cout << "" << endl;
    }
}

