

#ifndef EDAII_PUBLCACIONS_H
#define EDAII_PUBLCACIONS_H
#include <stdbool.h>
#include "estructures.h"

void nova_publ(User* user, struct hash_table* dict);
void crear_pub(User* user, struct hash_table* dict, char tit[MAX_LENGHT_TITOL], char cos[MAX_LENGHT_COS]);
void guardar_publ(char* filename, llista_usuaris* list);
void llegir_fitx(char* filename, llista_usuaris* list, struct hash_table* dict);
void mostrar_publ(llista_usuaris* list, User* user);
void pub_user(User* user);
void mostrar_novetats(llista_usuaris* list, User* user);


unsigned int funcio_hash(char* key);
struct node* create_node(char* key);
void add_dict(struct hash_table* dict,char* key);
void top_10(struct hash_table* dict);
void free_dict(struct hash_table* dict);

#endif //EDAII_PUBLCACIONS_H
