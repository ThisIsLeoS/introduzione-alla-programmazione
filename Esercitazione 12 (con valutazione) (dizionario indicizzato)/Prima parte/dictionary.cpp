#include "dictionary.h"

alfabeto_t create_dictionary(alfabeto_t az) // inizializza tutti i puntatori dell' array "az.alfabeto" a "NULL" e lo restituisce
{
	#ifdef DEBUG
	cout << "create_dictionary in\n";
	#endif	
	for (int i=0; i<27; i++) az.alfabeto[i]=create_list();
	#ifdef DEBUG
	cout << "create_dictionary out\n";
	#endif
	return az;
}

void add_word(alfabeto_t & az, string s) // sostanzialmente si occupa di chiamare la f. "f" e quella "add_word" del modulo "word_list"
{
	#ifdef DEBUG
	cout << "add_word in\n";
	#endif		
	char c;
	int i;
	stringstream is(s);
	is.get(c);
	i=f(c);
	add_word(az.alfabeto[i], s);
	#ifdef DEBUG
	cout << "add_word out\n";
	#endif
}

bool contains_word(alfabeto_t & az, string s) // sostanzialmente si occupa di chiamare la f. "f" e quella "contains_word" del modulo "word_list"
{
	#ifdef DEBUG
	cout << "contains_word in\n";
	#endif		
	char c;
	int i;
	bool b;	
	stringstream is(s);
	is.get(c);
	i=f(c);
	if (i<0 || i>25) b=false;
	else b=contains_word(az.alfabeto[i], s);
	#ifdef DEBUG
	cout << "contains_word out\n";
	#endif
	return b;
}

void print_word_by_letter(alfabeto_t & az, char c) // stampa tutte le parole presenti nel dizionario che iniziano per una data lettera
{
	#ifdef DEBUG
	cout << "print_word_by_letter in\n";
	#endif		
	int i;
	cell* cur;
	i=f(c);
	if (i<0 || i>25) cout << "Nel dizionario non ci sono parole che inziano per '" << c << "'\n";
	else
	{
		cur=az.alfabeto[i];
		if (cur==NULL) cout << "Nel dizionario non ci sono parole che inziano per '" << c << "'\n";
		else 
		{	
			cout << "Le parole che iniziano per '" << c << "' contenute nel dizionario sono le seguenti:\n\n";
			while (cur!=NULL) // finchè "cur" non arriva alla fine della lista
			{
				cout << cur->info << endl;
				cur=cur->next;
			}
		}
	}
	#ifdef DEBUG
	cout << "print_word_by_letter out\n";
	#endif	
}

int f(char c) // prende in input un carattere e restituisce il numero che il carattere avrebbe nell' alfabeto se questo seguisse un ordine numerico (a=0, b=1 ecc.)
{
	#ifdef DEBUG
	cout << "f in\n";
	#endif	
	int i=c-'a';
	#ifdef DEBUG
	cout << "f out\n";
	#endif	
	return i;
}


