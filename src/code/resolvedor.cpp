#include "resolvedor.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace std;

Resolvedor::Resolvedor(){
}

Resolvedor::Resolvedor(Matriz& m){
/*  vector<Matriz> lu = m.lu();
  L = lu[0];
  U = lu[1];*/
  L = Matriz(0,0);
  matriz = m;
}

Matriz Resolvedor::resolverTriangular(Matriz& m, Matriz& b){
  Matriz sol = Matriz(b.filas(), b.columnas());
  double acum;
  int pasoVertical=m.columnas()-1;

  if (m.esTriangularSuperior()){
    //caso triangular superior: backward substitution
    for (int i=pasoVertical; i>=0; i--){
      acum = 0.0;
      if (m[i][i]!=0){
        for (int j=i+1; j<m.columnas(); j++){
          acum=acum+m[i][j]*sol[j][0];
        }
        sol[i][0] = (b[i][0] - acum) / m[i][i];
      } else {
        sol[i][0] = 0.0;
      }
    }
    return sol;
  } else if (m.esTriangularInferior()){
    //caso triangular superior: forward substitution
    for (int i=0; i<m.columnas(); i++){
      acum = 0.0;
      if (m[i][i]!=0){
        for (int j=0; j<i; j++){
          acum=acum+m[i][j]*sol[j][0];
        }
        sol[i][0] = (b[i][0] - acum) / m[i][i];
      } else {
        sol[i][0] = 0.0;
      }
    }
    return sol;
  } else {
    throw std::runtime_error("La matriz no es triangular");
  }
}

/*Matriz Resolvedor::resolverUsandoLU(Matriz * b){
  Matriz y = resolverTriangular(&L,b);
  Matriz sol = resolverTriangular(&U, &y);
  return sol;
}*/

Matriz Resolvedor::resolverUsandoGauss(Matriz& b){
  Matriz m = Matriz(matriz);
  Matriz y = Matriz(b);

  for (int k=0; k<m.filas(); k++){
    for (int i=k+1; i<m.filas(); i++){
      double z = m[i][k] / m[k][k];
      m[i][k] = 0;
      for (int j=k+1; j<m.columnas(); j++) {
        m [i][j] = m[i][j] - z * m[k][j];
      }
      y[i][0] = y[i][0] - z * y[k][0];
    }
  }
  Matriz sol = resolverTriangular(m, y);
  return sol;
}

Matriz Resolvedor::resolverUsandoCholesky(Matriz& b){
  if (L.filas() == 0){
    L = matriz.cholesky();
    L_t = L.trasponer();
  }

  cout << "L: " << endl;
  cout << L << endl;

  cout << "L_t: " << endl;
  cout << L_t << endl;

  Matriz y = resolverTriangular(L,b);
  Matriz x = resolverTriangular(L_t, y);
  return x;
}