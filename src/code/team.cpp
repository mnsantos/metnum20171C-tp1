#include "team.h"

using namespace std;

Team::Team(int id, int name){
	this -> id = id;
	this -> nm = name;
	this -> ws = 0;
	this -> ls = 0;
	this -> chs = map<int, int>();
}

Team::Team(){
	this -> id = 0;
	this -> nm = 0;
	this -> ws = 0;
	this -> ls = 0;
	this -> chs = map<int, int>();
}

void Team::recordGame(int oponente, int aFavor, int enContra){
//if team_i was never before seen, it is indexed in the map, so to add wins-loses-points in the correct positions.
	map<int,int>::iterator it;	
	it = chs.find(oponente);
	if (it == chs.end())
	{
		chs[oponente] = 1;
	} else {
		//si ya esta definido
		chs[oponente] = chs[oponente]+1;
	}
	if (aFavor > enContra)
	{
		ws++;
	} else {
		ls++;
	}
	ps += aFavor;
}

int Team::wins(){
	return ws;
}

int Team::name(){
	return nm;
}

int Team::points(){
	return ps;
}

int Team::loses(){
	return ls;
}

int Team::challenges(int team_id){
	return chs[team_id];
}