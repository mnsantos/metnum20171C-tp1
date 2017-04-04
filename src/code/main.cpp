#include "matriz.h"
#include "resolvedor.h"

using namespace std;

int main(int argc, char **argv) {


	Matriz m = Matriz(3,3);
	m[0][0] = 2;
	m[0][1] = 1;
	m[0][2] = 3;
	m[1][0] = 1;
	m[1][1] = 2;
	m[1][2] = 4;
	m[2][0] = 2;
	m[2][1] = 6;
	m[2][2] = 1;

	Matriz b = Matriz(3,1);
	b[0][0] = 1;
	b[1][0] = 1;
	b[2][0] = 1;

	cout << m << endl;

	Resolvedor resolvedor = Resolvedor(m);
	Matriz x = resolvedor.resolverUsandoGauss(b);
	
	cout << "A:\n" << m << endl;
	cout << "X:\n" << x << endl;
	cout << "b:\n" << b << endl;

}