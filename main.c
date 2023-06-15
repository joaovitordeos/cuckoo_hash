/*  Trabalho 2 - Cuckoo Hashing
 *  Autor: João Vitor de Oliveira Souza    GRR20211760
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "libhash.h"

#define TAM_TAB 11

int main (int agrc, char **argv){
    Tabelas_t *t;

    t = criaTabelas(TAM_TAB);

    //for (int i = 0; i < 22 ; i++)
    //    inclui(i, t);


    inclui(10, t);
    inclui(22, t);
    inclui(4, t);
    inclui(15, t);
    inclui(59, t);


    imprimeTab(t, t->nSlots);

    t = destroiTabelas(t);

    return 0;
}