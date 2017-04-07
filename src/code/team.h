#ifndef __TEAM_H__
#define __TEAM_H__

#include <vector>

using namespace std;

class Team {

private:
	int id;
	int ws;
	int ls;
	vector<double> chs;

public:
	Team(int id, int wins, int loses, vector<double> challenges);
	int wins();
	int loses();
	int challenges(int team_id);
};

#endif
