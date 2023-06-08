#include "estructures.h"
#include "main.h"
#include "play.h"
#include "usuari.h"
#include "publcacions.h"
#include <stdio.h>
#include <string.h>
#define MAX 200

//PUBLICAICONS

void nova_publ(User* user, struct hash_table* dict){ //comprovat
    char tit[MAX_LENGHT_TITOL];
    char cos[MAX_LENGHT_COS];
    printf("Quin titol vols que tingui aquesta publicacio? (EN MAJUSCULES)\n");
    scanf("%s", tit);
    printf("Escriu el cos la publicacio (max. %d caracters):\n", MAX_LENGHT_COS);
    scanf(" %[^\n]s", cos);
    crear_pub(user, dict, tit, cos);
}
void crear_pub(User* user, struct hash_table* dict, char tit[MAX_LENGHT_TITOL], char cos[MAX_LENGHT_COS]){ //comprovat
    int i=4;
    while(i>0){
        user->pub[i] = user->pub[i-1];
        i--;
    }
    add_dict(dict, tit); //afegim el titòl al diccionari
    struct publicacio* nova = (struct publicacio*) malloc(sizeof(struct publicacio));;
    strcpy(nova->titol, tit);
    strcpy(nova->cos, cos);
    user->pub[0] = nova;
    user->num_pub++;
    if(user->num_pub>5) user->num_pub=5;

}

void guardar_publ(char* filename, llista_usuaris* list){ //comprovat
    FILE* f = fopen(filename, "w+");
    if (f == NULL) {
        printf("No s'ha pogut obrir el fitxer");
        return;
    }
    usuaris_llista* act = list->first;
    while(act!=NULL){
        fprintf(f, "%s\n", act->user->sobrenom);
        int i=0;
        while(i<5){
            if(act->user->pub[i] != NULL) {
                fprintf(f, "F\n");
                fprintf(f, "%s\n%s\n", act->user->pub[i]->titol,
                        act->user->pub[i]->cos);
            }
            else{
                fprintf(f, "N\n");
            }
            i++;
        }
        act = act->next;
    }
    fclose(f);
}

void llegir_fitx(char* filename, llista_usuaris* list, struct hash_table* dict){
    char tit[MAX_LENGHT_TITOL];
    char cos[MAX];
    char publ[MAX];
    char comp[MAX_LENGHT];
    char check[MAX_LENGHT];
    char name[MAX_LENGHT];
    char username[MAX_LENGHT];
    FILE* f = fopen(filename, "r");
    if (f == NULL){
        printf("No s'ha pogut entrar al fitxer\n");
        return;
    }
    while (fgets(name, sizeof(name),f) != NULL){
        sscanf(name, "%s", username);
        User* public = buscar(list, username);
        for(int i=0; i<5; i++){
            fgets(comp, sizeof(comp), f);
            sscanf(comp, "%s", check);
            if(strcmp(check, "F")==0){
                fgets(publ, sizeof(publ), f);
                sscanf(publ, "%s", tit);
                fgets(publ, sizeof(publ), f);
                sscanf(publ, "%[^\n]s", cos);
                crear_pub(public, dict, tit, cos);
            }
        }

    }
    fclose(f);
}

void pub_user(User* user){ //comprovat
    printf("Ultimes publicacions de %s:\n", user->sobrenom);
    for(int i=0; i<user->num_pub; i++){
        printf("%d. %s : %s\n", i+1, user->pub[i]->titol, user->pub[i]->cos);
    }
}
void mostrar_publ(llista_usuaris* list, User* user){
    Pila p = init_pila();
    for(int i=0; i<3; i++){
        int n = rand() % 20; // fem que es tri un número fins a 20 perquè tenim 20 usuaris
        User* u = usuari_aleatori(n, list); // usuari corresponent a la posició aleatòria
        while (strcmp(u->sobrenom, user->sobrenom) == 0){ // codi per assegurar-nos que no apareix el mateix usuari
            n = rand() % 20;
            u = usuari_aleatori(n, list);
        }
        push(&p, u); // posem l'usuari a la pila
    }
    for(int j=0; j<3; j++) {
        User *U = top(&p);
        pub_user(U);
        pop(&p);
    }
}

