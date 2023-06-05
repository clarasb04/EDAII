#include <stdio.h>
#include "estructures.h"
#include "main.h"
#include "play.h"
#include "usuari.h"
#include "publcacions.h"
#include <stdbool.h>
#include <string.h>
#define MAX_LENGHT 50

void interactuar(llista_usuaris* list, User* user, struct hash_table* dict, char* f_publ){
    int n;
    printf("Escull una opcio: \n [1]. Enviar sol.licitud d'amistat \n [2]. Gestionar sol.licituds pendents \n [3]. Gestionar publicacions \n [4]. Tornar al menu principal\n");
    scanf("%d", &n);
    if (n == 1){
        int a;
        printf("\nVols enviar una sol.licitud concreta [1] o et mostrem perfils aleatoris que poden encaixar amb el vostre perfil[2]?\n");
        scanf("%d", &a);
        if (a==1){
            enviar_s_amistat(list, user);
        }
        else if (a==2){
            enviar_s_amistat_aleatoria(list, user);
        }
        else{
            printf("Resposta incorrecta");
            printmenu();
        }
    }
    else if (n == 2){
        gestionar_s_pendents(user, user->cua_sol->u);

    }
    else if (n == 3){
        int c;

        printf("[1] Vols crear una publiacio,\n [2]mirar totes les publiacions o\n [3]mirar les publicacions d'un uaruari? \n");
        scanf("%d", &c);
        if (c==1){
            publ(user, dict);
        }
        else if (c==2){
            mostrar_publ(f_publ);
        }
        else if (c==3) {
            char sobrenom[MAX_LENGHT];
            printf("introdueix el sobrenom de l'usurai que vols observar les publicacions: \n");
            scanf("%s", sobrenom);
            User* u = buscar(list, sobrenom);
            while (u==NULL){
                printf("aquest usuari no existeix \n");
                printf("introdueix el sobrenom de l'usurai que vols observar les publicacions: \n");
                scanf("%s", sobrenom);
                u = buscar(list, sobrenom);
            }
            pub_user(f_publ, u);
        }
    }
    else if (n == 4){
        printmenu();
    }
    else{
        printf("Tria una opcio existent");
        interactuar(list, user, dict, f_publ);
    }
}

void menu(llista_usuaris* llista, User* user, struct hash_table* dict, char* f_publ){
    int n;
    printf("\n_____________________\n");
    n = printmenu();
    if (n==1){
        all_users(llista);
        menu(llista, user, dict, f_publ);
    }
    else if (n==2){
        interactuar(llista, user, dict, f_publ);
        menu(llista, user, dict, f_publ);
    }
    else if (n==3){
        printf("Has sortit");
    }
    else{
        printf("L'opcio escollida no exisiteix. Intenta-ho de nou.");
        printmenu();
    }
}
int printmenu(){
    int n;
    printf("Escolliu una opcio:\n [1]. Listat d'usuaris\n [2]. Interactuar amb un usuari\n [3]. Sortir \n");
    scanf("%d", &n);
    return n;
}

bool verificar_pin(User* u, int pin){ //revisada
    FILE* f = fopen("pins", "r");
    if (f == NULL){
        printf("No s'ha pogut obrir");
        return false;
    }
    char sobrenom[MAX_LENGHT];
    int contra;
    while (fscanf(f, "%s %d", sobrenom, &contra) == 2){
        if ((pin == contra) && (strcmp(u->sobrenom, sobrenom)==0)){
            fclose(f);
            return true;
        }
    }
    fclose(f);
    return false;
}

void registrar(llista_usuaris* llista){ //revisada
    FILE* f = fopen("pins", "a+");
    if (f == NULL){
        printf("No s'ha pogut obrir");
        return;
    }
    printf("intodueix un sobrenom:\n");
    char s[MAX_LENGHT];
    User* u;
    scanf("%s", s);
    u=buscar(llista, s);
    while (u!=NULL){
        printf("sobrenom existen, prova un altre\n");
        scanf("%s", s);
        u=buscar(llista, s);

    }
    printf("introduiu un pin de 4 xifres\n");
    int a;
    scanf("%d", &a);
    fprintf(f,"%s %d\n", s, a);
    fclose(f);
}

User* entrar(llista_usuaris* llista) { //revisada
    int n;
    printf("[1]Iniciar sessio\n [2] registrat \n");
    scanf("%d", &n);
    while ((n != 1) && (n != 2)) {
        printf("[1]Iniciar sessio\n [2] registrat ");
        scanf("%d", &n);
    }
    if (n == 1) {
        printf("Introdueix el sobrenom:\n");
        char sobrenom[MAX_LENGHT];
        User *u;
        scanf("%s", sobrenom);
        if (buscar(llista, sobrenom) != NULL){
            u = buscar(llista, sobrenom);
            printf("Introdueix la contrasenya, solament numeros i sense espais:\n");
            int pin;
            int intents = 0;
            scanf("%d", &pin);
            while ((verificar_pin(u, pin) == false) && (intents<3)){
                printf("Contrasenya incorrecta, tens %d intents\n", 3-intents);
                scanf("%d", &pin);
                intents++;
            }
            if (intents >= 3){
                printf("S'han acabat els intents\n");
                entrar(llista);
            }
            return u;
        }
        else{
            printf("No es pot iniciar sessio, ja que aquest usuari no existeix\n");
            entrar(llista);
        }
    } else {
        registrar(llista);
        printf("Introdueix totes les dades del nou ususri\n");
        return new_user(llista);
    }
}


int main(){
    char* nom_fitxer = "usuaris";
    //incialitzacio llista
    llista_usuaris llista;
    llista.size =0;
    llista.first = NULL;
    llista.last = NULL;
    llegir_fitxer(nom_fitxer, &llista);
    //incialitzacio dicionari
    struct hash_table* dict = (struct hash_table*)malloc(sizeof(struct hash_table));
    dict->size=CAPACITY;
    //dict->array=(node**)calloc(dict->size, sizeof(node*));
    for (int i = 0; i<dict->size; i++) {
        dict->array[i] = NULL;
    }
    //iniciar sessió o resgitrar-se
    User* usuariprincipal = entrar(&llista);

    char* fitxer = "publicacions";
    menu(&llista, usuariprincipal, dict, fitxer);
    omplir_fitxer(nom_fitxer, &llista);
    return 1;
}
