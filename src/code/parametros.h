#ifndef PARAMETROS_H
#define PARAMETROS_H

#include <utility>
#include <iostream>
#include "matriz.h"
#include <fstream>
#include <stdio.h>
#include <map>
#include "team.h"

using namespace std;

struct Parametros {
  //variables
  int n; // Teams
  int k; // Encounters
  vector<Team> teams;
  string method;
};

#endif
