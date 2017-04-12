#include "armador.h"

using namespace std;

vector<Matriz> Armador::armarCMM(vector<Team> teams) {

	//Creamos la matriz C y el vector b con los coeficientes correspondientes
	int n = teams.size();
	Matriz c = Matriz(n,n);
	Matriz b = Matriz(n,1);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			double coef = (i != j) ? -teams[i].challenges(teams[j].name()) : (2 + teams[i].wins() + teams[i].loses());
			c[i][j] = coef;
		}
		b[i][0] = 1.0 + (teams[i].wins() - teams[i].loses())/2.0;
	}
	vector<Matriz> res;
	res.push_back(c);
	res.push_back(b);
	return res;
}