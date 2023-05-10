//
// Created by clara on 05/05/2023.
//

#ifndef EDAII_ESTRUCTURES_H
#define EDAII_ESTRUCTURES_H
#define MAX_LENGHT 30
#define GUSTOS 5
#endif //EDAII_ESTRUCTURES_H
#include <stdlib.h>



typedef struct User{
    char sobrenom[MAX_LENGHT];
    char name[MAX_LENGHT];
    char surname[MAX_LENGHT];
    char gmail[MAX_LENGHT];
    char poblacio[MAX_LENGHT];
    int sexe;
    int edat;
    char gustos[GUSTOS][MAX_LENGHT];
};

typedef struct list_nodes{
    struct User* user;
    struct list_nodes* next;
    struct list_nodes* last;
}list_nodes;

typedef struct llista_usuaris{
    int size;
    list_nodes* first;
    list_nodes* last;
};



