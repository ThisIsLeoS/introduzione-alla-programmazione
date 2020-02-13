#include "raster.h"

void init_raster( matrix & RI, int nrow, int ncol) // inizializza la matrice assegnando 0 a tutti i suoi elementi
{
	for ( int i=0; i<nrow; i++ )
	{
		for ( int j=0; j<ncol; j++ ) RI[i][j]=0;
	}	
}

void popola_matrix_r ( matrix & RI, int nrow, int ncol, rectangle r ) // popola la matrice col rettangolo a partire dal vertice in alto a sinistra del rettangolo
{
	for ( int i=r.p.x; i<r.p.x+r.height; i++ ) 
	{
		for ( int j=r.p.y; j<r.p.y+r.width; j++ ) 
		{
			if ( i<0 || i>(nrow-1) || j<0 || j>(ncol-1) ); // se il punto è fuori dalla matrice, non viene fatto nulla
			else RI[i][j]=255; 
		}
	}
}

void popola_matrix_c ( matrix & RI, int nrow, int ncol, circle c) // popola la matrice col cerchio
{
	// viene considerato un quadrato di lato lungo quanto il diametro del cerchio
	for ( int i=c.p.x-c.radius; i<c.p.x+c.radius; i++ ) 
	{
		for ( int j=c.p.y-c.radius; j<c.p.y+c.radius; j++ ) 
		{
			if ( i<0 || i>(nrow-1) || j<0 || j>(ncol-1) ); // se il punto è fuori dalla matrice, non viene fatto nulla
			else 
			{
				if(((i-c.p.x)*(i-c.p.x))+((j-c.p.y)*(j-c.p.y))<=(c.radius*c.radius)) RI[j][i]=255; //mi sono basato sull' equazione cartesiana della circonferenza ( (x-a)^2+(y-b)^2=r^2 con centro di coordinate (a,b) )
			}
		}
	}
}

void popola_matrix_p ( matrix & RI, int nrow, int ncol, polygon p )
{
	int i=0; // i indica la posizione dei vertici nel vector "vertex", verrà incrementata alla fine di ogni ogni ciclo dello while
	int size;
	size=p.vertex.size(); // la size del vector mi serve per sapere quante volte aumentare "i"
	if ( size>2 ) // se ci sono almeno 3 punti nel vector
	{	
		point aux;
		aux=p.vertex[i];
		p.vertex.push_back(aux); // viene messo il primo vertice anche in coda al vector perchè l' ultimo segmento andrà tracciato fra l' ultimo vertice ed il primo 	
	}
	if ( size==1 ) // se c' è solo un vertice viene scritto solo lui
	{
		int x=p.vertex[i].x;
		int y=p.vertex[i].y;
		if ( x<0 || x>(nrow-1) || y<0 || y>(ncol-1) ); // se il punto è fuori dalla matrice, non fare nulla		
		else RI[y][x]=255;
	}		
	else
	{
	// applico il for alla variabile indipendente e calcolo il punto su quella dipendente ( così come suggerito dalla prof. Odone sul forum )
	// con questa procedura più il segmento è verticale, più ci saranno dei buchi nello stesso ( se le x di due vertici disteranno di 0 unità ( retta verticale ), non verranno scritti punti, se le x di due vertici disteranno di 1 unità, verrà scritto un solo punto ecc. )
	while ( i<size )
	{
		if ( p.vertex[i].x != p.vertex[i+1].x ) // se il segmento non è verticale
		{
			if ( p.vertex[i].x < p.vertex[i+1].x ) // se il primo vertice ha una x < a quella del secondo
			{
				for ( int x=p.vertex[i].x; x<=p.vertex[i+1].x; x++ ) // popola la matrice a partire dalla x del primo vertice
				{
					int y=p.vertex[i].y + ((( p.vertex[i+1].y - p.vertex[i].y ) / ( p.vertex[i+1].x - p.vertex[i].x )) * ( x - p.vertex[i].x ));
					if ( x<0 || x>(nrow-1) || y<0 || y>(ncol-1) ); // se il punto è fuori dalla matrice, non fare nulla		
					else RI[y][x]=255;
				}
			}
			else // se il primo vertice ha una x > di quella del secondo
			{	
				for ( int x=p.vertex[i+1].x; x<=p.vertex[i].x; x++ ) // popola la matrice a partire dalla x del secondo vertice
				{
					int y=p.vertex[i].y + ((( p.vertex[i+1].y - p.vertex[i].y ) / ( p.vertex[i+1].x - p.vertex[i].x )) * ( x - p.vertex[i].x ));
					if ( x<0 || x>(nrow-1) || y<0 || y>(ncol-1) ); // se il punto è fuori dalla matrice, non fare nulla		
					else RI[y][x]=255;
				}
			}
		}
		else // se il segmento è verticale
		{	
			int x=p.vertex[i].x; // la x rimane invariata
			if ( p.vertex[i].y < p.vertex[i+1].y ) // se la y del primo vertice è < a quella del secondo
			{		
				for ( int y=p.vertex[i].y; y<p.vertex[i+1].y; y++ ) // popola la matrice a partire dalla y del primo vertice
				{			
					if ( x<0 || x>(nrow-1) || y<0 || y>(ncol-1) ); // se il punto è fuori dalla matrice, non fare nulla		
					else RI[y][x]=255;
				}
			}
			else // se la y del primo vertice è > di quella del secondo
			{
				for ( int y=p.vertex[i+1].y; y<p.vertex[i].y; y++ ) // popola la matrice a partire dalla y del secondo vertice
				{			
					if ( x<0 || x>(nrow-1) || y<0 || y>(ncol-1) ); // se il punto è fuori dalla matrice, non fare nulla		
					else RI[y][x]=255;
				}
			}
		}
		i++;
	}
	}
}

void write_image ( string filename, matrix & RI, int nrow, int ncol )
{
	string tmp;
	ofstream ost(filename.c_str());
	if (!ost) {
		cout << "Errore nell'apertura del file\n";
	}
	ost << "P2\n" << nrow << " " << ncol << endl << "255" << endl; // scrivo l'header.
	for(int i=0;i<nrow;i++)
	{
		for(int j=0;j<ncol;j++)
		{
			ost << RI[i][j] << " ";
		}
		ost << endl;
	}
	ost.close();
}


