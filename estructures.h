

#ifndef EDAII_ESTRUCTURES_H
#define EDAII_ESTRUCTURES_H

#define MAX_LENGHT 50
#define MAX_LENGHT_TITOL 20
#define MAX_LENGHT_COS 120
#define GUSTOS 5
#define CAPACITY 100
#define MAX_SIZE 10

#include <stdlib.h>

typedef struct User{
    char sobrenom[MAX_LENGHT];
    char name[MAX_LENGHT];
    char surname[MAX_LENGHT];
    char gmail[MAX_LENGHT];
    char poblacio[MAX_LENGHT];
    int sexe;
    int edat;
    int gustos[GUSTOS];
    struct Queue_sol* cua_sol;
    struct Queue_sol* cua_amics;
    struct publicacio* pub[5];
    int num_pub;
}User;

//estructures per tots els usuaris de l'aplicació

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

//estructura cua (sol·licituds d'amistats)
typedef struct Queue_sol{
    User* u[MAX_SIZE];
    int head;
    int tail;
    int size;
}Queue_sol;

//estructura publicacions
struct publicacio{
    char titol[MAX_LENGHT_TITOL];
    char cos[MAX_LENGHT_COS];
};
typedef struct Pila{
    int top;
    int size;
    User* users[MAX_SIZE];
}Pila;

//estructura diccionari
typedef struct node{
    struct node* next;
    char key[MAX_LENGHT_TITOL];
    int count;
}node;

struct hash_table{
    struct node* array[CAPACITY]; //mida dicionari
    int size;
};

#endif //EDAII_ESTRUCTURES_H
