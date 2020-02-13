#include <iostream> // per le stampe a schermo e altro
#include <string> // per la dichiarazione e l'uso di una var. di tipo "string"
#include <fstream> // per la dichiarazione e l'uso di una var. di tipo "ifstream" 
#include "word_preparation.h" // per le chiamate alle f. il cui prototipo è in quel .h
#include "dictionary.h" // per le chiamate alle f. il cui prototipo è in quel .h e altro

using namespace std; // per l'uso di "cout" e altro

int main()
{
	char c;
	bool b;	
	string s;
	alfabeto_t az=create_dictionary(az); // la dichiarazione della "struct" "alfabeto_t" è in "dictionary.h"
	while (true)
	{
		cout 
		<< endl
		<< "a)ggiungi una parola\n" 
		<< "l)eggi tutte le parole di un file\n" 
		<< "c)erca una parola\n"
		<< "s)tampa tutte le parole che iniziano per...\n" 
		<< "e)sci\n\n"
		<< "Fai la tua scelta: "
		;
		cin >> s;
		cout << endl;
		if (s.size()>1) c='z'; // se è stato inserito più di un carattere, si andrà direttamente all'ultimo "else" della prossima cascata di "else if"
		else c=s[0]; // altrimenti viene messo in "c" l' unico carattere della stringa "s"
		if (c=='a')
		{
			while (true)
			{
			  	cout << "Inserisci la parola da aggiungere: ";
			  	cin >> s;
				cout << endl;
				b=trim(s); // viene chiamata prima "trim" di "lower", così potenzialmente verrà passata una stringa più corta a quest'ultima funzione e il calcolatore farà meno lavoro
			  	if (b==false || s.size()<2) cout << "La parola deve avere almeno due caratteri alfabetici\n\n"; // se la stringa conteneva solo caratteri non alfabetici o comunque meno di due caratteri alfabetici
				else 
			  	{
					lower(s);
			  		add_word(az, s);
			  		cout << "La parola è stata aggiunta\n";
					break; 
				}
			}
		}
		else if (c=='l') 
		{ 
			cout << "Inserisci il nome del file: ";
			cin >> s;
			cout << endl;
			ifstream ist (s.c_str());
			if (!ist) cout << "Errore nell'apertura del file\n"; // se "ist" è falso (per es. perchè nn è stato trovato un file che abbia il nome inserito da utente)
		  	else 
			{
				while (!ist.eof()) // finchè non viene raggiunta la fine del file
				{
					ist >> s;
					b=trim(s); // viene chiamata prima "trim" di "lower", così potenzialmente verrà passata una stringa più corta a quest' ultima funzione e il calcolatore farà meno lavoro
					if (b==false || s.size()<2); // se la stringa letta dal flusso contiene solo caratteri non alfabetici o ha meno di due caratteri alfabetici (quelli non alfabetici sono stati eliminati da "trim") non viene fatto nulla
					else
					{					
				  		lower(s);
						add_word(az, s);
					}
				}
				cout << "Il file è stato letto\n";
			}
		}
		else if (c=='c') 
		{
			cout << "Inserisci la parola da cercare: ";
			cin >> s;
			cout << endl;
			b=contains_word(az, s);
			if (b) cout << "La parola è contenuta nel dizionario\n";
			else cout << "La parola non è contenuta nel dizionario\n";
		}	
		else if (c=='s') 
		{		
			while (true)
			{
				cout << "Inserisci la lettera: ";
				cin >> s;
				cout << endl;
				if (s.size()>1) cout << "Devi inserire un solo carattere\n\n"; // se è stato inserito più di un carattere
			  	else
				{					
					c=s[0]; // viene messo in "c" l' unico carattere della stringa "s"
					print_word_by_letter(az,c);
					break;
				}
			}
		}
		else if (c=='e') return 0;
		else cout << "Devi inserire una sola lettera e questa dev'essere compresa tra quelle del menù\n";
	}
}


