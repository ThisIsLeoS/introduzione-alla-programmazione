// è assunta la correttezza dei comandi del file .vec

#include "parse.h"

vector <lineIdentifier_t> archivio; // il vector "archivio" conterrà le struct che identificano le righe contenenti "id". La dichiarazione è nello scope globale perchè il vector dev' essere visto da tutte le funzioni

void process_rectangle ( stringstream & flussoRiga, matrix & RI, int nrow, int ncol )
{
	rectangle r;
	int acc=0; // var. che è usata per accumulare i valori di rotazione ( 90, 180 ecc. )
	string transformation; // "transformation" conterrà di volta in volta "move" o "rotate" o "scale" o ">" o "id" 
	string lineContainer; // "lineContainer" conterrà provvisoriamente la riga arrivata a "process_rectangle" in "flussoRiga"
	lineIdentifier_t lineAndId; // "lineAndId" conterrà "rect" + la riga arrivata a "process_rectangle" e, se presente, il nome che identifica la riga ( es. rettangolo1 )
	getline(flussoRiga,lineContainer); 
	lineAndId.line="rect"+lineContainer; // ora in "lineAndId.line" c' è la riga da "rect" in poi
	stringstream lineStream ( lineContainer ); // riapro il flusso, precedentemente chiuso con la getline
	lineStream >> r.p.x >> r.p.y >> r.height >> r.width >> transformation; 
	if ( transformation==">" ) popola_matrix_r ( RI, nrow, ncol, r ); 
	else
	{	
		while ( transformation != ">" )
		{
			if ( transformation=="move" )
			{
				point p1; 			
				lineStream >> p1.x >> p1.y >> transformation;
				Sum(r.p, p1); 
				if ( transformation==">" ) popola_matrix_r ( RI, nrow, ncol, r );
			}
			else if ( transformation=="rotate" ) 
			{
				int rtt;				
				lineStream >> rtt >> transformation;
				acc=acc+rtt; // acc è stato inizializzato a 0 prima del while, quindi rtt non è addizionato a "spazzatura"
				if ( acc==450 ) acc=90; // una rotazione di 450 gradi da lo stesso risultato di una di 90 e, dato che la f. "rotate_r" gestisce 4 casi ( 90, 180, 270, 360 ), se acc=450, la riporto a 90
				rotate_r ( r, acc ); // il passaggio dei paramentri è per riferimento
				if ( transformation==">" ) popola_matrix_r ( RI, nrow, ncol, r );
			}
			else if ( transformation=="scale")
			{
				float scaleFactor; 
				lineStream >> scaleFactor >> transformation;
				scale( r.height, scaleFactor ); // il passaggio dei parametri è per riferimento
				scale( r.width, scaleFactor );
				if ( transformation==">" ) popola_matrix_r ( RI, nrow, ncol, r );
			}
			else if ( transformation=="id" ) 
			{
				popola_matrix_r ( RI, nrow, ncol, r );
				lineStream >> lineAndId.id >> transformation;				
				// a questo punto in "lineAndId" sono contenuti "rect" + la riga arrivata a "process_rectangle" e anche l' identificatore ( per es. rettangolo1 )
				archivio.push_back(lineAndId); // metto lineAndId nel vector "archivio"			
			}
			else
			{		
				popola_matrix_r ( RI, nrow, ncol, r );
				cout << "I don't recognize the tag '" << transformation << "', I'm skipping the part of the line '< rect " << lineStream.str() << "' beyond that tag" << endl;
				transformation=">";
			}
		}
	}
}

