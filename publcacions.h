

#ifndef EDAII_PUBLCACIONS_H
#define EDAII_PUBLCACIONS_H
#include <stdbool.h>
#include "estructures.h"

void publ(User* user, struct hash_table* dict);
void guardar_publ(char* filename, User* user);
void mostrar_publ(char* filename);
void pub_user(char* filename, User* user);


unsigned int hash_function(char* key);
struct node* create_node(char* key);
void add_dict(struct hash_table* dict,char* key);
void top_10(struct hash_table* dict);
void free_dict(struct hash_table* dict);

#endif //EDAII_PUBLCACIONS_H
