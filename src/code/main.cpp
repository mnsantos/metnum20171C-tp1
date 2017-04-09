#include "matriz.h"
#include "resolvedor.h"
#include "armador.h"
#include "parametros.h"
#include "fileManager.h"
#include <stdlib.h>

using namespace std;

Matriz calcularWP(vector<Team> teams) {
  Matriz rs = Matriz(teams.size(),1);
  for (int i=0; i<teams.size(); i++) {
    rs[i][0] = (double) teams[i].wins() / (teams[i].wins() + teams[i].loses());
  }
  return rs;
}

int main(int argc, char **argv) {
  FileManager fm = FileManager(argv[1], argv[2], argv[3]);
  Parametros params = fm.read();
  Matriz rankings;
  if (params.method == "0" || params.method == "1") {
    Armador armador = Armador();
    vector<Matriz> sistema = armador.armarCMM(params.teams);
    Matriz c = sistema[0];
    Matriz b = sistema[1];
    Resolvedor resolvedor = Resolvedor(c);
    if (params.method == "0") {
      rankings = resolvedor.resolverUsandoGauss(b);
    } else {
      rankings = resolvedor.resolverUsandoCholesky(b);
    } 
  } else if (params.method == "2") {
    rankings = calcularWP(params.teams);
  } else {
    cout << "Method " << params.method << " unrecognized" << endl;
    exit(EXIT_FAILURE);
  }   

  fm.write(rankings);
}

