#ifndef __ARMADOR_H__
#define __ARMADOR_H__

#include <vector>
#include "team.h"
#include "matriz.h"

using namespace std;

class Armador {

public:
	vector<Matriz> armarCMM(vector<Team>);
};

#endif


