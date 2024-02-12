#include <stdio.h>
#include <stdlib.h>
#include "quotazioni.h"

struct bst_s {
    link_BST root;
    link_BST sentinella;
};

struct BSTnodo_s {
    quotazione_giornaliera q;
    int N;
    link_BST left;
    link_BST right;
};

int DATAcmp(data_t d1, data_t d2) {
    if (d1.anno > d2.anno ) {
        return 1;
    }
    else if (d1.anno < d2.anno) {
        return -1;
    }
    else {
        if (d1.mese > d2.mese ) {
            return 1;
        }
        else if (d1.mese < d2.mese) {
            return -1;
        }
        else {
            if (d1.giorno > d2.giorno ) {
                return 1;
            }
            else if (d1.giorno < d2.giorno) {
                return -1;
            }
            else {
                return 0;
            }
        }
    }
}
BST BSTinit (void) {
    BST bst;
    bst = malloc (sizeof(struct bst_s));
    bst->root = (bst->sentinella=BSTnewNode(QUOTAZIONEsetNull(), NULL, NULL, 0));
    return bst;
}
static link_BST BSTnewNode(quotazione_giornaliera q, link_BST l, link_BST r, int N) {
    link_BST x = malloc(sizeof (*x));
    x->q = q;
    x->left = l;
    x->right = r;
    x->N = N;
    return x;
}
void BSTinsertLeafR (BST bst, quotazione_giornaliera q) {
    bst->root = BSTinsertR(bst->root, q, bst->sentinella);
}
static link_BST BSTinsertR(link_BST h, quotazione_giornaliera q, link_BST z) {
    if (h == z)
        return BSTnewNode(q, z, z, 1);
    if (DATAcmp((q.data), (h->q.data))==-1) {
        h->left = BSTinsertR(h->left, q, z);
    }
    else {
        h->right = BSTinsertR(h->right, q, z);
    }
    (h->N)++;
    return h;
}
void BSTfree (BST bst) {
    if (bst == NULL)
        return;
    BSTtreeFree(bst->root, bst->sentinella);
    free(bst->sentinella);
    free(bst);
}
static void BSTtreeFree(link_BST h, link_BST z) {
    if (h == z)
        return;
    BSTtreeFree(h->left, z);
    BSTtreeFree(h->right, z);
    free(h);
}
quotazione_giornaliera BSTsearchR(link_BST h, data_t k, link_BST z) {
    int cmp;
    if (h == z)
        return QUOTAZIONEsetNull();
    cmp = DATAcmp(k, (h->q.data));
    if (cmp == 0)
        return h->q;
    if (cmp == -1)
        return BSTsearchR(h->left, k, z);
    return BSTsearchR(h->right, k, z);
}
quotazione_giornaliera BSTsearch(BST bst, data_t k) {
    return BSTsearchR(bst->root, k, bst->sentinella);
}
void BSTvisitInOrderR(link_BST root, link_BST sentinella, data_t d1, data_t d2, int * max, int * min, int totale) {
    if ( root == sentinella) {
        return;
    }
    BSTvisitInOrderR(root->left, sentinella, d1, d2,  max, min, totale);
    if (totale == 1 || (DATAcmp(root->q.data, d1) >= 0 && DATAcmp(root->q.data, d2) <= 0)) {
        if (root->q.valore_eff > *max) {
            *max = root->q.valore_eff;
        }
        if (root->q.valore_eff < *min) {
            *min = root->q.valore_eff;
        }
    }
    BSTvisitInOrderR(root->right, sentinella, d1, d2, max, min, totale);
}
void BSTvisitMinMax(BST bst, data_t d1, data_t d2, int * max, int * min, int totale) {
    BSTvisitInOrderR(bst->root, bst->sentinella, d1, d2, max, min, totale);
}
link_BST rotL(link_BST h) {
    link_BST x = h->right;
    h->right = x->left;
    x->left = h;
    x->N = h->N;
    h->N = 1;
    h->N += (h->left) ? h->left->N : 0;
    h->N += (h->right) ? h->right->N : 0;
    return x;
}
link_BST rotR(link_BST h) { link_BST x = h->left;
    h->left = x->right;
    x->right = h;
    x->N = h->N;
    h->N = 1;
    h->N += (h->left) ? h->left->N : 0;
    h->N += (h->right) ? h->right->N : 0;
    return x;

}
link_BST partR(link_BST h, int r) {
    int t = h->left->N;
    if (t > r) {
        h->left = partR(h->left, r);
        h = rotR(h);
    }
    if (t < r) {
        h->right = partR(h->right, r-t-1);
        h = rotL(h);
    }
    return h;
}
static link_BST BSTbalanceR(link_BST h, link_BST sentinella) {
    int r;
    if (h == sentinella)
        return sentinella;
    r = (h->N+1)/2-1;
    h = partR(h, r);
    h->left = BSTbalanceR(h->left, sentinella);
    h->right = BSTbalanceR(h->right, sentinella);
    return h;
}
void BSTbalance(BST bst) {
    bst->root = BSTbalanceR(bst->root, bst->sentinella);
}
int BSTheight(BST bst) {
    return bst->root->N;
}
quotazione_giornaliera QUOTAZIONEsetNull(void) {
    quotazione_giornaliera q;
    q.data.anno = 0;
    q.data.mese = 0;
    q.data.giorno = 0;
    q.valore_eff = -1;
    return q;
}