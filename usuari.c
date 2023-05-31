#include "estructures.h"
#include "main.h"
#include "play.h"
#include "usuari.h"
#include <stdio.h>
#include "string.h"


void crear_gustos(User* u){
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


User* new_user(llista_usuaris* list){
    User* user = (User*)malloc(sizeof(User));
    printf("Introdueix el sobrenom: \n");
    scanf("%s", user->sobrenom);
    if(buscar(list,user->sobrenom) != NULL){
        printf("Introdueix el sobrenom: \n");
        scanf("%s", user->sobrenom);
    }
    printf("Introdueix el nom:");
    scanf("%s", user->name);
    printf("Introdueix el cognom:");
    scanf("%s", user->surname);
    printf("Introdueix el correu de la universitat:");
    scanf("%s", user->gmail);
    while(comprovar_correu(user)==0){
        printf("El correu introduit no és valid");
        scanf("%s", user->gmail);
    }
    printf("Introdueix la poblacio:");
    scanf("%s", user->poblacio);
    printf("Introdueix el sexe M o F:");
    scanf("%s", user->sexe);
    printf("Introdueix l'edat:");
    scanf("%d", &user->edat);
    crear_gustos(user);
    printf("PERFECTE T'HAS REGISTRAT\n");
    afegir_usuaris_a_la_llista(list, user); //fins aqui està comprovat i funciona
    return user;
}


//Funció per inicialitzar llista, s'utilitza quan baixem els usuaris del fitxer
llista_usuaris* init_list(){
    llista_usuaris* llista = (llista_usuaris*) malloc(sizeof(usuaris_llista));
    llista->size = 0;
    llista->first = NULL;
    llista->last = NULL;
    return llista;
}
// En aquesta funció s'afegeix un usuari a la llista d'usuaris
void afegir_usuaris_a_la_llista(llista_usuaris* list, User* u){
    usuaris_llista* node = (usuaris_llista*) malloc(sizeof(usuaris_llista)); //canviar el tamany llista i no usuari
    node->user = u;     //inicialitzar usuari i despres posarlo a la llista
    node->next = NULL;
    node->prev = NULL;

    if (list->first == NULL){
        list->first = node;
        list->last = node;
        node->prev = NULL;
    }
    else{
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }
    printf("%s\n", list->first->user->name);
    list->size++;
}

/* Funció per implementar funció d'ordenació
void afegir_usuari(llista_usuaris* list, User* u){
    //buscar la posició corresponent
    usuaris_llista comp;
    int check=0;
    comp = *list->first;
    while(check==0){
        if(strcmp(comp.user->sobrenom, u->sobrenom)==2){
            check=1;
        }
        //comp = comp.next;
    }
}
*/

// En aquesta funció posem tots els usuaris del fitxer a una llista
llista_usuaris* llegir_fitxer(char* filename){ //File* f
    FILE* f= fopen(filename, "r");
    if (f == NULL){
        printf("No s'ha pogut entrar al fitxer");
        return NULL;
    }
    llista_usuaris* llista = init_list();
    char linia[100];
    while (fgets(linia, sizeof(linia),f) != NULL){
        User* user = (User*) malloc(sizeof(User));

        sscanf(linia, "%s %s %s %s %s %c %d %d %d %d %d", user->sobrenom, user->name, user->surname, user->gmail, user->poblacio, &user->sexe, &user->edat, &user->gustos[0], &user->gustos[1], &user->gustos[2], &user->gustos[3], &user->gustos[4]);
        afegir_usuaris_a_la_llista(llista, user);
        free(user);

    }
    fclose(f);
    //reservar espai i afegir l'usuari a la llista
    return llista;
}


// En aquesta funció s'omple el fitxer amb la nova llista actualitzada
void omplir_fitxer(char* filename, llista_usuaris* llista){
    FILE* fp = fopen(filename, "w"); //mirar com s'ha d'obrir
    if (fp == NULL){
        printf("No s'ha pogut obrir el fitxer");
        return;
    }
    usuaris_llista* current = llista->first;
    while(current != NULL){
        fprintf(fp, "%s %s %s %s %s %c %d", current->user->sobrenom, current->user->name, current->user->surname, current->user->gmail, current->user->poblacio, current->user->sexe, current->user->edat);

        for (int i = 0; i < 5; i++){
            fprintf(fp, "%d", current->user->gustos[i]);
        }
        fprintf(fp, "\n");
        current = current->next;
    }
    fclose(fp);

}



int comprovar_correu(User* user){
    char* correu_u = user->gmail;
    char* comp = "estudiant.upf.edu";
    char* temp;
    for (int i=0; i<MAX_LENGHT; i++){
        if (strcmp(correu_u, "@")==0){
            for (int j=0; j<(MAX_LENGHT-i); j++){
                temp[j] = correu_u[i+j];
            }
            if (strcmp(temp,comp)==0){
                return 1;
            }
        }
    }
    return 0;
}