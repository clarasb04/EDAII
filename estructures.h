

#ifndef EDAII_ESTRUCTURES_H
#define EDAII_ESTRUCTURES_H

#define MAX_LENGHT 30
#define GUSTOS 5
#include <stdlib.h>

typedef struct User{
    char sobrenom[MAX_LENGHT];
    char name[MAX_LENGHT];
    char surname[MAX_LENGHT];
    char gmail[MAX_LENGHT];
    char poblacio[MAX_LENGHT];
    char sexe;
    int edat;
    int gustos[5];
}User;



typedef struct {
    struct User* user;
    struct usuaris_llista* next;
    struct usuaris_llista* prev;
}usuaris_llista;

typedef struct{
    int size;
    usuaris_llista* first;
    usuaris_llista* last;
}llista_usuaris;


#endif //EDAII_ESTRUCTURES_H
