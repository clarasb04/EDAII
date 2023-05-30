#include "estructures.h"

#include <stdio.h>
#include "main.h"
#include "play.c"
#include "string.h"

typedef struct User;



User* new_user(llista_usuaris* list){
    User* user = (User*)malloc(sizeof(User));
    printf("Introdueix el sobrenom: ");
    scanf(" %s ", user->sobrenom);
    if(buscar(list,user->sobrenom) != NULL){
        printf("Introdueix el sobrenom: ");
        scanf(" %s ", user->sobrenom);
    }
    printf("Introdueix el nom: ");
    scanf(" %s ", user->name);
    printf("Introdueix el cognom:");
    scanf(" %s ", user->surname);
    printf("Introdueix el correu univeristat: ");
    scanf(" %s ", user->gmail);
    printf("Introdueix la població: ");
    scanf(" %s ", user->poblacio);
    printf("Introdueix el sexe (M/F): ");
    scanf(" %c ", &user->sexe);
    printf("Introdueix l'edat: ");
    scanf(" %d ", &user->edat);
    printf("Contesta a les seqüents preguntes per a saber els teus gustos: ");
    crear_gustos(&user);
    printf("PERFECTE T'HAS REGISTRAT");
    //podriem implementar un diccionari per mirar la gent que és de la mateixa població
    //falta afegir l'usuari al fitxer i a la llista
    return user;
}



void crear_gustos(User* u){
    int n;
    printf("Respon les següents preguntes per saber els teus gustos: [0] fals o [1] cert");
    printf("T'agraden els nois?");
    fscanf(stdin,"%d", n);
    u->gustos[0]=n;
    printf("T'agraden les noies?");
    fscanf(stdin,"%d", n);
    u->gustos[1]=n;
    printf("T'importa que no sigui de la teva edat?");
    fscanf(stdin,"%d", n);
    u->gustos[2]=n;
    printf("T'agrada el futbol?");
    fscanf(stdin,"%d", n);
    u->gustos[3]=n;
    printf("Toques algun instrument?");
    fscanf(stdin,"%d", n);
    u->gustos[4]=n;
}

//Funció per inicialitzar llista, s'utilitza quan baixem els usuaris del fitxer
llista_usuaris* init_list(){
    llista_usuaris* llista = (llista_usuaris*) malloc(sizeof(usuaris_llista));
    llista->size = 0;
    llista->first = NULL;
    llista->last = NULL;
    return llista;
}
// En aquesta funció s'afegueix un usuari a la llista d'usuaris
void afegir_usuaris_a_la_llista(llista_usuaris* list, User* u){
    usuaris_llista* node = (usuaris_llista*) malloc(sizeof(usuaris_llista));
    node->user = u;
    node->next = NULL;
    node->prev = NULL;

    if (list->first == NULL){
        list->first = node;
        list->last = node;
        node->prev = NULL;
    }
    else{
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }
    list->size++;
}

/* Aquesta funció no sé perquè està
void afegir_usuari(llista_usuaris* list, User* u){
    //buscar la posició corresponent
    usuaris_llista comp;
    int check=0;
    comp = *list->first;
    while(check==0){
        if(strcmp(comp.user->sobrenom, u->sobrenom)==2){
            check=1;
        }
        //comp = comp.next;
    }
}
*/

// En aquesta funció posem tots els usuaris del fitxer a una llista
llista_usuaris* llegir_fitxer(char* filename){
    FILE* f= fopen(filename, "r");
    if (f == NULL){
        printf("No s'ha pogut entrar al fitxer");
        return NULL;
    }
    llista_usuaris* llista = init_list();
    char linia_fitxer[100];
    while (fgets(linia_fitxer, sizeof(linia_fitxer),f)){
        User* user = (User*) malloc(sizeof(User));

        sscanf(linia_fitxer, "%c %s %s %s %s %c %d %d %d %d %d", &user->sobrenom, user->name, user->surname, user->gmail, user->poblacio, &user->sexe, &user->edat, &user->gustos[0], &user->gustos[1], &user->gustos[2], &user->gustos[3], &user->gustos[4]);

        afegir_usuaris_a_la_llista(llista, user);

    }
    fclose(f);
    //reservar espai i afegir l'usuari a la llista
    return llista;
}


// En aquesta funció s'omple el fitxer amb la nova llista actualitzada
void omplir_fitxer(char* filename, llista_usuaris* llista){
    FILE* fp = fopen(filename, "w");
    if (fp == NULL){
        printf("No s'ha pogut obrir el fitxer");
        return;
    }
    usuaris_llista* current = llista->first;
    while(current != NULL){
        fprintf(fp, "%c %s %s %s %s %c %d", current->user->sobrenom, current->user->name, current->user->surname, current->user->gmail, current->user->poblacio, current->user->sexe, current->user->edat);

        for (int i = 0; i < 5; i++){
            fprintf(fp, "%d", current->user->gustos[i]);
        }
        fprintf(fp, "\n");
        current = current->next;
    }
    fclose(fp);

}

