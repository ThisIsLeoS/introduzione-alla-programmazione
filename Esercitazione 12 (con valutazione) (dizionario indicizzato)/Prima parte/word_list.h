#ifndef WORD_LIST_H
#define WORD_LIST_H

#include <iostream> // per le stampe a schermo e altro
#include <string> // per la f. "add_word" e altro
#include <sstream> // per la f. "change_next_couple"

using namespace std; // perchè è usato "string" e altro

#define a

struct cell
{
	string info;
	cell* next;
};

cell* create_list(); // restituisce un puntatore a "NULL" (ovvero una lista vuota)
void add_word(cell* &, string); // inserisce la stringa in input nella lista in input, a meno che la stringa non sia già presente (nota: il puntatore alla testa della lista non viene modificato)
bool contains_word(cell*, string); // cerca la stringa in input nella lista in input e restituisce "false" se non la trova, "true" se la trova (nota: il puntatore alla testa della lista non viene modificato)

#endif
