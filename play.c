#include "estructures.h"
#include "usuari.c"
#include <stdio.h>
#include "main.h"
#include "string.h"
#define MAX_SOL 10
#define MAX_LENGHT 30

void enviar_s_amistat_aleatoria(llista_usuaris* llista, User* user){ //s'ha de canviar s'ha d'urilitzar una pila
    char a;
    printf("Les comandes son [S] voleu enviar amistat,\n [N] no voleu eviar amistat,\n [E] sortir ");
    usuaris_llista* current = llista->first;
    while (current != NULL) {
        mostrarusuari(current->user);
        fscanf(stdin, "%c", a);
        if (a =='S'){
            afegir_sol(&current->user->cua_sol, &user);
        }
        else if (a =='N'){
            current = current->next;
        }
        else if (a == 'E'){
            printmenu();
            menu();
            break;
        }
        else{
            printf("Opció incorrecta");
            printf("Les comandes son [S] voleu enviar amistat,\n [N] no voleu eviar amistat,\n [E] sortir ");
            fscanf(stdin, "%c", a);
        }
    }
}

void enviar_s_amistat(llista_usuaris* llista, User* user){ //enviar sol·licitud a un usuari concret
    //user és l'usuari que està enviant la sol·licitud
    char a[MAX_LENGHT];
    printf("Introdueix el sobrenom de la nova solicitud d'amistat que vols enviar");
    scanf( "%s", a);
    if (buscar(llista,a) != NULL){
        User* u = buscar(llista,a); //u és l'usuari al qual se li sol·licita
        afegir_sol(u->cua_sol,user);
    }
}

void gestionar_s_pendents(struct Queue_sol* cua){
    char a;
    for (int i = cua->head; i<cua->size; i++){
        printf("Si vols acceptar la sol·licitud [S] si no vols[N]");
        scanf("%c", a);
        if (a=="S") {
            //funció per afegir amic
            treure_sol(cua);
        }
        else if (a == "N"){
            treure_sol(cua);
        }

    }
}

void publicacio(){

}

//Funció per inicialitzar una cua on es posaran les sol·licituds
struct Queue_sol* init_cua(){
  struct Queue_sol* cua = (struct Queue_sol*)malloc(sizeof(struct Queue_sol));
  cua->usuer_sol = (User*) malloc(sizeof(User));
  cua->head=1;
  cua->tail=1;
  cua->size=0;
  return cua;
}
int cua_buida(struct Queue_sol* cua){
    return (cua->size == 0);
}
struct Queue_sol* afegir_sol(struct Queue_sol* cua, User* user){
    if (cua->size > MAX_SOL){
        printf("Ja hi ha un màxim de sol·licituds");
    }
    else{
        cua->usuer_sol[cua->tail] = *user;
        cua->tail = cua->tail + 1;
        if (cua->tail > MAX_SOL){
            cua->tail = 1;
        }
        cua->size = cua->size + 1;
    }
    return cua;
}

struct Queue_sol* treure_sol(struct Queue_sol* cua){
    if (cua_buida(cua)){
        printf("No hi ha sol·licituds");
    }
    else{
        cua->head = cua->head + 1;
        if (cua->head > MAX_SOL){
            cua->head = cua->head + 1;
        }
        cua->size = cua->size - 1;
    }
    return cua;
}

usuaris_llista* buscar(llista_usuaris* llista, char* sobrenom){
    usuaris_llista* current = llista->first;
    while (current != NULL) {
        if (current->user->sobrenom == sobrenom) {
            return current;
        }
        current = current->next;
    }
    return NULL;  // L'usuari no ha estat trobat
}


void mostrarusuari(User u){
    printf("%s %s %d %c", u.sobrenom, u.name, u.edat, u.sexe);

    for(int i = 0; i < 5; i++){
        if (i == 0){
            printf("Li agraden els nois: ");
        }
        else if (i == 1){
            printf("Li agraden les noies: ");
        }
        else if (i == 2){
            printf("Li importa que no sigui de la teva edat: ");
        }
        else if (i == 3){
            printf("Li agrada el futbol: ");
        }
        else if (i == 4){
            printf("Toca algun instrument: ");
        }
        if (u.gustos[i] == 0) printf("No\n");
        else if (u.gustos[i] == 1) printf("Si\n");
    }
}