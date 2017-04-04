#include "matriz.h"
#include "resolvedor.h"

using namespace std;

int main(int argc, char **argv) {


	Matriz m = Matriz(3,3);
	m[0][0] = 1;
	m[0][1] = -1;
	m[0][2] = 2;

	m[1][0] = -1;
	m[1][1] = 5;
	m[1][2] = -4;

	m[2][0] = 2;
	m[2][1] = -4;
	m[2][2] = 6;

	Matriz b = Matriz(3,1);
	b[0][0] = 1;
	b[1][0] = 1;
	b[2][0] = 1;

	Resolvedor resolvedor = Resolvedor(m);
	Matriz x_gauss = resolvedor.resolverUsandoGauss(b);
	Matriz x_cholesky = resolvedor.resolverUsandoCholesky(b);

	Matriz b_res = m * x_gauss;

	cout << "A:\n" << m << endl;
	cout << "X (gauss):\n" << x_gauss << endl;
	cout << "X (cholesky):\n" << x_cholesky << endl;
	cout << "b:\n" << b << endl;
	cout << "A*x_gauss:\n" << b_res << endl;

}