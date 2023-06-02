

#ifndef EDAII_ESTRUCTURES_H
#define EDAII_ESTRUCTURES_H

#define MAX_LENGHT 30
#define MAX_LENGHT_TITOL 20
#define MAX_LENGHT_COS 120
#define GUSTOS 5
#include <stdlib.h>

typedef struct User{
    char sobrenom[MAX_LENGHT];
    char name[MAX_LENGHT];
    char surname[MAX_LENGHT];
    char gmail[MAX_LENGHT];
    char poblacio[MAX_LENGHT];
    char sexe[1];
    int edat;
    int gustos[5];
    struct Queue_sol* cua_sol;
    struct publicacio* pub;
}User;

//estructures per tots els usuaris de l'aplicacio

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

//estructura solisituds d'amistats
struct Queue_sol{
    User* usuer_sol;
    int head;
    int tail;
    int size;
};

//estructura publicacions
struct publicacio{
    char titol[MAX_LENGHT_TITOL];
    char cos[MAX_LENGHT_COS];
    User* publicador;
    int num;
};
typedef struct Pila{
    int top;
    User* user;
}Pila;

#endif //EDAII_ESTRUCTURES_H
