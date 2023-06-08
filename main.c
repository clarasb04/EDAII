#include <stdio.h>
#include "estructures.h"
#include "main.h"
#include "play.h"
#include "usuari.h"
#include "publcacions.h"
#include <stdbool.h>
#include <string.h>
#define MAX_LENGHT 50

void interactuar(llista_usuaris* list, User* user, struct hash_table* dict){
    int n;
    printf("Escull una opcio: \n [1]. Enviar sol.licitud d'amistat \n [2]. Gestionar sol.licituds pendents \n [3]. Gestionar publicacions \n [4]. Mostrar amistats \n [5]. Tornar al menu principal\n");
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
        gestionar_s_pendents(user);
    }
    else if (n == 3){
        int c;
        printf("Gestionar publicacions: \n");
        printf(" [1] Vols crear una publiacio \n [2] Mirar les publicacions des tres usuaris aleatoris  \n [3] Mirar totes les publiacions d'un usuari \n [4] Mostar les publicacions mes recents (NEW) \n [5] Mostrar els 10 temes mes parlats \n ");
        scanf("%d", &c);
        if (c==1){
            nova_publ(user, dict);
        }

        else if (c==2){
            mostrar_publ(list, user);
        }

        else if (c==3) {
            char sobrenom[MAX_LENGHT];
            printf("Introdueix el sobrenom de l'usuari que vols observar les publicacions: \n");
            scanf("%s", sobrenom);
            User* u = buscar(list, sobrenom);
            while (u==NULL){
                printf("Aquest usuari no existeix \n");
                printf("Introdueix el sobrenom de l'usuari que vols observar les publicacions: \n");
                scanf("%s", sobrenom);
                u = buscar(list, sobrenom);
            }
            pub_user (u);
        }
        else if (c==4){
            mostrar_novetats(list, user);
        }
        else if (c==5){
            top_10(dict);
        }
        else{
            printf("Resposta incorrecta");
            printmenu();
        }
    }
    else if (n == 4){
        imprimir_amics(user);
    }
    else if (n == 5){
        printmenu();
    }
    else{
        printf("Tria una opcio existent \n");
        interactuar(list, user, dict);
    }
}

// Funció principal per a poder accedir a les diverses opcions de la xarxa
void menu(llista_usuaris* llista, User* user, struct hash_table* dict) {
    int n;
    printf("\n_____________________\n");
    n = printmenu(); //retorna l'opció a la qual volem accedir
    if (n == 1) {
        all_users(llista);
        menu(llista, user, dict);
    } else if (n == 2) {
        interactuar(llista, user, dict);
        menu(llista, user, dict);
    } else if (n == 3) {
        User* usuariprincipal = entrar(llista);
        menu(llista, usuariprincipal, dict);
    } else if (n == 4){
        printf("Has sortit");
    }
    else{
        printf("L'opcio escollida no exisiteix. Intenta-ho de nou.");
        printmenu();
    }
}
// funció per imprimir les opcions del menú
int printmenu(){
    int n;
    printf("Escolliu una opcio:\n [1]. Listat d'usuaris\n [2]. Interactuar\n [3]. Tancar sessio i entrar amb un altre usuari\n [4]. Sortir \n");
    scanf("%d", &n);
    return n;
}

// Aquesta funció serveix per a comprovar si el pin introduït en iniciar sessió és correcte
bool verificar_pin(User* u, int pin){ //revisada
    FILE* f = fopen("pins", "r"); //obrim el fitxer amb els sobrenoms i els seus pins corresponents
    if (f == NULL){ //en aquest cas no s'haurà pogut entrar al fitxer
        printf("No s'ha pogut obrir");
        return false;
    }
    char sobrenom[MAX_LENGHT];
    int contra;
    while (fscanf(f, "%s %d", sobrenom, &contra) == 2){ //agafem el sobrenom i el seu pin llegint la fila
        //comparem el sobrenom de l'usuari amb el sobrenom de la fila llegida
        //comparem el pin (paràmetre) amb el pin/contrasenya llegit del fitxer
        if ((pin == contra) && (strcmp(u->sobrenom, sobrenom)==0)){ //si els dos coincideixen retornem true
            fclose(f); //tanquem el fitxer
            return true;
        }
        // si no coincideixen anirem llegint totes les files una a una mentre obtinguem dos matches (sobrenom i contra) al fitxer
    }
    fclose(f); //tanquem el fitxer
    return false;
}

