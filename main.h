#ifndef EDAII_MAIN_H
#define EDAII_MAIN_H


void menu();
void all_users();
int printmenu();
User* new_user();
void interactuar();
void enviar_s_amistat_aleatoria();
void publicacio();
void gestionar_s_pendents();
void crear_gustos();
void afegir_usuaris_a_la_llista();
User busqueda();
void crear_llista();
struct Queue_sol* init_cua();
struct Queue_sol* afegir_sol();
struct Queue_sol* treure_sol();
usuaris_llista* buscar();
void enviar_s_amistat();
void mostrarusuari();

#endif //EDAII_MAIN_H