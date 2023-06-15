/*  Trabalho 2 - Cuckoo Hashing
 *  Autor: João Vitor de Oliveira Souza    GRR20211760
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "libhash.h"

#define CONST 0.9
#define NAO_EXISTE -1

/*  Aloca as duas tabelas com 'nSlots' de capacidade em cada uma.
    
    Retorna um ponteiro para as tabelas.
    Retorna NULL em caso de falha.   */
Tabelas_t *criaTabelas(int nSlots){
    Slot_t *s1, *s2;
    Tabelas_t *t;
    int i;

    t = malloc(sizeof(Tabelas_t));
    if (!t) return NULL;

    s1 = malloc(sizeof(Slot_t) * nSlots);
    if (!s1) return NULL;

    s2 = malloc(sizeof(Slot_t) * nSlots);
    if (!s2) return NULL;

    // Marca todos os slots como vazios.
    for (i = 0; i < nSlots ; i++){
        s1[i].status = VAZIO;
        s2[i].status = VAZIO;
    }

    t->nSlots = nSlots;
    t->nChaves = 0;
    t->T1 = s1;
    t->T2 = s2;

    return t;
}

/*  Desaloca a memória da tabela. Retorna NULL. */
Tabelas_t *destroiTabelas(Tabelas_t *t){
    free(t->T1);
    free(t->T2);
    free(t);

    return NULL;
}


/*  Primeira função hash usando a técnica linear. (chave mod slots). */
int hash1(int chave, int slots){
    return chave % slots;
}

/*  Segunda função hash usando a técnica quadrática. */
int hash2(int chave, int slots){
    return floor(slots*(chave*CONST - floor(chave*CONST)));
}

/*  Função responsável pela busca da chave nas duas tabelas. */
int busca(int chave, Tabelas_t *t){
    int h1, h2;

    h1 = hash1(chave, t->nSlots);
    h2 = hash2(chave, t->nSlots);

    // Se o local estiver vazio retornará NAO_EXISTE (-1)
    if (t->T1[h1].status == VAZIO) return NAO_EXISTE;

    if (t->T1[h1].valor == chave) return h1;

    return t->T2[h2].valor;
}

/*  Inclui a chave em uma das tabelas. */
void inclui(int chave, Tabelas_t *t){
    int h1, ih2;
    

    h1 = hash1(chave, t->nSlots);
    ih2 = hash2(t->T1[h1].valor, t->nSlots);

    if ((t->T1[h1].status == VAZIO) || (t->T1[h1].status == EXCLUIDO)){
        t->T1[h1].valor = chave;
        t->T1[h1].status = OCUPADO;
        t->nChaves++;
        return ;
    }
    else if (t->T1[h1].valor == chave) return ;

    t->T2[ih2].valor = t->T1[h1].valor;
    t->T2[ih2].status = OCUPADO;

    t->T1[h1].valor = chave;
    t->nChaves++;
    return ;
}

/*  Exclui a chave das tabelas. */
void exclui(int chave, Tabelas_t *t){
    int h1, h2;

    h1 = hash1(chave, t->nSlots);
    h2 = hash2(chave, t->nSlots);

    if (t->T2[h2].valor == chave){
        t->T2[h2].status = VAZIO;
        t->nChaves--;
        return;
    }

    t->T1[h1].status = EXCLUIDO;
    t->nChaves--;
}

void imprimeTab(Tabelas_t *t, int nSlots){
    for (int i = 0; i < nSlots ; i++){  
        if (t->T1[i].status == OCUPADO)
            fprintf(stdout, "%d | T1 | %d\n", t->T1[i].valor, i);
        if (t->T2[i].status == OCUPADO)
            fprintf(stdout, "%d | T2 | %d\n", t->T2[i].valor, i);
    }
}