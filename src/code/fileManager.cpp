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
			cout << "read 0";
			string date;
			cout << "read 1";
			int team_i, team_j, team_i_goals, team_j_goals;
			cout << "read 2";

cout << "read 3";
			inputFileStream >> date >> team_i >> team_i_goals >> team_j >> team_j_goals;
			cout << "read 4";
			//if team_i was never before seen, it is indexed in the map, so to add wins-loses-points in the correct positions.
			cout << "read 5";
			it = teamsMap.find(team_i);
			cout << "read 6";
  			if (it == teamsMap.end())
  				cout << "read 7";
			{
				cout << "read 8";
				Team team_a = Team(count, team_i);
				cout << "read 9";
				teamsMap[team_i] = team_a;
				cout << "read 10";
				count++;
				cout << "read 11";
			}
			cout << "read 12";
			//if team_j was never before seen, it is indexed in the map, so to add wins-loses-points in the correct positions.
			cout << "read 13";
			it = teamsMap.find(team_j);
			cout << "read 14";
  			if (it == teamsMap.end())
  				cout << "read 15";
			{
				cout << "read 16";
				Team team_b = Team(count, team_j);
				cout << "read 17";
				teamsMap[team_j] = team_b;
				cout << "read 18";
				count++;
				cout << "read 19";
			}
			cout << "read 20";
			teamsMap[team_i].recordGame(team_j, team_i_goals, team_j_goals);
			cout << "read 21";
			//cout << teamsMap[team_i].getId() << endl;;
			cout << "read 22";
			teams[teamsMap[team_i].getId()] = teamsMap[team_i];
			cout << "read 23";
			teamsMap[team_j].recordGame(team_i, team_j_goals, team_i_goals);
			cout << "read 24";
			//cout << teamsMap[team_j].getId() << endl;;
			cout << "read 25";
			teams[teamsMap[team_j].getId()] = teamsMap[team_j];
			cout << "read 26";
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