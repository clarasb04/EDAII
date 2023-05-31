//
// Created by clara on 31/05/2023.
//

#ifndef EDAII_PLAY_H
#define EDAII_PLAY_H

#include "estructures.h"

void enviar_s_amistat_aleatoria(llista_usuaris* llista, User* user);
void enviar_s_amistat(llista_usuaris* llista, User* user);
void gestionar_s_pendents(struct Queue_sol* cua);
struct Queue_sol* init_cua();
int cua_buida(struct Queue_sol* cua);
struct Queue_sol* afegir_sol(struct Queue_sol* cua, User* user);
struct Queue_sol* treure_sol(struct Queue_sol* cua);
User* buscar(llista_usuaris* llista, char* sobrenom);
void mostrarusuari(User* u);
void all_users(llista_usuaris* list);
void publ(User* user);
void guardar_publ(char* filename, User* user);
void mostrar_publ(char* filename);
void pub_user(char* filename, User* user);

#endif //EDAII_PLAY_H
