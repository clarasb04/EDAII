#include <stdio.h>
#include "estructures.h"
#include "main.h"
#include "play.h"
#include "usuari.h"



void interactuar(llista_usuaris* list, User* user){
    int n;
    printf("Escull una opció: [1]. Enviar sol·licitud d'amistat \n [2]. Gestionar sol·licituds pendents \n [3]. Realitzar una publicació \n [4]. Tornar al menú principal");
    scanf("%d", &n);
    if (n == 1){
        int a;
        printf("Vols enviar una sol·licitud concreta [1] o et mostrem perfils que poden encaixar amb el vostre perfil[2]?");
        fscanf(stdin, "%d", &a);
        if (a==1){
            enviar_s_amistat(list, user);
        }
        else if (a==2){
            enviar_s_amistat_aleatoria(list, user);
        }
        else{
            printf("resposta incorrecta");
            printmenu();
        }
    }
    else if (n == 2){
        gestionar_s_pendents(user->cua_sol);
    }
    else if (n == 3){
        publ(user);
    }
    else if (n == 4){
        printmenu();
    }
    else{
        printf("Tria una opció existent");
        interactuar(list, user);
    }
}
void menu(llista_usuaris* llista, User *user){
    int n;
    n = printmenu();
    if (n==1){
        new_user(llista);
    }
    else if (n==2){
        all_users(llista);
    }
    else if (n==3){
        interactuar(llista, user);
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
    printf("Escolliu una opcio:\n [1]. Afegir usuari\n [2]. Listat d'usuaris\n [3]. Interactuar amb un usuari\n [4]. Sortir \n");
    scanf("%d", &n);
    return n;
}

int main(){
    char* nom_fitxer = "usuaris";
    llista_usuaris* llista = llegir_fitxer(nom_fitxer);

    User* user;
    menu(llista, user);
    return 1;
}
