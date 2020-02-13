#ifndef PARSE_H
#define PARSE_H

#include <iostream> // incluso per i cout di debug
#include <fstream> // incluso per process_rectangle e altro
#include <string> // incluso per process_rectangle e altro
#include <sstream> // incluso per process_rectangle e altro
#include <vector> // incluso per process_rectangle e altro
#include "matrix.h" // incluso per process_rectangle e altro
#include "shapes.h" // incluso per process_rectangle e altro
#include "raster.h" // incluso per process_rectangle e altro

using namespace std;

struct lineIdentifier_t // Le var. di questo tipo andranno nel vector "archivio" ( ho aggiunto "t" per ricordarmi che si tratta di un tipo )
{
	string id;
	string line;
};

void process_rectangle(stringstream &, matrix &, int, int);
void process_circle(stringstream &, matrix &, int, int);
void process_polygon(stringstream &, matrix &, int, int);
void process_repeat(stringstream &, matrix &, int, int);

#endif


