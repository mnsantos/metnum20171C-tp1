#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <utility>
#include <iostream>
#include "Parametros.h"
#include "matriz.h"
#include <fstream>
#include <stdio.h>
#include <map>

using namespace std;

class FileManager {

public:
	FileManager(string pathFileIn, string pathFileOut, string method);
    Parametros read();
    void write(Parametros params, Matriz result);

private:
    string inputFile;
    string outputFile;
    string method;
    map<int, int> teamsMap;

};

#endif