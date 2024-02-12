#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "invArray.h"
#include "inv.h"

#define MAX_INV 20 // massimo degli oggetti nell'inventario



/* funzioni di input/output delle statistiche */
void stat_read(FILE *fp, stat_t *statp) {
    if (fp != stdin) {
        fscanf(fp, "%d %d %d %d %d %d\n", &statp->hp, &statp->mp, &statp->atk, &statp->def, &statp->mag,
               &statp->spr);
    }
    else {
        fscanf(fp, "%d %d %d %d %d %d", &statp->hp, &statp->mp, &statp->atk, &statp->def, &statp->mag,
               &statp->spr);
    }
}
void stat_print(FILE *fp, stat_t *statp, int soglia) {
    fprintf(fp, "hp: %d mp: %d atk: %d def: %d mag: %d spr: %d\n", (statp->hp < soglia) ? soglia : statp->hp, (statp->mp < soglia) ? soglia : statp->mp, (statp->atk < soglia) ? soglia : statp->atk, (statp->def < soglia ) ? soglia : statp->def, (statp->mag < soglia ) ? soglia : statp->mag, (statp->spr < soglia) ? soglia : statp->spr);
}
/* funzioni di input/output di un oggetto dell'inventario */
void inv_read(FILE *fp, inv_t *invp) {
    fscanf(fp, "%s %s", invp->nome, invp->tipo);
    stat_read(fp, &(invp->stat));
}
void inv_print(FILE *fp, inv_t *invp) {
    fprintf(fp, "%s %s", invp->nome, invp->tipo);
    stat_print(fp, &(invp->stat), -15000); // quando si stampano i modificatori si vuole vedere se ci sono delle variazioni in negativo
}

/* ritorna il campo stat di un oggetto dell'inventario */
stat_t inv_getStat(inv_t *invp) {
    return invp->stat;
};
stat_t somma(stat_t stat1, stat_t stat2) {
    stat_t somma_stat;
    somma_stat.hp = stat1.hp + stat2.hp;
    somma_stat.mp = stat1.mp + stat2.mp;
    somma_stat.atk = stat1.atk + stat2.atk;
    somma_stat.def = stat1.def + stat2.def;
    somma_stat.mag = stat1.mag + stat2.mag;
    somma_stat.spr = stat1.spr + stat2.spr;
    return somma_stat;
}
/* ARRAY DELL'INVENTARIO */

invArray_t invArray_init() {
    invArray_t invArray;
    invArray = (invArray_t) malloc( sizeof(struct invArray_s) ); // controlla bene
    invArray->maxInv = MAX_INV;
    invArray->nInv=0;
    invArray->vettInv= NULL;
    return invArray;
}
void invArray_free(invArray_t invArray) {
    free(invArray);
}

/* lettura e scrittura su file */
void invArray_read(FILE *fp, invArray_t invArray) {
    int i;
    fscanf(fp, "%d", &(invArray->nInv));
    invArray->vettInv = (inv_t  *) malloc ((invArray->nInv) * sizeof(inv_t));
    for (i=0; i<invArray->nInv; i++) {
        inv_read(fp, &(invArray->vettInv[i]));
    }
};
void invArray_print(FILE *fp, invArray_t invArray) {
    int i;
    printf("L'inventario è composto dai seguenti oggetti:\n");
    for (i=0; i<invArray->nInv; i++) {
        inv_print(fp, &(invArray->vettInv[i]));
    }
}
/* stampa un unico oggetto selezionato da indice (nel vettore) */
void invArray_printByIndex(FILE *fp, invArray_t invArray, int index) {
    inv_print(fp, &(invArray->vettInv[index]));
}
/* ritorna puntatore a oggetto selezionato da indice (nel vettore) */
inv_t *invArray_getByIndex(invArray_t invArray, int index) {
    return &(invArray->vettInv[index]);
}
/* ritorna indice (nel vettore) a oggetto selezionato da nome */
int invArray_searchByName(invArray_t invArray, char *name) {
    int i;
    for ( i=0; i< invArray->maxInv; i++) {
        if (strcmp(invArray->vettInv[i].nome, name) == 0) {
            return i;
        }
    }
    return -1;
}