void process_circle ( stringstream & flussoRiga, matrix & RI, int nrow, int ncol )
{
	circle c;	
	string transformation; // "transformation" conterrà di volta in volta "move" o "rotate" o "scale" o ">" o "id" 
	string lineContainer; // "lineContainer" conterrà provvisoriamente la riga arrivata a "process_circle" in "flussoRiga"
	lineIdentifier_t lineAndId; // "lineAndId" conterrà "circle" + la riga arrivata a "process_circle" e, se presente, il nome che identifica la riga ( es. cerchio1 )
	getline(flussoRiga,lineContainer); 
	lineAndId.line="circle"+lineContainer;// ora in "lineAndId.line" c' è la riga da "circle" in poi
	stringstream lineStream ( lineContainer ); // riapro il flusso, precedentemente chiuso con la getline
	lineStream >> c.p.x >> c.p.y >> c.radius >> transformation; 
	if ( transformation==">" ) popola_matrix_c ( RI, nrow, ncol, c );
	else
	{	
		while ( transformation != ">" )
		{
			if ( transformation=="move" )
			{
				point p1; 			
				lineStream >> p1.x >> p1.y >> transformation;
				Sum ( c.p, p1 ); // il passaggio dei parametri è per riferimento
				if ( transformation==">" ) popola_matrix_c ( RI, nrow, ncol, c );	
			}
			else if ( transformation=="rotate") // l' immagine con un cerchio non ruotato e quella con il cerchio ruotato rispetto all' origine sono identiche, quindi non viene fatto nulla
			{
				int rtt;
				lineStream >> rtt >> transformation;
				if ( transformation==">" ) popola_matrix_c ( RI, nrow, ncol, c );
			}
			else if ( transformation=="scale")
			{
				float scaleFactor; 
				lineStream >> scaleFactor >> transformation;
				scale ( c.radius, scaleFactor ); // il passaggio dei parametri è per riferimento
				if ( transformation==">" ) popola_matrix_c ( RI, nrow, ncol, c );	
			}
			else if ( transformation=="id" )
			{
				popola_matrix_c ( RI, nrow, ncol, c );
				lineStream >> lineAndId.id >> transformation;			
				// a questo punto in "lineAndId" sono contenuti "circle" + la riga arrivata a "process_circle" e anche l' identificatore ( per es. cerchio1 )
				archivio.push_back(lineAndId); // metto lineAndId nel vector "archivio"			
			}
			else
			{		
				popola_matrix_c ( RI, nrow, ncol, c );
				cout << "I don't recognize the tag '" << transformation << "', I'm skipping the part of the line '< circle " << lineStream.str() << "' beyond that tag" << endl;
				transformation=">";
			}
		}
	}
}

void process_polygon ( stringstream & flussoRiga, matrix & RI, int nrow, int ncol )
{
	polygon p;
	string transformation; // "transformation" conterrà di volta in volta "move" o "rotate" o "scale" o ">" o "id" 
	string lineContainer; // "lineContainer" conterrà provvisoriamente la riga arrivata a "process_polygon" in "flussoRiga"
	lineIdentifier_t lineAndId; // "lineAndId" conterrà "poly" + la riga arrivata a "process_polygon" e, se presente, il nome che identifica la riga ( es. poligono1 )
	int found; // "found" conterrà il valore di ritorno della f. "find_first_of"
	int size; // "size" conterrà il numero di elementi presenti nel vector "archivio"
	float vertexX, vertexY; 
	point vertex;
	getline(flussoRiga,lineContainer); 
	lineAndId.line="poly"+lineContainer; // ora in "lineAndId.line" c' è la riga da "poly" in poi
	stringstream lineStream ( lineContainer ); // riapro il flusso, precedentemente chiuso con la getline
	p.vertex.clear(); // svuoto il vector contenente i vertici del poligono, perchè potrebbero esserci vertici derivanti da una riga "poly" precendete a quella ora valutata

	// nel seguente do-while verrà riempito il vector "vertex", membro della struct polygon, con i vertici del poligono. Il vector è di tipo point e i membri di point sono di tipo float, quindi verrà fatta una lettura formattata del flusso lineStream, valutato se ciò che è stato letto è una stringa numerica e se così fosse, convertita la stringa numerica in un float da mettere nel vector. Quando non verrà più trovata una stringa numerica, significherà che i vertici nella riga "poly" sono finiti

	do
	{		
		lineStream >> transformation; 
		// va capito ora se in transformation c' è una striga numerica ( la x del vertice ) o meno		
		found=transformation.find_first_of("1234567890"); // nella var. "transformation" viene cercato un carattere compreso tra 0 e 9
		if ( found==-1 ); // se il carattere non viene trovato non viene fatto nulla e si uscirà dal ciclo
		else // se il carattere viene trovato significa che in transformation c' è effivamente una stringa numerica
		{
			// trasformo la stringa numerica in "transformation" in un float
			stringstream lineStream1(transformation); 
			lineStream1 >> vertexX; 
			// trasformo la stringa numerica successiva ( mi aspetto che sia una stringa numerica perchè dopo la x deve esserci la y ) in un float			
			lineStream >> vertexY;
			vertex=Set( vertexX, vertexY ); // viene chiamata una f. che trasforma vertexX e vertexY in un punto
			p.vertex.push_back(vertex); // metto il punto nel vector "vertex" ( membro della struct polygon )
		}
	}
	while ( found != -1 );
	
	// alla fine dello while in "transformation" c' è una stringa non numerica
	if ( transformation==">" ) popola_matrix_p ( RI, nrow, ncol, p );
	else
	{	
		while ( transformation != ">" )
		{
			if ( transformation=="move" )
			{
				point p1; 			
				lineStream >> p1.x >> p1.y >> transformation;
				size=p.vertex.size();
				for ( int i=0; i<size; i++ ) Sum ( p.vertex[i], p1 ); // sommo tutti i vertici al punto p1. Il passaggio dei praramentri è per riferimento
				if ( transformation==">" ) popola_matrix_p ( RI, nrow, ncol, p );	
			}
			else if ( transformation=="rotate")
			{ 
				float gradi;
				lineStream >> gradi >> transformation;				
				size=p.vertex.size();
				for ( int i=1; i<size; i++ ) rotate_p (  gradi, p.vertex[0], p.vertex[i] ); // ruoto tutti i vertici rispetto al primo. Il passaggio del vertice i-esimo è per riferimento
				if ( transformation==">" ) popola_matrix_p ( RI, nrow, ncol, p );	
			}
			else if ( transformation=="scale")
			{
				float scaleFactor; 
				lineStream >> scaleFactor >> transformation;
				size=p.vertex.size();
				for ( int i=1; i<size; i++ ) scale_p ( scaleFactor, p.vertex[0], p.vertex[i] ); // scalo tutti i vertici rispetto al primo. Il passaggio del vertice i-esimo è per riferimento
				if ( transformation==">" ) popola_matrix_p ( RI, nrow, ncol, p );	
			}
			else if ( transformation=="id" )
			{
				popola_matrix_p ( RI, nrow, ncol, p );
				lineStream >> lineAndId.id >> transformation;	
				// a questo punto in "lineAndId" sono contenuti "poly" + la riga arrivata a "process_polygon" e anche l' identificatore ( per es. poligono1 )
				archivio.push_back(lineAndId); // metto lineAndId nel vector "archivio"							
			}
			else
			{
				popola_matrix_p ( RI, nrow, ncol, p );
				cout << "I don't recognize the tag '" << transformation << "', I'm skipping the part of the line '< poly " << lineStream.str() << "' beyond that tag" << endl;
				transformation=">";
			}
		}
	}
}

