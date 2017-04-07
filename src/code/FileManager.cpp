#include "FileManager.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

FileManager::FileManager(string inputFile, string outputFile, string method){
	this->inputFile = inputFile;
	this->outputFile = outputFile;
	this->method = method;
}

Parametros FileManager::read(){
	Matriz c;
	Matriz b;
	int n;
	int k;
	map<int, int> teamsMap = map<int, int>();
	map<int,int>::iterator it;
	vector<int> wins;
	vector<int> loses;
	vector<int> points;
	Matriz challenges;
	ifstream inputFileStream;
	Parametros params;

	inputFileStream.open(inputFile.c_str());
	if (inputFileStream.is_open()) {
		int count = 0;
		inputFileStream >> n >> k;
		wins = vector<int>(n,0);
		loses = vector<int>(n,0);
		points = vector<int>(n,0);
		challenges = Matriz(n,n);
		for (int l = 0; l < k; ++l){
			string date;
			int team_i, team_j, team_i_goals, team_j_goals;

			inputFileStream >> date >> team_i >> team_i_goals >> team_j >> team_j_goals;
			int i = team_i-1;
			int j = team_j-1;
			if (team_i_goals > team_j_goals)
			{
				wins[i] += 1;
				loses[j] += 1;
				challenges[i][j] += 1;
				challenges[j][i] += 1;
			} else {
				wins[j] += 1;
				loses[i] += 1;
				challenges[i][j] += 1;
				challenges[j][i] += 1;
			}
			points[i] += team_i_goals;
			points[j] += team_j_goals;
		}
		//Creamos la matriz C y el vector b con los coeficientes correspondientes
		c = Matriz(n,n);

		cout << c <<endl;
		b = Matriz(n,1);
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				double coef = (i != j) ? -challenges[i][j] : (2 + wins[i] + loses[i]);
				c[i][j] = coef;
			}
			b[i][0] = 1.0 + (wins[i] - loses[i])/2.0;
		}
	} else {
		c = Matriz(1,1);
	}
	params.n = n;
	params.k = k;
	params.teamsMap = teamsMap;
	params.c = c;
	params.b = b;

	
	cout << params.n << endl;
	cout << params.k << endl;
	cout << params.c;
	cout << params.b;

	return params;
}

void FileManager::write(Matriz result){
	ofstream outFile;
  	outFile.open(outputFile.c_str());
	for (int i=0; i<result.filas(); i++) {
		outFile << setprecision(9) << result[i][0] << endl;
	}
}