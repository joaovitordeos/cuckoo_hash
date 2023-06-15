/*  Trabalho 2 - Cuckoo Hashing
 *  Autor: João Vitor de Oliveira Souza    GRR20211760
 */
#ifndef __LIBHASH__
#define __LIBHASH__

// Estrutura de slot que representa cada bloco da tabela Hash.
typedef struct slot{
    int valor;              
    enum {VAZIO, OCUPADO, EXCLUIDO} status;  // Situação do slot, se está vazio,ocupado ou se foi uma chave excluída.
} Slot_t;


// Estrutura que engloba duas tabelas do tipo Slot_t.
typedef struct tabelas{
    int nChaves;           // Número de chaves na tabela.  
    int nSlots;            // Número de slots em cada tabela
    Slot_t *T1;
    Slot_t *T2;
} Tabelas_t;

/*  Aloca as duas tabelas com 'nSlots' de capacidade em cada uma.
    
    Retorna um ponteiro para as tabelas.
    Retorna NULL em caso de falha.   */
Tabelas_t *criaTabelas(int nSlots);

/*  Desaloca a memória da tabela. Retorna NULL. */
Tabelas_t *destroiTabelas(Tabelas_t *t);

/*  Primeira função hash usando a técnica linear. (chave mod slots). */
int hash1(int chave, int slots);

/*  Segunda função hash usando a técnica quadrática. */
int hash2(int chave, int slots);

/*  Função responsável pela busca da chave nas duas tabelas. */
int busca(int chave, Tabelas_t *t);

/*  Inclui a chave em uma das tabelas. */
void inclui(int chave, Tabelas_t *t);

/*  Exclui a chave das tabelas. */
void exclui(int chave, Tabelas_t *t);

void imprimeTab(Tabelas_t *t, int nSlots);

#endif