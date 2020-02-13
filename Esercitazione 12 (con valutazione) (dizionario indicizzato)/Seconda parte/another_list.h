#ifndef ANOTHER_LIST_H
#define ANOTHER_LIST_H

#include <iostream> // per le stampe a schermo e altro
#include <string> // per la f. "add_word" e altro
#include <sstream> // per la f. "change_next_couple"

using namespace std; // perchè è usato "string" e altro

#define a

struct cell
{
	string info;
	cell* next;
	cell* next_couple;
};

cell* create_list(); // restituisce un puntatore a "NULL" (ovvero una lista vuota)
void add_word(cell* &, string); // inserisce la stringa in input nella lista in input, a meno che la stringa non sia già presente (nota: il puntatore alla testa della lista non viene modificato)
void change_next_couple(cell*, string); // si occupa di far puntare "next_couple" della stringa "s" in input alla cella contenente la stringha che inizia per la coppia di caratteri maggiore secondo l' ordine lessicografico. Inoltre, se "s" è la prima stringa di un gruppo che inizia per una data coppia di caratteri, si occupa di cambiare i membri "next_couple" che puntano alla ex prima stringa del gruppo (nota:questa f. presuppone che "s" sia già stata inserita nella lista) 
bool contains_word(cell*, string); // cerca la stringa in input nella lista in input e restituisce "false" se non la trova, "true" se la trova (nota: il puntatore alla testa della lista non viene modificato)

#endif
