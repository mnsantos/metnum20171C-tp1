#include "fileManager.h"
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
	int n;
	int k;
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
		
	}

	vector<Team> teams;
	for (int i=0; i<n; i++) {
		teams.push_back(Team(i,wins[i],loses[i],challenges[i]));
	}
	params.n = n;
	params.k = k;
	params.method = method;
	params.teams = teams;

	return params;
}

void FileManager::write(Matriz result){
	ofstream outFile;
  	outFile.open(outputFile.c_str());
	for (int i=0; i<result.filas(); i++) {
		outFile << setprecision(9) << result[i][0] << endl;
	}
}

void FileManager::writeTimeTestResults(Matriz result){
	ofstream outFile;
  	outFile.open((outputFile + "-time_tests").c_str());
	for (int i=0; i<result.filas(); i++) {
		for (int j=0; j<result.columnas(); j++) {
			outFile << setprecision(9) << result[i][j] << " ";
		}
		outFile << endl;
	}
}