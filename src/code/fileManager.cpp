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
	ifstream inputFileStream;
	Parametros params;
	map<int, Team> teamsMap;
	map<int, Team>::iterator it;
	vector<Team> teams;

	inputFileStream.open(inputFile.c_str());
	if (inputFileStream.is_open()) {
		int count = 0;
		inputFileStream >> n >> k;
		for (int l = 0; l < k; ++l){
			string date;
			int team_i, team_j, team_i_goals, team_j_goals;

			inputFileStream >> date >> team_i >> team_i_goals >> team_j >> team_j_goals;
			//if team_i was never before seen, it is indexed in the map, so to add wins-loses-points in the correct positions.
			it = teamsMap.find(team_i);
  			if (it == teamsMap.end())
			{
				Team team_a = Team(count, team_i);
				teams.push_back(team_a);
				teamsMap[team_i] = team_a;
				count++;
			}
			//if team_j was never before seen, it is indexed in the map, so to add wins-loses-points in the correct positions.
			it = teamsMap.find(team_j);
  			if (it == teamsMap.end())
			{
				Team team_b = Team(count, team_j);
				teams.push_back(team_b);
				teamsMap[team_j] = team_b;
				count++;
			}
			teamsMap[team_i].recordGame(team_i, team_i_goals, team_j_goals);
			teamsMap[team_j].recordGame(team_j, team_j_goals, team_i_goals);
		}
		
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