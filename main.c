#include <stdio.h>
#include "estructures.h"
#include "main.h"
#include "string.h"


void new_user(){
    int edat, MAX=30, a;
    char nom[MAX], cog[MAX], sobrenom[MAX], mail[MAX], poblacio[MAX], gust[MAX], sexe;
    printf("Introdueix les següents dades separades en espais: \nnom cognom sobrenom gmail població edat sexe(M/F/A)");
    a = fscanf(stdin,"%s %s %s %s %s %d %c", nom, cog, sobrenom, mail, poblacio, edat, sexe);
    if (a!=7){
        printf("No has introduit correctament les dades, usuari no creat");
        return;
    } else{
        struct User provnou;
        strcpy(provnou.sobrenom, sobrenom);
        strcpy(provnou.name, nom);
        strcpy(provnou.surname, cog);
        strcpy(provnou.gmail, mail);
        strcpy(provnou.gustos, gust);
        strcpy(provnou.poblacio, poblacio);
        provnou.edat = edat;
        provnou.sexe = sexe;
        //crear usuari
    }
     //podriem implementar un diccionari per mirar la gent q és de la mateixa població
}

void interactuar(){
    int n;
    printf("Escull una opció: [1]. Enviar sol·licitud d'amistat \n [2]. Gestionar sol·licituds pendents \n [3]. Realitzar una publicació \n [4]. Tornar al menú principal");
    fscanf(stdin,"%d", n);
    if (n == 1){
        enviar_s_amistat();
    }
    else if (n == 2){
        gestionar_s_pendents();
    }
    else if (n == 3){
        publicacio();
    }
    else if (n == 4){
        printmenu();
    }
    else{
        printf("Tria una opció existent");
        interactuar();
    }
}
void menu(){
    int n;
    n = printmenu();
    if (n==1){
        new_user();
    }
    else if (n==2){
        all_users();
    }
    else if (n==3){
        interactuar();
    }
    else if (n==4){
       printf("Has sortit");
    }
    else{
        printf("L'opció escollida no exisiteix. Intenta-ho de nou.");
        printmenu();
    }
}
int printmenu(){
    int n;
    printf("Escolliu una opcio:\n [1]. Afegir usuari\n [2]. Listat d'usuaris\n [3]. Interactuar amb un usuari\n [4]. Sortir");
    fscanf(stdin,"%d", n);
    return n;
}
void crearllista(){
           //crear la llista dinamica per anar afegint els usuaris
    FILE* f= fopen("usuaris", "r");
    int res, edat, sex, cont;
    char sob[MAX_LENGHT], nom[MAX_LENGHT], surn[MAX_LENGHT], gmail[MAX_LENGHT], pob[MAX_LENGHT], gust[GUSTOS][MAX_LENGHT];
    res = fscanf(f, "%s %s %s %s %s %d %d %s", sob, nom, surn, gmail, pob, sex, edat, gust); //problema en detectar gustos
    while(res==8){
        struct User usuariprov;
        strcpy(usuariprov.sobrenom, sob);
        strcpy(usuariprov.name, nom);
        strcpy(usuariprov.surname, surn);
        strcpy(usuariprov.gmail, gmail);
        strcpy(usuariprov.gustos, gust);
        strcpy(usuariprov.poblacio, pob);
        usuariprov.edat = edat;
        usuariprov.sexe = sex;
        //reservar espai i afegir l'usuari a la llista
        res = fscanf(f, "%s %s %s %s %s %d %d %s", sob, nom, surn, gmail, pob, sex, edat, gust);
    }
}
int main() {
    printf("hola !\n");
    menu();
    return 0;

}
