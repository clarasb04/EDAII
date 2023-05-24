#include "estructures.h"
#include "usuari.c"
#include <stdio.h>
#include "main.h"
#include "string.h"
#define MAX_SOL 10

void enviar_s_amistat_aleatoria(){ //ha d'entrar la llista
    char a;
    printf("Les comandes son [S] voleu enviar amistat,\n [N] no voleu eviar amistat,\n [E] sortir ");
    fscanf(stdin, "%c", a);
    //for per anar mostrant diferents usuaris
    if (a='S'){

    }
    if (a='N'){

    }
    if (a='E'){
        return;
    }
}

void enviar_s_amistat(){ //ha d'entrar la llista de tots els usuris
    char a;
    printf("Introdueix el sobrenom de la nova solicitud d'amistat que vols enviar");
    fscanf(stdin, "%c", a);
    //cerca_usuari(,a); falta introduir la llista

}

void gestionar_s_pendents(){

}

void publicacio(){

}

struct Queue_sol* init_cua(){
  struct Queue_sol* cua = (struct Queue_sol*)malloc(sizeof(struct Queue_sol));
  cua->usuer_sol = (User*) malloc(sizeof(User));
  cua->head=1;
  cua->tail=1;
  cua->size=0;
  return cua;
}

void afegir_sol(){

}


