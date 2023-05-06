#include <stdio.h>
#include "main.h"

void new_user(){

}
void menu(){
    int n;
    n = printmenu();
    if (n==1){
        new_user();
    }
    if (n==2){
        all_users();
    }
    if (n==3){
        interactuar();
    }
}
int printmenu(){
    int n;
    printf("Escolliu una opcis:\n [1]. Afegir usuari\n [2]. Listat d'usuaris\n [3]. Interactuar amb un usuari\n [4]. Sortir");
    fscanf(stdin,"%d", n); //mirar com es el scan
    return n;
}
int main() {
    printf("Hello, World!\n");
    return 0;

}
