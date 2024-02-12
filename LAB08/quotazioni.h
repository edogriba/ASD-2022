#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bst_s * BST;
typedef struct BSTnodo_s * link_BST;

typedef struct {
    int anno;
    int mese;
    int giorno;
    int ora;
    int minuti;
} data_t ;

typedef struct  {
    data_t data;
    int * quantita;
    int * valori;
    int transazioni;
    int valore_eff;
} quotazione_giornaliera;


BST BSTinit(void);
static link_BST BSTnewNode(quotazione_giornaliera q, link_BST l, link_BST r, int N);
void BSTinsertLeafR (BST bst, quotazione_giornaliera q);
static link_BST BSTinsertR(link_BST h, quotazione_giornaliera x, link_BST sentinella);
static void BSTtreeFree(link_BST h, link_BST z);
quotazione_giornaliera BSTsearchR(link_BST h, data_t k, link_BST z);
quotazione_giornaliera BSTsearch(BST bst, data_t k);
void BSTvisitInOrderR(link_BST root, link_BST sentinella, data_t d1, data_t d2, int * max, int * min, int totale);
void BSTvisitMinMax(BST bst, data_t d1, data_t d2, int * max, int * min, int totale);
link_BST partR(link_BST h, int r);
static link_BST BSTbalanceR(link_BST h, link_BST z);
void BSTbalance(BST bst);
int BSTheight(BST bst);
void BSTfree (BST bst);
quotazione_giornaliera QUOTAZIONEsetNull(void);
int DATAcmp(data_t d1, data_t d2);

