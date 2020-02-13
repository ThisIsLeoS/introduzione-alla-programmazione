#include "word_preparation.h"

void lower(string & s) // converte la stringa "s" nella corrispettiva stringa minuscola
{
	#ifdef DEBUG
	cout << "lower in\n";
	#endif	
	char c;
	string aux;
	stringstream is(s);
	s.clear(); // "s" servirà come stringa vuota la prima volta che viene fatta la concatenzione di stringhe (vd. più in basso nel codice)
	while (true)
	{
		is.get(c);
		if (is.eof()) break; // se il flusso "is" è terminato si esce dal ciclo while
		aux=tolower(c); // "tolower" è una f. che prende un char e restituisce il suo equivalente minuscolo
		s=s+aux; // "s" è stata inizializzata come stringa vuota, quindi questo comando non mette in "s" spazzatura
		#ifdef DEBUG			
		cout << s << " "; 
		#endif
	}
	#ifdef DEBUG			
		cout << endl; 
		cout << "lower out\n";
	#endif	
}

bool trim(string & s) 
/* La f. booleana "trim":
1) se la stringa contiene solo caratteri non alfabetici, la svuota (setta la grandezza a 0) e restituisce "false"
2) se la stringa contiene caratteri alfabetici e non, elimina dalla stringa i caratteri non alfabetici e restituisce "true" */
{
	#ifdef DEBUG
	cout << "trim in\n";
	#endif	
	string aux;
	char c; 
	int x;
	stringstream is(s);
	s.clear(); // "s" servirà come stringa vuota la prima volta che viene fatta la concatenzione di stringhe (vd. più in basso nel codice)
	while (true)
 	{
		is.get(c);
		if (is.eof()) break; // se il flusso "is" è terminato, si esce dallo while
		x=c;
		if ((x>64 && x<91) || (x>96 && x<123)) // se x è un intero corrispondente ad un carattere alfabetico non accentato
		{
			aux=x;
			s=s+aux; // al primo ciclo in "s" verrà inserito solo "aux" perchè "s" sarà una stringa vuota
			#ifdef DEBUG			
			cout << s << " "; 
			#endif
		}
	}
	#ifdef DEBUG			
		cout << endl; 
	#endif
	if (s.empty()) // se "s" è vuota significa che non si è mai entrati nel secondo "if" all'interno dello "while" e quindi "s" conteneva solo caratteri non alfabetici
	{	
		#ifdef DEBUG
		cout << "trim out (false)\n";
		#endif
		return false; 
	}
	else 
	{
		#ifdef DEBUG
		cout << "trim out (true)\n";
		#endif
		return true;
	}	
}



