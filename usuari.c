#include "estructures.h"
#include "main.h"
#include "play.h"
#include "usuari.h"
#include "publcacions.h"
#include <stdio.h>
#include "string.h"
#include <stdbool.h>

// Funció per a introduir els gustos d'un usuari, tractarem els gustos com un array de 0s i 1s
void crear_gustos(User* u){   //revisada
    int n;
    printf("Respon les seguents preguntes per saber els teus gustos: [0] fals o [1] cert\n");
    printf("T'agraden els nois?\n");
    scanf("%d", &n);
    u->gustos[0]=n;
    printf("T'agraden les noies?\n");
    scanf("%d", &n);
    u->gustos[1]=n;
    printf("T'importa que no sigui de la teva edat?\n");
    scanf("%d", &n);
    u->gustos[2]=n;
    printf("T'agrada el futbol?\n");
    scanf("%d", &n);
    u->gustos[3]=n;
    printf("Toques algun instrument?\n");
    scanf("%d", &n);
    u->gustos[4]=n;
}

// Funció per a introduir les dades d'un usuari
User* new_user(llista_usuaris* list){ //revisada
    User* user = (User*)malloc(sizeof(User)); // inicialitzem un array dinàmica per a un usuari
    printf("Introdueix el sobrenom: \n");
    scanf("%s", user->sobrenom);
    while (buscar(list,user->sobrenom) != NULL){ //comprovem que no existeixi un usuari amb el sobrenom introduït
        printf("Sobrenom ja utilitzat, introdueix el sobrenom: \n");
        scanf("%s", user->sobrenom);
    }
    printf("Introdueix el nom: ");
    scanf("%s", user->name);
    printf("Introdueix el cognom: ");
    scanf("%s", user->surname);
    printf("Introdueix el correu de la universitat: ");
    scanf("%s", user->gmail);
    while(!comprovar_correu(user)){ // comprovem que el gmail introduït sigui un correu de la UPF
        printf("El correu introduit no es valid");
        scanf("%s", user->gmail);
    }
    printf("Introdueix la poblacio: ");
    scanf("%s", user->poblacio);
    printf("Introdueix el sexe M(0) o F(1): ");
    scanf("%d", &user->sexe);
    printf("Introdueix l'edat: ");
    scanf("%d", &user->edat);
    crear_gustos(user); // cridem a la funció gustos per introduir els gustos
    printf("PERFECTE T'HAS REGISTRAT\n");
    afegir_usuaris_a_la_llista(list, user); // afegim l'usuari a la llista enllaçada d'usuaris
    return user;
}

// Funció que afegeix un usuari a la llista d'usuaris, s'utilitza quan baixem els usuaris del fitxer
void afegir_usuaris_a_la_llista(llista_usuaris* list, User* u){ //revisada
    usuaris_llista* node = (usuaris_llista*) malloc(sizeof(usuaris_llista)); // inicialitzem un array dinàmica per a un usuari de la llista
    node->user = u;     //inicialitzar usuari i després posar-lo a la llista
    node->next = NULL;
    node->prev = NULL;

    if (list->first == NULL){ // comprovem si és el primer usuari de la llista
        list->first = node;
        list->last = node;
    }
    else{ // si ja hi ha usuaris a la llista
        list->last->next = node;
        node->prev = list->last;
        list->last = node;

    }
    list->size++;
    for(int i=0; i<5; i++) u->pub[i] = NULL; //canviar de lloc
    u->num_pub = 0; //afegir dins de afegir_usuari
    bubbleSort(list); //ordenem la llista
    init_cua(u);  //inicialitzem les dues cues que tindrà l'usuari, la d'amics i la de sol·licituds
}

