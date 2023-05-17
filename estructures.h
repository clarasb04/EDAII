//
// Created by clara on 05/05/2023.
//

#ifndef EDAII_ESTRUCTURES_H
#define EDAII_ESTRUCTURES_H
#define MAX_LENGHT 30
#define GUSTOS 5
#endif //EDAII_ESTRUCTURES_H
#include <stdlib.h>



typedef struct{
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
    struct list_nodes* next;
    struct list_nodes* prev;
}usuaris_llista;

typedef struct{
    int size;
    usuaris_llista* first;
    usuaris_llista* last;
}llista_usuaris;



