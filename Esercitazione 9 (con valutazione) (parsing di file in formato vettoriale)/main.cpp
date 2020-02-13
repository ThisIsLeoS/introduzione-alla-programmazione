#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "matrix.h"
#include "raster.h"
#include "parse.h"


using namespace std;



int main()
{	
	int nrow=100, ncol=100;				// con una piccola modifica potete leggere le dimensioni dal file di input
	matrix RI=matrixNew(nrow, ncol);	// Raster Image (RI) - Un'immagine digitale che per semplicita' codifichiamo con int. 
									
	string line;
	string dummy, shape;
	
	ifstream in;
	in.open("data.vec");
	if (!in) {
		cerr << "Error" << endl;
		return(-1);
	}
	
	init_raster(RI,nrow,ncol); // funzione che inizializza un'immagine digitale assegnando 0 a tutti i pixel
	
	getline(in,line);
	
	while(in) {
	
		stringstream lineStream(line);
	
		// Parsing dell'input: immagazzino gli elementi in variabili del tipo opportuno
		lineStream >> dummy >> shape;
		
		if (shape=="rect") {
			process_rectangle(lineStream,RI,nrow,ncol); //interpreto la riga e aggiorno RI
		}
		
		else if (shape=="circle") {
			process_circle(lineStream,RI,nrow,ncol); //interpreto la riga e aggiorno RI
		}
		
		else if (shape=="poly") {
			process_polygon(lineStream,RI,nrow,ncol); //interpreto la riga e aggiorno RI
		}
		
		else if (shape=="repeat") {
			process_repeat(lineStream, RI, nrow, ncol); //interpreto la riga e aggiorno RI
		}
			
		else {
			cout << "I don't recognize this tag, I'm skipping the line: " << lineStream.str() << endl;
		}

		getline(in,line);
	}
	
	write_image("raster.pgm",RI, nrow, ncol);
	
	cout << "Conversion completed\n";
	return(1);
}
		


