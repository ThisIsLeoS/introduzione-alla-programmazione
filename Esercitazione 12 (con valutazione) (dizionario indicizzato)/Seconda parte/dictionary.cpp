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

void add_word(alfabeto_t & az, string s) // sostanzialmente si occupa di chiamare la f. "f" e quella "add_word" del modulo "another_list"
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

void change_next_couple(alfabeto_t & az, string s) // sostanzialmente si occupa di chiamare la f. "f" e quella "change_next_couple" del modulo "another_list"
{
	#ifdef DEBUG
	cout << "change_next_couple in\n";
	#endif		
	char c;
	int i;
	stringstream is(s);
	is.get(c);
	i=f(c); 
	change_next_couple(az.alfabeto[i], s); 
	#ifdef DEBUG
	cout << "change_next_couple out\n";
	#endif	
}

bool contains_word(alfabeto_t & az, string s) // sostanzialmente si occupa di chiamare la f. "f" e quella "contains_word" del modulo "another_list"
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

void print_word_by_couple(alfabeto_t & az, string s) // stampa tutte le parole presenti nel dizionario che iniziano per la coppia di lettere contenuta in "s"
{
	#ifdef DEBUG
	cout << "print_word_by_couple in\n";
	#endif		
	int i,j;
	char c;	
	cell* cur;
	cell* aux;
	string s1,s2;
	stringstream is(s);
	is.get(c);
	i=f(c);
	is.get(c);
	j=f(c);
	if (i<0 || i>25 || j<0 || j>25) // se uno od entrambi i caratteri inseriti non sono caratteri alfabetici minuscoli
	{
		cout << "Nel dizionario non ci sono parole che iniziano per '" << s << "'\n";
		#ifdef DEBUG
		cout << "print_word_by_couple out\n";
		#endif	
		return;	
	}	
	cur=az.alfabeto[i];
	while (cur!=NULL && cur->info!=s && cur->info<s) cur=cur->next; // finchè "cur" non punta a "NULL" o ad una cella con una stringa maggiore di oppure uguale a "s" (se "s" contiene "ab" alla fine dello "while" "cur" punterà ad una cella contenente per es. "abaco" o, se non ci fossero stringhe che iniziano per "ab", "acero" o altro)
	if (cur==NULL) cout << "Nel dizionario non ci sono parole che iniziano per '" << s << "'\n";		
	else // altrimenti bisogna verificare che "cur" punti effettivamente ad una cella contenente una stringa che inizia per "s"
	{
		stringstream is(cur->info);
		is.get(c);
		s1=c;
		is.get(c);
		s2=c;
		s1=s1+s2; // in "s1" vengono messi i primi due caratteri della stringa contenuta nella cella puntata da "cur"
		if (s1==s)
		{	
			cout << "Le parole che iniziano per '" << s << "' contenute nel dizionario sono le seguenti:\n\n";		
			aux=cur;
			while (cur!=NULL && aux->next_couple==cur->next_couple) // finchè le celle puntate da "cur", hanno "cur->next_couple" uguale a quello della prima cella del gruppo di quelle contenenti stringhe che iniziano per una data coppia di caratteri
			{	
				cout << cur->info << endl;
				cur=cur->next;	
			}
		}
		else cout << "Nel dizionario non ci sono parole che iniziano per '" << s << "'\n";
	}
	#ifdef DEBUG
	cout << "print_word_by_couple out\n";
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


