#include "matriz.h"
#include <stdexcept>

using namespace std;

Matriz::Matriz(){
}

Matriz::Matriz(vector<double> &v) {
  cantFilas = v.size();
  cantColumnas = 1;
  for (int i=0; i<cantFilas; i++){
    data.push_back(vector<double>(1,v[i]));
  }
}

Matriz::Matriz(int filas, int columnas) {
  cantFilas = filas;
  cantColumnas = columnas;
  vector<double> fila = vector<double>(columnas,0);
  for(int i=0; i<filas; i++){
    data.push_back(fila);
  }
}

int Matriz::filas() {
  return cantFilas;
}

int Matriz::columnas() {
  return cantColumnas;
}

Matriz Matriz::trasponer() {
  Matriz C = Matriz(this -> filas(), this -> columnas());
  for (int i=0; i<this -> filas(); i++){
    for (int j=0; j<this -> columnas(); j++){
      C[i][j] = data[j][i];
    }
  }
}

vector<double>& Matriz:: operator [](int i) {
  return data[i];
}

Matriz Matriz:: operator +(Matriz& m2) {
  if (this -> filas() != m2.filas() || this -> columnas() != m2.columnas()){
    throw runtime_error("Las matrices deben ser del mismo tamaño");
  }
  Matriz C = Matriz(this -> filas(), this -> columnas());
  for (int i=0; i<this -> filas(); i++){
    for (int j=0; j<this -> columnas(); j++){
      C[i][j] = data[i][j] + m2[i][j];
    }
  }
  return C;
}

Matriz Matriz:: operator -(Matriz& m2) {
  if (this -> filas() != m2.filas() || this -> columnas() != m2.columnas()){
    throw runtime_error("Las matrices deben ser del mismo tamaño");
  }
  Matriz C = Matriz(this -> filas(), this -> columnas());
  for (int i=0; i<this -> filas(); i++){
    for (int j=0; j<this -> columnas(); j++){
      C[i][j] = data[i][j] - m2[i][j];
    }
  }
  return C;
}

Matriz Matriz:: operator *(Matriz& m2) {
  if (this -> columnas() != m2.filas()){
    throw runtime_error("No se pueden multiplicar matrices de estos tamaños");
  }

  Matriz C = Matriz(this -> filas(), m2.columnas());
  for(int i=0;i<this->filas();i++){
    for(int j=0;j<m2.columnas();j++){
      C[i][j]=0;
      for(int k=0;k<this->columnas();k++){
        C[i][j]=C[i][j]+(data[i][k] * m2[k][j]);
      }
    }
  }
  return C;
}

Matriz Matriz:: operator *(vector<double>& v) {
  if (this -> columnas() != v.size()){
    throw runtime_error("No se puede multiplicar esta matriz por el vector recibido como parametro");
  }

  Matriz C = Matriz(this -> filas(), 1);
  for(int i=0;i<this->filas();i++){
    C[i][0]=0;
    for(int k=0;k<this->columnas();k++){
      C[i][0]=C[i][0]+(data[i][k] * v[k]);
    }
  }
  return C;
}

Matriz Matriz:: operator *(double n) {
  Matriz C = Matriz(this -> filas(), this->columnas());
  for(int i=0;i<this->filas();i++){
    for(int j=0;j<this->columnas();j++){
      C[i][j] = data[i][j] * n;
    }
  }
  return C;
}

Matriz Matriz::subMatriz(int n){
  int k = this -> columnas() - n;
  if (k < 0) {
    throw runtime_error("La submatriz no se encuentra definida para el n recibido como parametro");
  }
  Matriz C = Matriz(this->filas()-n, this->columnas()-n);
  for(int i=n;i<this->filas();i++){
    for(int j=n;j<this->columnas();j++){
      C[i][j] = data[i][j];
    }
  }
  return C;
}

bool Matriz::esTriangularSuperior(){
  for (int i=0; i<this->filas(); i++){
    for (int j=0; j<i-1; j++){
      if (data[i][j] != 0){
        return false;
      }
    }
  }
  return true;
}

bool Matriz::esTriangularInferior(){
  for (int i=0; i<cantFilas; i++){
    for (int j=i+1; j<cantColumnas; j++){
      if (data[i][j] != 0){
        return false;
      }
    }
  }
  return true;
}

ostream& operator<<(ostream& os, Matriz& m) {
  for (int i=0; i<m.filas(); i++){
    for (int j=0; j<m.columnas(); j++){
      os << m[i][j] << " ";
    }
    os << "\n";
  }
  return os;
}
