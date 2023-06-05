#include "estructures.h"
#include "main.h"
#include "play.h"
#include "usuari.h"
#include "publcacions.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SOL 10

#define MAX_SIZE 10

void enviar_s_amistat_aleatoria(llista_usuaris* llista, User* user){
    Pila p=init_pila();
    for(int i=0; i<3; i++){
        int n = rand() % 20;
        User* u = usuari_aleatori(n, llista);
        push(p, u);
    }

    printf("Les comandes son [0] no voleu enviar amistat,\n [1] si voleu eviar amistat\n ");
    for(int j=0; j<3; j++){
        User* U = top(p); //imprimeix mal els usuaris
        mostrarusuari(U);
        pop(p);
        int a;
        scanf("%d", &a);
        while((a!=0)&&(a!=1)){
            printf("Opció incorrecta\n");
            printf("Les comandes son [S] voleu enviar amistat,\n [N] no voleu eviar amistat\n");
            scanf("%d", &a);
        }
        if (a == 1){
            afegir_sol(user, U);
        }
    }
}
User* usuari_aleatori(int num, llista_usuaris* llista){
    int posicio=0;
    usuaris_llista* node_actual = llista->first;
    while(node_actual!=NULL){
        if (posicio==num){
            return node_actual->user;
        }
        node_actual=node_actual->next;
        posicio++;
    }
    return NULL;
}

void enviar_s_amistat(llista_usuaris* llista, User* user){ //enviar sol·licitud a un usuari concret
    //user és l'usuari que està enviant la sol·licitud
    char a[MAX_LENGHT];
    printf("Introdueix el sobrenom de la nova solicitud d'amistat que vols enviar: ");
    scanf( "%s", a);
    if (buscar(llista,a) != NULL){
        User* sol = buscar(llista,a); //u és l'usuari al qual se li sol·licita
        afegir_sol(user,sol);
        printf("Hola");
    }
    else printf("Usuari no trobat\n");
}

void gestionar_s_pendents(User* user, User* sol){
    char a;
    int i = user->cua_sol->head;

    if (cua_buida(user->cua_sol)){
        printf("No hi ha sol.licituds pendents.");
        return;
    }
    while (i < user->cua_sol->tail){
        printf("Si vols acceptar la sol.licitud [S], si no vols acceptar-la [N], si vols sortir [E]");
        scanf("%c", &a);

        if (a =='S') {
            //afegir_amic(user, sol);
            treure_sol(user);
        }
        else if (a == 'N'){
            treure_sol(user);
        }
        else if (a == 'E'){
            printf("Opcio incorrecta.");
        }
        else{
            break;
        }

        i = (i + 1) % user->cua_sol->size;
    }
    //Processem l'última sol·licitud
    if (a =='S') {
        //afegir_amic(user->cua_amics, cua[i].user_sol);
        treure_sol(user);
    }
    else if (a == 'N'){
        treure_sol(user);
    }
    else if (a == 'E'){
        printf("Opcio incorrecta.");
    }
}

void afegir_sol(User* user, User* sol){
    printf("Adeu");
    if ((user->cua_sol->tail + 1) % user->cua_sol->size == user->cua_sol->head){
        printf("La cua de sol·licituds està plena.\n");
        return;
    }
    int new_tail = (user->cua_sol->tail + 1) % user->cua_sol->size;

    user->cua_sol->u[user->cua_sol->tail] = *sol;
    user->cua_sol->tail = new_tail;
    printf("Sol·licitud afegida a la cua de sol·licituds.\n");
}

//Funció per inicialitzar una cua on es posaran les sol·licituds
void init_cua(User* user){
    user->cua_sol = (Queue_sol*)malloc(sizeof(Queue_sol));
    user->cua_sol->u = NULL;
    user->cua_sol->head = -1;
    user->cua_sol->tail = -1;
    user->cua_sol->size = MAX_SOL;
    user->cua_amics=(Queue_sol*)malloc(sizeof(Queue_sol));
    user->cua_amics->u = NULL;
    user->cua_amics->head=-1;
    user->cua_amics->tail=-1;
    user->cua_amics->size = MAX_SOL;
}
int cua_buida(struct Queue_sol* cua){
    return (cua->size == 0);
}


struct Queue_sol* treure_sol(User* u){
    if (cua_buida(u->cua_sol)){
        printf("No hi ha sol·licituds");
    }
    else{
        u->cua_sol->head = u->cua_sol->head + 1;
        if (u->cua_sol->head > MAX_SOL){
            u->cua_sol->head = 0;
        }
        u->cua_sol->size = u->cua_sol->size - 1;
    }
    return u->cua_sol;
}

struct Queue_sol* afegir_amic(struct Queue_sol* cua, User* user){
    if (cua->size > MAX_SOL){
        printf("Ja te un maxim d'amics");
    }
    else{
        //cua->user_sol[cua->tail] = *user;
        cua->tail = cua->tail + 1;
        if (cua->tail > MAX_SOL){
            cua->tail = 1;
        }
        cua->size = cua->size + 1;
    }
    return cua;
}

User* buscar(llista_usuaris* llista, char* sobrenom){ //comprovat
    usuaris_llista* current = llista->first;
    while (current != NULL) {
        if (strcmp(current->user->sobrenom, sobrenom) == 0) {
            return current->user;
        }
        current = current->next;

    }
    return NULL;  // L'usuari no ha estat trobat
}


void mostrarusuari(User* u){ //comprovat
    printf("%s, %s %s, %d anys\n", u->sobrenom, u->name, u->surname, u->edat);
    if(u->sexe==0) printf("es un noi\n");
    if (u->sexe==1) printf("es una noia\n");
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
        if (u->gustos[i] == 0) printf("No\n");
        else if (u->gustos[i] == 1) printf("Si\n");
    }
}
void all_users(llista_usuaris* list){ //comprovat
    usuaris_llista* current = list->first;
    while (current != NULL) {
        mostrarusuari(current->user);
        current = current->next;
    }
}



//PILA

Pila init_pila(){
    Pila p;
    p.top = -1;
    p.size=MAX_SIZE;
    p.users= malloc(MAX_SIZE*sizeof(User));
    return p;
}

bool is_full(Pila p){
    return (p.top == MAX_SIZE);
}

bool is_empty(Pila p){
    return (p.top == 0);
}

Pila push(Pila p, User* u){
    if (!is_full(p)){
        p.top = p.top + 1;
        p.users[p.top] = *u;
    }else{
        printf("Pila plena");
    }
    return p;
}

Pila pop(Pila p){
    if (!is_empty(p)){
        p.top = p.top - 1;
    }
    else{
        printf("La pila està buida");
    }
    return p;
}

User* top(Pila p){
    if (!is_empty(p)){
        return &p.users[p.top];
    }
    else{
        printf("Pila buida");
    }
}
