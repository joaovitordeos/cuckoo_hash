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
        s1[i].local = T1;
        s2[i].status = VAZIO;
        s2[i].local = T2;
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

    h1 = hash1(abs(chave), t->nSlots);
    h2 = hash2(abs(chave), t->nSlots);

    // Se o local estiver vazio retornará NAO_EXISTE (-1)
    if (t->T1[h1].status == VAZIO) return NAO_EXISTE;

    if (t->T1[h1].valor == chave) return h1;

    return t->T2[h2].valor;
}

/*  Inclui a chave em uma das tabelas. */
void inclui(int chave, Tabelas_t *t){
    int h1, ih2;
    

    h1 = hash1(abs(chave), t->nSlots);           // Hash1 da chave a ser inserida.

    // Se o slot estiver vazio, ou for um slot com um valor excluído uma nova chave será inserida
    if ((t->T1[h1].status == VAZIO) || (t->T1[h1].status == EXCLUIDO)){
        t->T1[h1].valor = chave;
        t->T1[h1].status = OCUPADO;
        t->nChaves++;
        return ;
    }
    else if (t->T1[h1].valor == chave) return ; // Ignorando duplicatas
    
    ih2 = hash2(abs(t->T1[h1].valor), t->nSlots);   // Hash2 da chave em T1 que será movida

    // Move a chave presente em T1 para o seu slot em T2 [ h2(ki) ].
    t->T2[ih2].valor = t->T1[h1].valor;
    t->T2[ih2].status = OCUPADO;

    // A nova chave é inserida em T1, no lugar da antiga.
    t->T1[h1].valor = chave;
    t->nChaves++;
    return ;
}

/*  Exclui a chave das tabelas. */
void exclui(int chave, Tabelas_t *t){
    int h1, h2;

    h1 = hash1(abs(chave), t->nSlots);
    h2 = hash2(abs(chave), t->nSlots);

    // Se a chave estiver em T2, ela é removida
    if ((t->T2[h2].status != VAZIO) &&  (t->T2[h2].valor == chave)){
        t->T2[h2].status = VAZIO;
        t->nChaves--;
        return;
    }

    // Se não ela é removida em T1 e o slot é marcado como EXCLUÍDO
    t->T1[h1].status = EXCLUIDO;
    t->nChaves--;
}

/*  Função de comparação do parâmetro valor da struct Slot_t para o qsort. */
int comparaChaves(const void *a, const void *b){
    Slot_t *x, *y;

    x = (Slot_t *) a;
    y = (Slot_t *) b;

    if (x->valor > y->valor) return 1;
    if (x->valor < y->valor) return -1;
    return 0;
}

/*  Imprime na saída padrão de forma crescente as chaves presentes nas tabelas,
    juntamente com sua localização (T1 ou T2) e sua posição no vetor. 
    
    Ela usa um vetor de Slot_t auxiliar que é ordenado usand o algoritmo qsort. */
void imprimeTab(Tabelas_t *t, int nSlots){
    int nVal, i;
    Slot_t *v;
    
    v = malloc(sizeof(Slot_t)* 2 * nSlots);
    if (!v) return;

    // Insere os valores das tabelas no vetor auxiliar de Slot_t 'v'.
    nVal = 0;
    for (i = 0; i < nSlots ; i++){  
        if (t->T1[i].status == OCUPADO){
            v[nVal] = t->T1[i];
            nVal++;            
        }
        if (t->T2[i].status == OCUPADO){
            v[nVal] = t->T2[i];
            nVal++;   
        }
    }
    // Ordena usando qsort 
    qsort(v, nVal, sizeof(Slot_t), comparaChaves);

    // Imprime formatado na saída padrão.
    for (i = 0; i < nVal ; i++){
        if (v[i].local == T1)
            fprintf(stdout, "%d,T1,%d\n", v[i].valor, hash1(abs(v[i].valor), t->nSlots));
        if (v[i].local == T2)
            fprintf(stdout, "%d,T2,%d\n", v[i].valor, hash2(abs(v[i].valor), t->nSlots));    
    }

    free(v);
}