#ifndef PG_H_DEFINED
#define PG_H_DEFINED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "equipArray.h"
#include "inv.h"

/* quasi ADT personaggio */
typedef struct pg_s {
  char cod[LEN];
  char nome[LEN];
  char classe[LEN];
  stat_t b_stat, eq_stat;
  equipArray_t equip;
} pg_t;

typedef struct nodoPg * link;


/* lettura e scrittura su file */
int pg_read(FILE *fp, pg_t *pgp);
/* non essendo struct dinamica, pulisce chiamando il distruttore di equipArray */
void pg_clean(pg_t *pgp);

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray);

void pg_updateEquip(pg_t *pgp, invArray_t invArray);



#endif