// Aquesta funció serveix per a registrar nous usuaris a la xarxa
void registrar(llista_usuaris* llista){ //revisada
    FILE* f = fopen("pins", "a+"); // hem d'obrir el fitxer on guardarem el sobrenom i la contrasenya en format a+
    if (f == NULL){
        printf("No s'ha pogut obrir");
        return;
    }
    printf("Intodueix un sobrenom:\n");
    char s[MAX_LENGHT];
    User* u;
    scanf("%s", s);
    u=buscar(llista, s); // guardem a u l'usuari que correspon al sobrenom introduït per pantalla
    while (u!=NULL){ // mentre sigui diferent de NULL voldrà dir que aquell sobrenom ja està utilitzat
        printf("Sobrenom existent, prova un altre\n");
        scanf("%s", s);
        u=buscar(llista, s); //per tant, es demanarà que s'introdueixi un altre sobrenom fins està disponible

    }
    printf("Introduiu un pin de 4 xifres\n"); //demanem el pin
    int a;
    scanf("%d", &a);
    fprintf(f,"%s %d\n", s, a);
    fclose(f);
}

// Funció per entrar a l'aplicació, retrorna l'usuari amb el qual utilitzarem la xarxa
User* entrar(llista_usuaris* llista) { //revisada
    printf(" ----------\n | UPloFe | \n ----------\n Benvinguts a l'aplicacio on trobareu l'amor a la UPF \n");
    int n;
    printf("[1]Iniciar sessio \n[2]Registrat \n");
    scanf("%d", &n);
    while ((n != 1) && (n != 2)) { // Mentre no sigui ni 1 ni 2 el valor introduït
        printf("[1]Iniciar sessio \n[2] Registrat \n");
        scanf("%d", &n);
    }
    if (n == 1) { //en aquest cas iniciem sessió
        printf("Introdueix el sobrenom:\n");
        char sobrenom[MAX_LENGHT];
        User *u;
        scanf("%s", sobrenom);
        if (buscar(llista, sobrenom) != NULL){ //es comprova que existeix un usuari amb el sobrenom corresponent
            u = buscar(llista, sobrenom); //assignem l'usuari al sobrenom corresponent
            printf("Introdueix la contrasenya, solament numeros i sense espais:\n");
            int pin;
            int intents = 0;
            scanf("%d", &pin);
            while ((verificar_pin(u, pin) == false) && (intents<3)){ //verifiquem que el pin introduït sigui l'adequat
                printf("Contrasenya incorrecta, tens %d intents\n", 3-intents);
                scanf("%d", &pin);
                intents++;
            }
            if (intents >= 3){ // si arribem aquí és perquè hem arribat al màxim d'intents
                printf("S'han acabat els intents\n");
                entrar(llista); // es crida a ella mateixa per tornar a entrar a l'aplicació
            }
            return u;
        }
        else{ //en aquest cas el sobrenom introduït no corresponia al de cap usuari registrat prèviament
            printf("No es pot iniciar sessio, ja que aquest usuari no existeix\n");
            entrar(llista); // es crida a ella mateixa per tornar a entrar a l'aplicació
        }
    } else {
        registrar(llista); //registrem l'usuari (sobrenom i pin)
        printf("Introdueix totes les dades del nou ususri\n");
        return new_user(llista); //emplenem les dades i retornem el usuari
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
    for (int i = 0; i<dict->size; i++) {
        dict->array[i] = NULL;
    }
    //iniciar sessió o resgitrar-se
    User* usuariprincipal = entrar(&llista);
    char* fitxer_publ = "publicacions";
    llegir_fitx(fitxer_publ, &llista, dict);
    menu(&llista, usuariprincipal, dict);
    guardar_publ(fitxer_publ, &llista);
    free_dict(dict);
    omplir_fitxer(nom_fitxer, &llista);
    return 1;
}