void process_repeat ( stringstream & lineStream, matrix & RI, int nrow, int ncol )
{
	/* la f. repeat si occupa di costruire le righe da passare alle funzioni "process". Per es. per la riga < repeat triangolo1 3 move 10 10 > andranno costruite 3 righe di questo genere: 
1) < <riga corrispondete a triangolo1> move 10 10 >
2) < <riga corrispondete a triangolo1> move 10 10 move 10 10 >
3) < <riga corrispondete a triangolo1> move 10 10 move 10 10 move 10 10 >*/
	
	string id; // id conterrà il nome della riga da ripetere
	int n; // n conterrà il numero di volte per il quale la riga deve essere ripetuta ( con le opportune aggiunte )
	lineStream >> id >> n;
	int size; 
	size=archivio.size();
	if ( size==0 ) // se il vector "archivio" è vuoto, non c' è nulla da ripetere
	{
		cout << "L' archivio è vuoto, " << "salto la riga: < repeat " << lineStream.str () << endl;
		return;
	}
	int i;	// dicharo "i" fuori dal for perchè serve anche dopo 
	for ( i=0; i<size; i++ ) // cerco nel vector "archivio" il nome della riga da ripetere 
	{
		if ( archivio[i].id==id ) break;
	}
	if ( archivio[i].id != id ) // il nome della riga da ripetere non è nel vector "archivio"
	{ 
		cout << "Non ho trovato '" << id << "' nell' archivio, salto la riga: < repeat " << lineStream.str () << endl; 
		return;
	}
	// A partire da qui verranno costruite le righe.
	string aux, line1; // la stringa line1 conterrà la riga trovata nel vector "archivio" meno la porzione da "id" in poi
	stringstream lineStream1 ( archivio[i].line ); // con il flusso "lineStream1" verrà riempita la var. "line1"
	lineStream1 >> aux; 
	line1=aux+" "; 
	while ( true ) 
	{	
		lineStream1 >> aux;
		if ( aux != "id" )
		{		
			line1=line1+aux+" ";
		}
		else break;
	}
	string line2; // la stringa line2 conterrà la parte della riga arrivata alla f. "process_repeat" che non è ancora stata estratta ( quindi da "n" esclusa in poi )
	lineStream >> aux; // con il flusso "lineStream" verrà riempita la var. "line2"
	line2=aux+" ";	
	while ( true )
	{
		lineStream >> aux;
		if ( aux != ">" )
		{		
			line2=line2+aux+" ";
		}
		else break;
	}
	// a questo punto devo costruire le "n" righe come nell' esempio sopra riportato
	string line, line3, shape; 
	for ( int i=0; i<n; i++ )
	{			
		line1=line1+line2; // ad ogni ciclo line1 conterrà se stessa più i volte line2
		line3=line1+">";
		stringstream lineStream2(line3);
		lineStream2 >> shape;
		if ( shape=="rect" ) process_rectangle(lineStream2,RI,nrow,ncol);
		if ( shape=="circle" ) process_circle(lineStream2,RI,nrow,ncol);
		if ( shape=="poly" ) process_polygon(lineStream2,RI,nrow,ncol); 
	}
}
