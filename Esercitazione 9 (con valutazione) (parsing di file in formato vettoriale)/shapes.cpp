#include "shapes.h"

point Set ( float x, float y ) // crea un punto a partire da due float
{
	point p;
	p.x=x;
	p.y=y;
	return p;
}

void Sum ( point & p0, point & p1 ) // somma le x e le y di due punti
{
	p0.x=p0.x+p1.x;
	p0.y=p0.y+p1.y;
}

void scale ( int & x, float & scaleFactor ) // moltiplica un intero per un fattore di scaling
{
	x=(int)(x*scaleFactor); // viene eseguito anche un casting esplicito ad int
}	

void rotate_r ( rectangle & r, int acc )
{
	// dato che la f. che riempirà la matrice, lo farà partendo dal vertice in alto a sinistra della figura e dato che la posizione del vertice in alto a sinistra cambia nelle figure ruotate, la seguente f., a seconda del valore di rotazione, sposta opportunamente il vertice

	int aux; // in una figura ruotata di 90 gradi altezza e larghezza sono scambiate rispetto alla figura non ruotata. "aux" verrà usata per fare questo scambio.
	switch ( acc )
	{
		case 90: 
		{
			r.p.x=r.p.x-r.width;
			aux=r.height;				
			r.height=r.width;
			r.width=aux;
			break;
		}
		case 180:
		{
			r.p.x=r.p.x+r.height-r.width;
			r.p.y=r.p.y-r.height;
			aux=r.height;				
			r.height=r.width;
			r.width=aux;
			break;
		}
		case 270:
		{
			r.p.x=r.p.x+r.height;
			r.p.y=r.p.y+r.width-r.height;
			aux=r.height;				
			r.height=r.width;
			r.width=aux;
			break;	
		}
		case 360:
		{
			r.p.y=r.p.y+r.width;		
			aux=r.height;				
			r.height=r.width;
			r.width=aux;
			break;
		}
	}
}

void scale_p ( float scaleFactor,  point p0, point & p1 ) // ridimensiona il poligono rispetto al primo vertice
{
	// Modifica della x di un vertice, a seconda che sia < o > di quella del primo vertice
	if ( p0.x-p1.x<0 ) p1.x=p0.x+(scaleFactor*((p0.x-p1.x)*-1)); 
	else  
	{	
		if ( p0.x-p1.x>0 ) p1.x=p0.x-(scaleFactor*(p0.x-p1.x));
	}
	// Modifica della y di un vertice, a seconda che sia < o > di quella del primo vertice
	if ( p0.y-p1.y<0 ) p1.y=p0.y+(scaleFactor*((p0.y-p1.y)*-1));
	else 
	{	
		if ( p0.y-p1.y>0 ) p1.y=p0.y-(scaleFactor*(p0.y-p1.y));
	}
}

void rotate_p ( float gradi, point p0, point & p1 ) // ruota il poligono sul primo vertice
{
	point aux, pNew;
	pNew.x=p1.x-p0.x;
	pNew.y=p1.y-p0.y;
	aux.x=pNew.x; // il valore attuale di pNew.x serve anche dopo e, dato che verrà sovrascritto, lo salvo in aux.x
	aux.y=pNew.y; // il valore attuale di pNew.y serve anche dopo e, dato che verrà sovrascritto, lo salvo in aux.y
	// ora applico la formula per ruotare x e y ( i gradi sono trasformati in radianti )	
	pNew.x=((cos((gradi*3.14)/180))*aux.x)-((sin((gradi*3.14)/180))*aux.y); 
	pNew.y=((sin((gradi*3.14)/180))*aux.x)+((cos((gradi*3.14)/180))*aux.y);
	p1.x=pNew.x+p0.x;
	p1.y=pNew.y+p0.y;
}
