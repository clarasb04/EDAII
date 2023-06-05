#include "estructures.h"
#include "main.h"
#include "play.h"
#include "usuari.h"
#include "publcacions.h"
#include <stdio.h>
#include <string.h>
#define MAX 200

//PUBLICAICONS

void publ(User* user, struct hash_table* dict){
    if (user->pub->num<0) user->pub->num=0;
    printf("El titular de la teva publacació (una paraula en majuscules)\n");
    scanf("%s", user->pub[user->pub->num+1].titol);
    printf("Cos de la publicacio maxim 120 paraules\n");
    scanf("%s", user->pub[user->pub->num+1].cos);
    //add_dict(dict ,user->pub[user->pub->num+1].titol); //per afegir paraula al dicionari
    char* nom_fitxer = "publiacions";
    guardar_publ(nom_fitxer, user);
    user->pub->num+=1;
}

void guardar_publ(char* filename, User* user){
    FILE* f = fopen(filename, "w+");
    if (f == NULL) {
        printf("No s'ha pogut obrir el fitxer");
        return;
    }

    fprintf(f, "%d/%s/%s/%s\n", user->pub->num, user->sobrenom, user->pub[user->pub->num].titol, user->pub[user->pub->num].cos);
    fclose(f);
}

void mostrar_publ(char* filename){
    char a[MAX];
    User* u= malloc(sizeof (User));
    FILE* f = fopen(filename, "r");
    if (f==NULL){
        printf("No s'ha pogut entrar al fitxer");
        return;
    }
    while(fgets(a, MAX, f)!=NULL){
        sscanf(a, "%d/%s/%s/%s", &u->pub->num, u->sobrenom, u->pub[u->pub->num].titol, u->pub[u->pub->num].cos);
        printf("%s\n%s\n", u->pub[u->pub->num].titol, u->pub[u->pub->num].cos);

    }
    free(u);
}

void pub_user(char* filename, User* user){ //s'ha de fer
    char a[MAX];
    User* u= malloc(sizeof (User));

    FILE* f = fopen(filename, "r");
    if (f == NULL){
        printf("No s'ha pogut entrar al fitxer");
        return;
    }
    while(fgets(a, MAX, f)!=NULL){
        sscanf(a, "%d/%s/%s/%s", &u->pub->num, u->sobrenom, u->pub[u->pub->num].titol, u->pub[u->pub->num].cos);
        if (strcmp(u->sobrenom,user->sobrenom)==0){
            printf("%s\n%s\n", user->pub[u->pub->num].titol, user->pub[u->pub->num].cos);
        }
    }
    free(u);
}


//DICIONARI
//HashTable *create_table(int size){}
unsigned int hash_function(char* key){
    unsigned long i=0;
    for(int j=0; key[j]; j++){
        i+=key[j];
    }
    return i%CAPACITY;
}


struct node* create_node(char* key){
    struct node* new = (struct node*) malloc(sizeof(struct node));
    strcpy(new->key, key);
    new->count=1;
    new->next=NULL;
    return new;
}

void add_dict(struct hash_table* table ,char* key){
    unsigned int index= hash_function(key);
    struct node* current = table->array[index];
    if (current==NULL){
        printf("Diciionari complert");
        return;
    }
    while (current!=NULL){
        if (strcmp(current->key, key)==0){ //si es troba la paraula s'incrementa el comptador
            current->count++;
            return;
        }
        current=current->next;
    }
    //si no es troba la paraula es crea un nou node i s'afegueix al final
    struct node* new = create_node(key);
    current=table->array[index];
    while (current->next!=NULL){
        current=current->next;
    }
    current->next=new;
}

void top_10(struct hash_table* dict){ //ns
    struct node* top10[10];
    int count=0;
    for (int i = 0; i < 10; i++) {
        top10[i] = NULL;
    }
    for (int i = 0; i < CAPACITY; i++) {
        struct node *current = dict->array[i];
        while (current != NULL) {
            int j = 0;
            while (j<count && current->count<top10[j]->count) {
                j++;
            }
            for (int k = count - 1; k >= j; k--) {
                top10[k + 1] = top10[k];
            }
            top10[j] = current;
            if (count < 10) {
                count++;
            }
            if (count > 10) {
                top10[9] = NULL;
                count--;
            }
            current = current->next;
        }
    }
    printf("Top 10 temes de conversació: \n");
    for(int i=0; i<10; i++){
        printf("%s: %d \n", top10[i]->key, top10[i]->count);
    }
}

void free_dict(struct hash_table* dict){
    for (int i = 0; i<CAPACITY; i++) {
        struct node* current = dict->array[i];
        while (current != NULL) {
            struct node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(dict);
}