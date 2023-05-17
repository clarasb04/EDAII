#include "estructures.h"

#include <stdio.h>
#include "main.h"
#include "string.h"

void new_user(){
    int edat, a;
    char nom[MAX_LENGHT], cog[MAX_LENGHT], sobrenom[MAX_LENGHT], mail[MAX_LENGHT], poblacio[MAX_LENGHT], sexe;
    printf("Introdueix les següents dades separades en espais: \nnom cognom sobrenom gmail població edat sexe(M/F/A)");
    a = fscanf(stdin,"%s %s %s %s %s %d %c", nom, cog, sobrenom, mail, poblacio, edat, sexe);
    if (a!=7){
        printf("No has introduit correctament les dades, usuari no creat");
        return;
    } else{
        user provnou;
        strcpy(provnou.sobrenom, sobrenom);
        strcpy(provnou.name, nom);
        strcpy(provnou.surname, cog);
        strcpy(provnou.gmail, mail);
        strcpy(provnou.poblacio, poblacio);
        provnou.edat = edat;
        provnou.sexe = sexe;
        crear_gustos(provnou);
    }
    //podriem implementar un diccionari per mirar la gent q és de la mateixa població
    //falta afegir l usuari al fitxer i a la llista
}

void afegir_usuaris_a_la_llista(user* u, user* list){
    if (list == NULL){

    }


}


void crear_gustos(user* u){ //que retornem?
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


void crearllista(){
    user* list = (struct User*) malloc(sizeof(user));
    FILE* f= fopen("usuaris", "r");
    int res, edat, sex, gust1, gust2, gust3, gust4, gust5, cont=0;
    char sob[MAX_LENGHT], nom[MAX_LENGHT], surn[MAX_LENGHT], gmail[MAX_LENGHT], pob[MAX_LENGHT];
    res = fscanf(f, "%s %s %s %s %s %d %d %d %d %d %d %", sob, nom, surn, gmail, pob, sex, edat, &gust1, &gust2, &gust3, &gust4, &gust5); //problema en detectar gustos
    while(res==12){
        user usuariprov;
        strcpy(usuariprov.sobrenom, sob);
        strcpy(usuariprov.name, nom);
        strcpy(usuariprov.surname, surn);
        strcpy(usuariprov.gmail, gmail);
        strcpy(usuariprov.poblacio, pob);
        //usuariprov.gustos afegir gustos
        usuariprov.edat = edat;
        usuariprov.sexe = sex;
        //reservar espai i afegir l'usuari a la llista
        list = (struct User*) realloc(list, (cont+1)*sizeof(struct User*));
        list[cont] = usuariprov;
        cont++;
        res = fscanf(f, "%s %s %s %s %s %d %d %d %d %d %d %", sob, nom, surn, gmail, pob, sex, edat, &gust1, &gust2, &gust3, &gust4, &gust5);
    }
}

