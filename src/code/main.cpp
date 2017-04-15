#include "matriz.h"
#include "resolvedor.h"
#include "armador.h"
#include "parametros.h"
#include "fileManager.h"
#include <stdlib.h>

using namespace std;
bool TESTS_FLAG = 0;
int iter = 30;
bool variar_termino_independiente = 0;

Matriz calcularWP(vector<Team> teams) {
  Matriz rs = Matriz(teams.size(),1);
  for (int i=0; i<teams.size(); i++) {
    rs[i][0] = (double) teams[i].wins() / (teams[i].wins() + teams[i].loses());
  }
  return rs;
}

void timeTests(FileManager fm, Resolvedor resolvedor, Matriz c, Matriz b) {
  Matriz resultados;
  if (variar_termino_independiente) {
    resultados = Matriz(iter, 2);
  } else {
    resultados = Matriz(1,2);
  }
  clock_t inicio, inicio1, final, final1;
  double total_gauss, total_cholesky;
  //total_gauss = 0;
  //total_cholesky = 0;
  for (int i=0; i<iter; i++){
    /*if (i == 0) {
      resolvedor = Resolvedor(c);
    }*/
    inicio = clock();
    resolvedor.resolverUsandoGauss(b);
    final = clock();
    total_gauss = ((double(final - inicio) / CLOCKS_PER_SEC) * 1000);
    inicio1 = clock();
    resolvedor.resolverUsandoCholesky(b);
    final1 = clock();
    total_cholesky = ((double(final1 - inicio1) / CLOCKS_PER_SEC) * 1000);
    if (variar_termino_independiente) {
      for (int j=0; j<b.filas(); j++) {
        b[j][0] = rand() % 10 + 1;
      }
    }
    if (variar_termino_independiente) {
      resultados[i][0] = total_gauss;
      resultados[i][1] = total_cholesky;
    }
  }
  if (!variar_termino_independiente) {
    resultados[0][0] = total_gauss / iter;
    resultados[0][1] = total_cholesky / iter;
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
      timeTests(fm, resolvedor, c, b);
    } else {
      if (params.method == "0") {
        rankings = resolvedor.resolverUsandoGauss(b);
      } else {
        rankings = resolvedor.resolverUsandoCholesky(b);
      } 
      fm.write(rankings);
      fm.writeExp(rankings, params);
    }
  } else if (params.method == "2") {
    rankings = calcularWP(params.teams);
    fm.write(rankings);
    fm.writeExp(rankings, params);
  } else {
    cout << "Method " << params.method << " unrecognized" << endl;
    exit(EXIT_FAILURE);
  }   
}

