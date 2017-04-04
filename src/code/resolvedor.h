#ifndef __RESOLVEDOR_H__
#define __RESOLVEDOR_H__

#include <utility>
#include <iostream>
#include "matriz.h"

using namespace std;

class Resolvedor {

  public:
  	Resolvedor();
    Resolvedor(Matriz& m);
    Matriz resolverUsandoGauss(Matriz& b);
    Matriz resolverUsandoCholesky(Matriz& b);
    //Matriz resolverUsandoLU(Matriz& b);
  private:
    Matriz resolverTriangular(Matriz& m, Matriz& b);
    Matriz L;
    Matriz L_t;
    //Matriz U;
    Matriz matriz;
};

#endif
