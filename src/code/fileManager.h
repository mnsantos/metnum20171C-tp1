#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <utility>
#include <iostream>
#include "parametros.h"
#include "matriz.h"
#include "team.h"
#include <fstream>
#include <stdio.h>
#include <map>

using namespace std;

class FileManager {

public:
	FileManager(string pathFileIn, string pathFileOut, string method);
    Parametros read();
    void write(Matriz result);
    void writeTimeTestResults(Matriz result);

private:
    string inputFile;
    string outputFile;
    string method;
};

#endif