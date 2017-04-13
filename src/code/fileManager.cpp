#include "fileManager.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>

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
		teams = vector<Team>(n);
		for (int l = 0; l < k; ++l){
			string date;
			int team_i, team_j, team_i_goals, team_j_goals;

			inputFileStream >> date >> team_i >> team_i_goals >> team_j >> team_j_goals;
			//if team_i was never before seen, it is indexed in the map, so to add wins-loses-points in the correct positions.
			it = teamsMap.find(team_i);
  			if (it == teamsMap.end())
			{
				Team team_a = Team(count, team_i);
				teamsMap[team_i] = team_a;
				count++;
			}
			//if team_j was never before seen, it is indexed in the map, so to add wins-loses-points in the correct positions.
			it = teamsMap.find(team_j);
  			if (it == teamsMap.end())
			{
				Team team_b = Team(count, team_j);
				teamsMap[team_j] = team_b;
				count++;
			}
			teamsMap[team_i].recordGame(team_j, team_i_goals, team_j_goals);
			//cout << teamsMap[team_i].getId() << endl;
			teams[teamsMap[team_i].getId()] = teamsMap[team_i];
			teamsMap[team_j].recordGame(team_i, team_j_goals, team_i_goals);
			//cout << teamsMap[team_j].getId() << endl;
			teams[teamsMap[team_j].getId()] = teamsMap[team_j];
		}

		
	}

	sort(teams.begin(), teams.end());
	params.n = n;
	params.k = k;
	params.method = method;
	params.teams = teams;

	return params;
}

void FileManager::writeExp(Matriz result, Parametros params){
	ofstream outFile;
  	outFile.open((outputFile + "-exp").c_str());
	for (int i=0; i<result.filas(); i++) {
		outFile << params.teams[i].name() << " " << params.teams[i].wins() << " " << params.teams[i].loses() << " " << setprecision(9) << result[i][0] << endl;
	}
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