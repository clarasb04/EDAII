#include "estructures.h"

#ifndef EDAII_USUARI_H
#define EDAII_USUARI_H

void crear_gustos(User* u);
User* new_user(llista_usuaris* list);
llista_usuaris* init_list();
void afegir_usuaris_a_la_llista(llista_usuaris* list, User* u);
llista_usuaris* llegir_fitxer(char* filename);
void omplir_fitxer(char* filename, llista_usuaris* llista);
int comprovar_correu(User* user);


#endif //EDAII_USUARI_H
