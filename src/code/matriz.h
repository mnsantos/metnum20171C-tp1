#ifndef MATRIZ_H
#define MATRIZ_H
#include <vector>
#include <iostream>

using namespace std;

class Matriz {

private:
    vector< vector<double> > data;
    int cantFilas;
    int cantColumnas;

public:
    //construye una matriz de tamaño v * 1
    Matriz();
    Matriz(vector<double>& v);
    Matriz(int filas, int columnas);
    int filas();
    int columnas();
    vector<double>& operator[] (int i);
    Matriz operator +(Matriz& m2);
    Matriz operator -(Matriz& m2);
    Matriz operator *(Matriz& m2);
    Matriz operator *(vector<double>& v);
    Matriz operator *(double n);
    bool esTriangularSuperior();
    bool esTriangularInferior();
    Matriz trasponer();
    Matriz subMatriz(int n);

};

ostream& operator<<(ostream& os, Matriz& m);

#endif