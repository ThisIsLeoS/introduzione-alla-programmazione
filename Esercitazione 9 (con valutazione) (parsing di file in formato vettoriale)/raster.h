#ifndef RASTER_H
#define RASTER_H

#include <iostream> // incluso per cout di debug e per write_image
#include <fstream> // incluso per write_image 
#include <string> // incluso per write_image
#include <vector> // incluso per popola_matrix_p e altro
#include "matrix.h" // incluso per init_raster e altro
#include "shapes.h" // incluso per popola_matrix_r e altro

using namespace std;

void init_raster( matrix &, int, int);
void popola_matrix_r ( matrix &, int, int, rectangle );
void popola_matrix_c ( matrix &, int, int, circle );
void popola_matrix_p ( matrix &, int, int, polygon );
void write_image ( string, matrix &, int, int );

#endif