void mostrar_novetats(llista_usuaris* list, User* user){
    usuaris_llista* current = list->first;
    while(current!=NULL){
        if(strcmp(current->user->sobrenom, user->sobrenom)==0) current = current->next;
        else{
            if(current->user->num_pub!=0) {
                printf("%s ha comentat:\n", current->user->sobrenom);
                printf("- %s: %s\n\n", current->user->pub[0]->titol, current->user->pub[0]->cos);
            }
            current = current->next;
        }
    }
}

// Funcions bàsiques per a la implementació del DICIONARI

// Funció que calcula un valor de hash únic per una cadena de caràcters
unsigned int funcio_hash(char* key){
    unsigned long i=0; // inicialitzem el valor de Hash
    for(int j=0; key[j]; j++){ //bucle que itera sobre cada caràcter de la cadena, no acaba fins que el caràcter sigui NULL
        i+=key[j]; // anem acumulant el valor de Hash
    }
    return i%CAPACITY; // tornem el valor del Hash, però dins del rang de capacitat
}

// Funció que crea un nou node en una llista enllaçada
struct node* create_node(char* key){
    struct node* new = (struct node*) malloc(sizeof(struct node)); // reservem memòria per a un nou node
    strcpy(new->key, key); // copiem la key a al del nou node
    new->count=1;
    new->next=NULL;
    return new;
}

// Funció per afegir una paraula al diccionari
void add_dict(struct hash_table* table ,char* key){
    unsigned int index= funcio_hash(key); // obtenim l'índex
    struct node* current = table->array[index]; //
    if (current == NULL) {
        // L'índex està buit, per tant, es crea un nou node i s'assigna com el primer node en l'índex
        table->array[index] = create_node(key);
    } else {
        // L'índex no està buit, es busca una paraula dins la llista enllaçada
        while (current != NULL) {
            if (strcmp(current->key, key) == 0) {
                // La paraula existeix i augmentem el contador
                current->count++;
                return;
            }
            current = current->next; // anem canviant de node per ordre dins la llista enllaçada
        }
        // La paraula no existeix, es crea un nou node i se l'afegeix al final de la llista
        current = table->array[index]; // tornem al primer node de la llista
        while (current->next != NULL) {
            current = current->next; // Avança fina a l'últim node de la llista enllaçada
        }
        current->next = create_node(key); // Es crea un nou node i s'afegeix al final de la llista enl·laçada
    }
}

// Funció que permet obtenir els 10 títols més rellevants del diccionari
void top_10(struct hash_table* dict){ //ns
    struct node* top10[10]; // array per posar els 10 nodes
    int count=0; // comptador del número de nodes

    // inicialitzem l'array
    for (int i = 0; i < 10; i++) {
        top10[i] = NULL;
    }

    for (int i = 0; i < CAPACITY; i++) { // recorrem tot el diccionari
        struct node *current = dict->array[i]; // primer node

        // recorrer la llista enllaçada
        while (current != NULL) {
            int j = 0;

            while (j<count && current->count<top10[j]->count) { // busquem la posició adequada dins de l'array top10
                j++;
            }

            for (int k = count - 1; k >= j; k--) { // movem els nodes a la dreta per fer lloc al nou node
                top10[k + 1] = top10[k];
            }

            top10[j] = current; //assignem el node a la posició j

            if (count < 10) {
                count++; // comprovem si encara hi ha espai

            }
            if (count > 10) { // en cas d'haver-hi 10 nodes, eliminem l'úlitm
                top10[9] = NULL;
                count--;
            }
            current = current->next; // movem
        }
    }
    // codi per imprimir
    printf("Top 10 temes de conversacio: \n");
    for(int i=0; i<10; i++){
        printf("%s: %d \n", top10[i]->key, top10[i]->count);
    }
}

// Funció per alliberar l'espai ocupat pel diccionari
void free_dict(struct hash_table* dict){
    for (int i = 0; i<CAPACITY; i++) {
        struct node* current = dict->array[i]; // primer node
        while (current != NULL) {
            struct node* temp = current; // guardem el node a una variable local
            current = current->next; // ens movem al següent node
            free(temp); // alliberem memòria del node
        }
    }
    free(dict); // alliberem memòria del diccionari
}