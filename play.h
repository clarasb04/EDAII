//
// Created by clara on 31/05/2023.
//

#ifndef EDAII_PLAY_H
#define EDAII_PLAY_H
#include <stdbool.h>
#include "estructures.h"

void enviar_s_amistat_aleatoria(llista_usuaris* llista, User* user);
User* usuari_aleatori(int num, llista_usuaris* llista);
void enviar_s_amistat(llista_usuaris* llista, User* user);
void gestionar_s_pendents(User* user, User* sol);
void init_cua(User* user);
int cua_buida(struct Queue_sol* cua);
void afegir_sol(User* user, User* sol);
struct Queue_sol* treure_sol(User* u);
struct Queue_sol* afegir_amic(struct Queue_sol* cua, User* user);

User* buscar(llista_usuaris* llista, char* sobrenom);
void mostrarusuari(User* u);
void all_users(llista_usuaris* list);

Pila init_pila();
bool is_full(Pila p);
bool is_empty(Pila p);
Pila push(Pila p, User* u);
Pila pop(Pila p);
User* top(Pila p);

#endif //EDAII_PLAY_H
