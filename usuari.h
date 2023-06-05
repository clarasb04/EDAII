#include "estructures.h"

#ifndef EDAII_USUARI_H
#define EDAII_USUARI_H

void crear_gustos(User* u);
User* new_user(llista_usuaris* list);
void afegir_usuaris_a_la_llista(llista_usuaris* list, User* u);
void llegir_fitxer(char* filename, llista_usuaris * llista);
void omplir_fitxer(char* filename, llista_usuaris* llista);
int comprovar_correu(User* user);
void bubbleSort(llista_usuaris* llista);

#endif //EDAII_USUARI_H
