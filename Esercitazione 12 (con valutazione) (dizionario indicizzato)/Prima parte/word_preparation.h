#ifndef WORD_PREPARATION_H
#define WORD_PREPARATION_H

#include <iostream> // perchè vengono fatte delle stampe a schermo
#include <string> // per la f. "lower" ed altro
#include <sstream> // per la f. "lower" ed altro
#include <cctype> // per la f. "tolower"

using namespace std; // perche è usato "string" e altro

#define a

bool trim(string &); 
/* La f. booleana "trim":
1) se la stringa contiene solo caratteri non alfabetici, la svuota (setta la grandezza a 0) e restituisce "false"
2) se la stringa contiene caratteri alfabetici e non, elimina dalla stringa i carattari non alfabetici e restituisce "true" */
void lower(string &); // converte la stringa in input nella corrispettiva stringa minuscola

#endif
