#include "team.h"

using namespace std;

Team::Team(int id, int wins, int loses, vector<double> challenges){
	this -> id = id;
	this -> ws = wins;
	this -> ls = loses;
	this -> chs = challenges;
}

int Team::wins(){
	return ws;
}


int Team::loses(){
	return ls;
}

int Team::challenges(int team_id){
	return chs[team_id];
}