#ifndef EDAII_MAIN_H
#define EDAII_MAIN_H
#include <stdbool.h>

void menu(llista_usuaris* llista, User *user, struct hash_table* dict);
int printmenu();
void interactuar(llista_usuaris* list, User* user, struct hash_table* dict);
bool verificar_pin(User* u, int pin);
User* entrar(llista_usuaris* llista);
void registrar(llista_usuaris* llista);


#endif //EDAII_MAIN_H