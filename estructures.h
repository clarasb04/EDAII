//
// Created by clara on 05/05/2023.
//

#ifndef EDAII_ESTRUCTURES_H
#define EDAII_ESTRUCTURES_H
#define MAX_LENGHT 30

#endif //EDAII_ESTRUCTURES_H

typedef struct Usuari{
    char sobrenom[MAX_LENGHT];
    char name[MAX_LENGHT];
    char surname[MAX_LENGHT];
    char gmail[MAX_LENGHT];
    char poblacio[MAX_LENGHT];
    char sexe[1];
    int edat;
    struct Gustos;
};

typedef  struct Gustos{
    char sexe[2];
    int edat;
};