#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream> // per i "cout" di debug e altro
#include <string> // per un campo della struct "cell" e altro
#include <sstream> // per "add_word" e altro
#include "another_list.h" // per la struct "cell"

using namespace std; // per i "cout" di debug

#define a

struct alfabeto_t 
{
	cell* alfabeto[26];
};

alfabeto_t create_dictionary(alfabeto_t); // inizializza tutti i puntatori dell' array "az.alfabeto" a "NULL" e lo restituisce
void add_word(alfabeto_t &, string); // inserisce una parola nel dizionario
void change_next_couple(alfabeto_t &, string); // fa puntare il membro "next_couple" della stringa in input alla giusta cella e se la stringa è la prima di un gruppo di stringhe che iniziano per una data coppia di caratteri, si occupa di modificare i puntatori delle celle che puntavano alla ex prima stringa del gruppo 
bool contains_word(alfabeto_t &, string); // verifica la presenza di una parola nel dizionario
void print_word_by_letter(alfabeto_t &, char); // stampa tutte le parole presenti nel dizionario che iniziano per una data lettera
void print_word_by_couple(alfabeto_t &, string); // stampa tutte le parole presenti nel dizionario che iniziano per una data coppia di lettere
int f(char); // prende in input un carattere e restituisce il numero che il carattere avrebbe nell' alfabeto se questo seguisse un ordine numerico (a=0, b=1 ecc.)

#endif