// Funció per implementar funció d'ordenació bubbleSort
void bubbleSort(llista_usuaris* llista) { //revisada
    if (llista == NULL || llista->size <= 1) {
        return;  // No cal ordenar una llista buida o amb un únic element
    }

    bool sorted = false; // assumim que primer està desordenat
    while (!sorted) { //per tant, entrarem al while
        sorted = true; // assumim que en aquest moment està ordenat
        usuaris_llista* current = llista->first; //punter per al primer user de la llista
        usuaris_llista* next = current->next; //punter per al segon user de la llista
        while (next != NULL) { //fins que no arribem a l'últim user no sortirà d'aquest while
            // Compara els sobrenoms dels dos usuaris per determinar l'ordre
            if (strcmp(current->user->sobrenom, next->user->sobrenom) > 0) { //en aquest cas l'ordre serà incorrecte
                User* temp = current->user; //fem servir una variable local
                current->user = next->user; //els intercanviem
                next->user = temp;
                sorted = false;  // Marquem que s'ha realitzat un intercanvi
            }
            //movem els dos usuaris a la dreta de la llista
            current = next;
            next = next->next;
        }
    }
}


// En aquesta funció posem tots els usuaris del fitxer a una llista enllaçada
void llegir_fitxer (char* filename, llista_usuaris* llista){ //comprovat
    FILE* f= fopen(filename, "r"); // obrim el fitxer amb el mode lectura
    if (f == NULL){ // comprovem que s'ha pogut obrir
        printf("No s'ha pogut entrar al fitxer");
        return;
    }
    char linia[100];

    while (fgets(linia, sizeof(linia),f) != NULL){ // llegim línia a línia fins que a una no hi hagi res
        User* usuari = (User * ) malloc(sizeof(User)); // reservem espai per a l'usuari
        // llegim les dades de l'usuari del fitxer
        sscanf(linia, "%s %s %s %s %s %d %d %d %d %d %d %d", usuari->sobrenom, usuari->name, usuari->surname, usuari->gmail, usuari->poblacio, &usuari->sexe, &usuari->edat, &usuari->gustos[0], &usuari->gustos[1], &usuari->gustos[2], &usuari->gustos[3], &usuari->gustos[4]);
        afegir_usuaris_a_la_llista(llista, usuari); // afegim l'usuari a la llista
    }
    fclose(f);

}


// En aquesta funció s'omple el fitxer amb la nova llista actualitzada durant l'execució del programa
void omplir_fitxer(char* filename, llista_usuaris* llista){ //revisada
    FILE* fp = fopen(filename, "w"); // obrim el fitxer de tal manera per escriure sobre el que ja estava escrit
    if (fp == NULL){ // comprovem que s'obri
        printf("No s'ha pogut obrir el fitxer");
        return;
    }
    usuaris_llista* current = llista->first; // primer usuari de la llista
    while(current != NULL){ //d'aquesta manera recorrem tota la llista
        // s'escriuen les dades dels usuaris en el fitxer
        fprintf(fp, "%s %s %s %s %s %d %d %d %d %d %d %d\n", current->user->sobrenom, current->user->name, current->user->surname, current->user->gmail, current->user->poblacio, current->user->sexe, current->user->edat, current->user->gustos[0], current->user->gustos[1], current->user->gustos[2], current->user->gustos[3], current->user->gustos[4]);
        current = current->next; // anem canviant d'usuari per ordre dins la llista enllaçada
    }
    fclose(fp);

}

// Funció per a comprovar el correu introduït en el new_user()
int comprovar_correu(User* user){ //revisat
    const char* domain = "estudiant.upf.edu";
    // Troba el símbol de @ a tot l'array del gmail
    const char* atSymbol = strchr(user->gmail, '@');
    if (atSymbol == NULL) { //si no es troba retona 0
        return 0;
    }
    const char* emailDomain = atSymbol + 1;
    return strcmp(emailDomain, domain) == 0; //comparem que el que hi ha després de @ sigui l'esperat
}

void imprimir_amics(User* u){
    for(int i=0; i<u->cua_amics->size; i++){
        if(u->cua_amics->u[i]!=NULL){
            printf("%d. %s , %s %s\n", i+1, u->cua_amics->u[i]->sobrenom, u->cua_amics->u[i]->name, u->cua_amics->u[i]->surname);
        }
        else{
            printf("No tens amistats, revisa les sol·licituds pendents");
        }
    }
}