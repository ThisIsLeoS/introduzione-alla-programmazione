#ifndef SHAPES_H
#define SHAPES_H

#include <iostream> // incluso per il debugging
#include <vector> // incluso per la struct polygon
#include <math.h> // incluso per rotate_p

using namespace std;

struct point
{
	float x; 
	float y;
};

struct rectangle
{
	point p; // il vertice in alto a sinistra
	int height;
	int width;
};

struct circle
{
	point p; // il centro
	int radius;
};

struct polygon
{
	vector <point> vertex; // vector contenente i vertici del poligono
};

point Set ( float, float );
void Sum ( point &, point & );
void scale ( int &, float & );
void rotate_r ( rectangle &, int );
void scale_p ( float, point, point & );
void rotate_p ( float, point, point & );

#endif
