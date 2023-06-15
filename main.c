/*  Trabalho 2 - Cuckoo Hashing
 *  Autor: João Vitor de Oliveira Souza    GRR20211760
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "libhash.h"

#define TAM_TAB 11
#define INSERSAO 'i'
#define REMOCAO 'r'


int main (int agrc, char **argv){
    Tabelas_t *t;
    int chave;
    char op;

    t = criaTabelas(TAM_TAB);

    while (fscanf(stdin, "%c %d", &op, &chave) != EOF){
        if (op == INSERSAO) inclui(chave, t);
        if (op == REMOCAO) exclui(chave, t);
    }

    imprimeTab(t, t->nSlots);

    t = destroiTabelas(t);

    return 0;
}