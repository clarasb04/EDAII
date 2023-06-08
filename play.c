#include "estructures.h"
#include "main.h"
#include "play.h"
#include "usuari.h"
#include "publcacions.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SOL 10

//GESTIÓ D'AMISTATS

// Funció per a enviar una sol·licitud d'amistat aleatòria utilitzant una pila a tres usuaris
void enviar_s_amistat_aleatoria(llista_usuaris* llista, User* user){ //comprovat
    Pila p = init_pila();
    for(int i=0; i<3; i++){
        int n = rand() % 20; // fem que es tri un número fins a 20 perquè tenim 20 usuaris
        User* u = usuari_aleatori(n, llista); // usuari corresponent a la posició aleatòria
        while (strcmp(u->sobrenom, user->sobrenom) == 0){ // codi per assegurar-nos que no apareix el mateix usuari
            n = rand() % 20;
            u = usuari_aleatori(n, llista);
        }
        push(&p, u); // posem l'usuari a la pila
    }

    printf("Les comandes son [0] no voleu enviar solicitud amistat \n[1] si voleu enviar solicitud amistat \n ");
    for(int j=0; j<3; j++){
        User* U = top(&p); //usuari al top de la pila
        mostrarusuari(U); //mostrem l'usuari
        pop(&p); //treiem l'usuari de la pila
        int a;
        scanf("%d", &a);
        while((a!=0)&&(a!=1)){
            printf("Opció incorrecta\n");
            printf("Les comandes son [S] voleu enviar amistat,\n [N] no voleu eviar amistat\n");
            scanf("%d", &a);
        }
        if (a == 1){ //en cas de vole enviar una sol·licitud
            afegir(U->cua_sol, user); // afegim l'usuari amb el qual estem tractant a la cua de sol·licituds de l'usuari de la pila
            printf("Sol.licitud enviada\n");
        }
    }
}

// Funció per a agafar usuari aleatori a partir de la posició que ocupa a la llista
User* usuari_aleatori(int num, llista_usuaris* llista){ //comprovat
    int posicio = 0;
    usuaris_llista* current = llista->first; // primer usuari de la llista
    while(current!=NULL){ //d'aquesta manera recorrem tota la llista
        if (posicio==num){ // comparem posició i num
            return current->user; // si és el cas retornem el user
        }
        current = current->next; //anem canviant l'usuari segons estiguin a la llista
        posicio++;
    }
    return NULL;
}

// Funció per a enviar una sol·licitud d'amistat a un usuari segons el seu sobrenom
void enviar_s_amistat(llista_usuaris* llista, User* user){ //comprovat
    //user és l'usuari que està enviant la sol·licitud, és a dir, amb el qual estem manejant l'aplicació
    char a[MAX_LENGHT];
    printf("Introdueix el sobrenom de la nova solicitud d'amistat que vols enviar: ");
    scanf( "%s", a);
    if (buscar(llista,a) != NULL){ // en aquest cas l'usuari existirà
        User* sol = buscar(llista,a); // sol és l'usuari al qual se li sol·licita
        afegir(sol->cua_sol,user); // afegim el user a la cua de sol
        printf("Sol.licitud enviada");

    }
    else printf("Usuari no trobat\n");
}

// Funció per a gestionar les sol·licituds d'amistats que ha rebut un usuari
void gestionar_s_pendents(User* user){ //comprovat
    int a;
    int i = user->cua_sol->head; // index per poder recórrer la cua
    if (cua_buida(user->cua_sol)){ // per saber si té sol·licituds pendents o no
        printf("No hi ha sol.licituds pendents.");
        return;
    }

    while (i <= user->cua_sol->tail){ // recorrem tots els usuaris de la cua
        printf("Si vols acceptar la sol.licitud [0], si no vols acceptar-la [1], si vols sortir [2]\n");
        mostrarusuari(user->cua_sol->u[i]); // mostrem l'usuari en aquella posició de la cua

        scanf("%d", &a);
        while((a!=0)&&(a!=1)&&(a!=2)) {
            printf("Opcio incorrecta\n");
            printf("Si vols acceptar la sol.licitud [0], si no vols acceptar-la [1], si vols sortir [2]\n");
            scanf("%d", &a);

        }
        if (a == 0) { // acceptem la sol·licitud
            afegir(user->cua_amics, user->cua_sol->u[i]); // afegim l'usuari a la cua d'amics
            treure(user->cua_sol); // treiem l'usuari de la cua de sol·licituds
            printf("Sol.licitud acceptada\n");
        } else if (a == 1) { // no acceptem la sol·licitud
            treure(user->cua_sol); // treiem l'usuari de la cua de sol·licituds sense afegir-lo a la cua d'amics
            printf("Sol.licitud denegada\n");
        } else if (a == 2) {
            return;
        }
        i = user->cua_sol->head; //augmentem la posició
    }
    printf("Ja no tens mes sol.licituds\n");
}

// Funcions bàsiques per la implementació de la CUA

