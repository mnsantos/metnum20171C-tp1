#include "matriz.h"
#include "resolvedor.h"
#include "armador.h"
#include "parametros.h"
#include "fileManager.h"
#include <stdlib.h>

using namespace std;
bool TESTS_FLAG = 0;
int iter = 10;

Matriz calcularWP(vector<Team> teams) {
  Matriz rs = Matriz(teams.size(),1);
  for (int i=0; i<teams.size(); i++) {
    rs[i][0] = (double) teams[i].wins() / (teams[i].wins() + teams[i].loses());
  }
  return rs;
}

void timeTests(FileManager fm, Resolvedor resolvedor, Matriz c, Matriz b) {
  Matriz resultados = Matriz(iter,2);
  clock_t inicio, final;
  double total_gauss, total_cholesky;
  for (int i=0; i<iter; i++){
    inicio = clock();
    resolvedor.resolverUsandoGauss(b);
    final = clock();
    total_gauss = double(final - inicio) / CLOCKS_PER_SEC;
    inicio = clock();
    resolvedor.resolverUsandoCholesky(b);
    final = clock();
    total_cholesky = double(final - inicio) / CLOCKS_PER_SEC;
    for (int j=0; j<b.filas(); j++) {
      b[j][0] = rand() % 10 + 1;
    }
    resultados[i][0] = total_gauss;
    resultados[i][1] = total_cholesky;
  }
  fm.writeTimeTestResults(resultados);
}

int main(int argc, char **argv) {
  FileManager fm = FileManager(argv[1], argv[2], argv[3]);
  Parametros params = fm.read();
  Matriz rankings;
  if (params.method == "0" || params.method == "1" || TESTS_FLAG) {
    Armador armador = Armador();
    vector<Matriz> sistema = armador.armarCMM(params.teams);
    Matriz c = sistema[0];
    Matriz b = sistema[1];
    Resolvedor resolvedor = Resolvedor(c);
    if (TESTS_FLAG) {
      timeTests(fm, resolvedor, c,b);
    } else {
      if (params.method == "0") {
        rankings = resolvedor.resolverUsandoGauss(b);
      } else {
        rankings = resolvedor.resolverUsandoCholesky(b);
      } 
      fm.write(rankings);
    }
  } else if (params.method == "2") {
    rankings = calcularWP(params.teams);
    fm.write(rankings);
  } else {
    cout << "Method " << params.method << " unrecognized" << endl;
    exit(EXIT_FAILURE);
  }   
}

