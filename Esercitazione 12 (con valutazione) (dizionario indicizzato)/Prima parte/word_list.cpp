#include "word_list.h"

cell* create_list() // restituisce un puntatore a "NULL" (ovvero una lista vuota)
{
	#ifdef DEBUG
	cout << "create list word_list in\n";
	#endif
	cell* cur;
	cur=NULL;
	#ifdef DEBUG
	cout << "create list word_list out\n";
	#endif
	return cur;
}

void add_word(cell* & cur, string s)
// Questa f. inserisce la stringa in input nella lista in input, a meno che la stringa non sia già presente (nota: il puntatore alla testa della lista non viene modificato).
{
	#ifdef DEBUG
	cout << "add_word word_list in\n";
	#endif
	if ((cur==NULL) || (cur->info>s)) // se la lista è vuota o la lista non è vuota e il primo elemento è maggiore della stringa in input, verrà fatto un inserimento in testa
	{
		cell* aux=new cell;
		aux->info=s;
		aux->next=cur;
		cur=aux; // viene fatto puntare "cur" alla nuova prima cella
	}
	else
	{
		if (cur->info==s) // se la stringa è già presente nella lista, si esce dalla f.
		{
			#ifdef DEBUG
			cout << "add_word word_list out\n";
			#endif
			return;
		}
		add_word(cur->next, s); // nota: non viene persa la testa della lista ("cur"), perchè ogni volta è passato "cur->next" non "cur" ("cur->next" diventa poi il parametro formale "cur", quindi sostanzialmente alla seconda chiamata verrà passato "cur->next->next", alla terza "cur->next->next->next" e così via, questo ci dice anche che ad ogni chiamata verrà considerato un elemento in meno rispetto alla chiamata precedente)
	}
	#ifdef DEBUG
	cout << "add_word word_list out\n";
	#endif
}

bool contains_word(cell* cur, string s )
// Questa f. cerca la stringa in input nella lista in input e restituisce "false" se non la trova, "true" se la trova (nota: il puntatore alla testa della lista non viene modificato).
{
	#ifdef DEBUG
	cout << "contains_word word_list in\n";
	#endif
	if (cur==NULL)
	{
		#ifdef DEBUG
		cout << "contains_word word_list out (false)\n";
		#endif
		return false;
	}
	if (cur->info==s)
	{
		#ifdef DEBUG
		cout << "contains_word word_list out (true)\n";
		#endif
		return true;
	}
	return contains_word(cur->next, s); // non viene persa la testa della lista ( "cur" ), perchè ogni volta è passato "cur->next" non "cur" ("cur->next" diventa poi il parametro formale "cur", quindi sostanzialmente alla seconda chiamata verrà passato "cur->next->next", alla terza "cur->next->next->next" e così via, questo ci dice anche che ad ogni chiamata verrà considerato un elemento in meno rispetto alla chiamata precedente)
}
