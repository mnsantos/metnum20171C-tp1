#ifndef __TEAM_H__
#define __TEAM_H__

#include <vector>
#include <map>

using namespace std;

class Team {

private:
	int id;
	int nm;
	int ws;
	int ls;
	int ps;
	map<int, int> chs;

public:
	Team();
	Team(int id, int name);
	void recordGame(int oponente, int aFavor, int enContra);
	int wins();
	int name();
	int loses();
	int points();
	int challenges(int team_id);
};

#endif