// Funció per inicialitzar les dues cues, la d'amics i la de sol·licituds
void init_cua(User* user){ //comprovat
    Queue_sol* cua = malloc(sizeof (Queue_sol));
    user->cua_sol=cua;
    user->cua_sol->head = 0;
    user->cua_sol->tail = -1;
    user->cua_sol->size = 0;
    Queue_sol* cua_1 = malloc(sizeof (Queue_sol));
    user->cua_amics=cua_1;
    user->cua_amics->head= 0;
    user->cua_amics->tail= -1;
    user->cua_amics->size = 0;
}

//Funció per comprovar si la cua està buida
bool cua_buida(Queue_sol* cua){ //comprovat
    return cua->size==0;
}
//Funció per comprovar si la cua està plena
bool cua_plena(Queue_sol* cua){ //comprovat
    return cua->size>=MAX_SIZE;
}

//Funció per afegir un usuari a una cua
void afegir(Queue_sol* cua, User* u){ //comprovat
    if(cua_plena(cua)){ //comprovem que no estigui plena
        printf("Cua plena");
        return;
    }
    cua->tail=(cua->tail+1)%MAX_SIZE; // augmentem la posició de l'últim element (usuari)
    cua->u[cua->tail]=u; // assignem l'usuari a l'última posició de la cua
    cua->size++; //augmentem la mida de la cua
}

//Funció per treure un usuari de la cua
void treure(Queue_sol* cua){ //comprovat
    if (cua_buida(cua)){ //comprovem que no estigui buida
        printf("Cua buida");
        return;
    }
    cua->head = (cua->head + 1) % MAX_SIZE; // augmentem la posició del primer element (usuari), ja que una cua es basa en el sistema FIFO
    cua->size--; //disminuïm la mida de la cua
}

//USUARIS

// Funció per a buscar un usuari a partir del seu sobrenom que li entra com a paràmetre a la funció
User* buscar(llista_usuaris* llista, char* sobrenom){ //comprovat
    usuaris_llista* current = llista->first; // primer usuari de la llista
    while (current != NULL) { //d'aquesta manera recorrem tota la llista
        if (strcmp(current->user->sobrenom, sobrenom) == 0) { //si coincideix retornem el usuari corresponent
            return current->user;
        }
        current = current->next; // anem canviant d'usuari per ordre dins la llista enllaçada

    }
    return NULL;  // l'usuari no ha estat trobat
}

// Funció per a mostrar la informació d'un usuari
void mostrarusuari(User* u){ //comprovat
    printf("Sobrenom: %s, Nom: %s, Cognom: %s, Edat: %d anys\n", u->sobrenom, u->name, u->surname, u->edat);
    if(u->sexe==0) printf("Es un noi\n");
    if (u->sexe==1) printf("Es una noia\n");
    printf("Gustos: \n");
    for(int i = 0; i < 5; i++){ //fem servir un for per a recórrer l'array (hem guardat els gustos en un array de 1s i 0s)
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
        // codi per contestar a cada una de les preguntes
        if (u->gustos[i] == 0) printf("No\n");
        else if (u->gustos[i] == 1) printf("Si\n");
    }
}

// Funció per mostrar tots els usuaris de l'aplicació
void all_users(llista_usuaris* list){ //comprovat
    usuaris_llista* current = list->first; // primer usuari de la llista
    while (current != NULL) { //d'aquesta manera recorrem tota la llista
        mostrarusuari(current->user); // mostrem cada usuari
        printf("\n");
        current = current->next; // anem canviant d'usuari per ordre dins la llista enllaçada
    }
}



// Funcions bàsiques per a la implementació d'una PILA

// Funció per a inicialitzar la pila
Pila init_pila(){ //comprovat
    Pila p;
    p.top = -1;
    p.size = MAX_SIZE;
    return p;
}

// Funció per a comprovar si la pila està plena
bool is_full(Pila* p){ //comprovat
    return (p->top == p->size-1);
}

// Funció per a comprovar si la pila està buida
bool is_empty(Pila* p){ //comprovat
    return (p->top == -1);
}

// Funció per a afegir un usuari a la pila
void push(Pila* p, User* u){ //comprovat
    if (!is_full(p)){ //si no està plena el podrem afegir
        p->top = p->top + 1; // augmentem la posició top
        p->users[p->top] = u; //assignem l'usuari a aquesta posició

    }else{
        printf("Pila plena");
    }
}

// Funció per a treure un usuari de la pila
void pop(Pila* p){ //comprovat
    if (!is_empty(p)){ // si no està buida podrem treure l'usuari que està al top
        p->top = p->top - 1; // simplement s'ha de borrar la posició top i amb aquest canvi s'eliminarà l'usuari
    }
    else{
        printf("La pila està buida");
    }
}

// Funció que retorna l'usuari que està en la posició top de la pila
User* top(Pila* p){ //comprovat
    if (!is_empty(p)){ // si no està buida
        return p->users[p->top]; //retornem l'usuari
    }
    else{
        printf("Pila buida");
    }
}
