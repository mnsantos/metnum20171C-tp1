#ifndef PARAMETROS_H
#define PARAMETROS_H

#include <utility>
#include <iostream>
#include "matriz.h"
#include <fstream>
#include <stdio.h>
#include <map>

using namespace std;

struct Parametros {
  //variables
  int n; // Teams
  int k; // Encounters
  Matriz b;
  Matriz c;
  map<int, int> teamsMap;
};

#endif
