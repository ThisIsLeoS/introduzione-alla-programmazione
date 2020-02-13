#include "another_list.h"

cell* create_list() // restituisce un puntatore a "NULL" (ovvero una lista vuota)
{
	#ifdef DEBUG
	cout << "create list another_list in\n";
	#endif
	cell* cur;
	cur=NULL;
	#ifdef DEBUG
	cout << "create list another_list out\n";
	#endif
	return cur;
}

void add_word(cell* & cur, string s)
// Questa f. inserisce la stringa in input nella lista in input, a meno che la stringa non sia già presente (nota: il puntatore alla testa della lista non viene modificato).
{
	#ifdef DEBUG
	cout << "add_word another_list in\n";
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
			cout << "add_word another_list out\n";
			#endif
			return;
		}
		add_word(cur->next, s); // nota: non viene persa la testa della lista ("cur"), perchè ogni volta è passato "cur->next" non "cur" ("cur->next" diventa poi il parametro formale "cur", quindi sostanzialmente alla seconda chiamata verrà passato "cur->next->next", alla terza "cur->next->next->next" e così via, questo ci dice anche che ad ogni chiamata verrà considerato un elemento in meno rispetto alla chiamata precedente)
	}
	#ifdef DEBUG
	cout << "add_word another_list out\n";
	#endif
}

void change_next_couple(cell* testa, string s)
/* Questa f. si occupa di far puntare "next_couple" della stringa "s" in input alla cella contenente la stringha che inizia per la coppia di caratteri maggiore secondo l' ordine lessicografico. Inoltre, se "s" è la prima stringa di un gruppo che inizia per una data coppia di caratteri, si occupa di cambiare i membri "next_couple" che puntano alla ex prima stringa del gruppo (nota: questa f. presuppone che "s" sia già stata inserita nella lista) */
{
	#ifdef DEBUG
	cout << "change_next_couple another_list in\n";
	#endif
	int x;
	char c;
	string s_couple, s_couple_next, s1, s2;
	cell* cur=testa; // cur viene fatto puntare alla testa della lista
	cell* aux;
	cell* aux1;
	stringstream is(s);
	is.get(c);
	s1=c; // in "s1" viene messo il primo carattere di "s"
	is.get(c);
	s2=c; // in "s2" viene messo il secondo carattere di "s"
	s_couple=s1+s2;
	while (cur->info!=s && cur->info<s_couple) cur=cur->next; // finchè non viene trovata una stringa > = quella composta dalle prime due lettere di "s", ovvero finchè non viene trovata la prima stringa del gruppo di stringhe che iniziano per "s_couple" (nota: prima di questa f. è stata chiamata "add_word", quindi "s" è già stata inserita nella lista e quindi non c'è bisogno di avere "cur!=NULL" come condizione di continuazione)
	aux=cur;
	while (cur->info!=s) cur=cur->next; // se "s" è la prima stringa del gruppo di stringhe che iniziano per "s_couple", non si ciclerà
	aux1=cur;
	x=c;
	s2=x+1; // in "s2" viene messo il carattere successivo al secondo della stringa "s"
	s_couple_next=s1+s2; // in "s_couple_next" vengono messi il primo carattere della stringa "s" e il successivo al secondo ( es.: stringa in input "abaco", in "s" verrà messo "ac" )
	while ((cur!=NULL) && (cur->info!=s_couple_next) && (cur->info<s_couple_next)) cur=cur->next; // finchè "cur" non punta alla cella contenente la prima stringa del gruppo di stringhe che iniziano per s_couple_next (es.: se "s" contiene "abaco", "cur" punterà ad una cella contenente una stringa maggiore di "ac", per es. "acacia" o "attimo" o qualunque sia la prima stringa maggiore di quelle che iniziano per "ab") (nota: non va "OR" perchè altrimenti anche se "cur" puntasse alla fine della lista ("cur!=NULL" fosse falsa) per determinare il risultato del test verrebbe verificata anche la seconda condizione, ma "cur->info" non esisterebbe)
	aux1->next_couple=cur; // la stringa "s" viene fatta puntare alla cella contenente la stringha che inizia per la coppia di caratteri maggiore secondo l'ordine lessicografico
	if (aux->info==s) // se "s" è la prima stringa del gruppo di stringhe che iniziano per "s_couple_next" (e quindi la ex prima stringa sarà situtata nella cella dopo quella che contiene "s", ovvero in "cur->next")
	{
		cur=testa; // cur viene fatto puntare alla testa della lista
		while ((cur->info)!=(aux->info)) // finchè cur non punta alla cella contenente "s"
		{
			if (cur->next_couple==aux->next) cur->next_couple=aux; // se "cur->next_couple" punta alla ex prima stringa del gruppo di stringhe che iniziano per "s_couple_next", viene fatta puntare alla nuova prima stringa
			cur=cur->next;
		}
	}
	#ifdef DEBUG
	cout << "change_next_couple another_list out\n";
	#endif
}

bool contains_word(cell* cur, string s )
// Questa f. cerca la stringa in input nella lista in input e restituisce "false" se non la trova, "true" se la trova (nota: il puntatore alla testa della lista non viene modificato).
{
	#ifdef DEBUG
	cout << "contains_word another_list in\n";
	#endif
	if (cur==NULL)
	{
		#ifdef DEBUG
		cout << "contains_word another_list out (false)\n";
		#endif
		return false;
	}
	if (cur->info==s)
	{
		#ifdef DEBUG
		cout << "contains_word another_list out (true)\n";
		#endif
		return true;
	}
	return contains_word(cur->next, s); // non viene persa la testa della lista ( "cur" ), perchè ogni volta è passato "cur->next" non "cur" ("cur->next" diventa poi il parametro formale "cur", quindi sostanzialmente alla seconda chiamata verrà passato "cur->next->next", alla terza "cur->next->next->next" e così via, questo ci dice anche che ad ogni chiamata verrà considerato un elemento in meno rispetto alla chiamata precedente)
}
