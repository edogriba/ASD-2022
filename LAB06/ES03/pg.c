#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "inv.h"
#include "invArray.h"
#include "equipArray.h"
#include "pg.h"
#include "pgList.h"

/* Equipaggiamento personaggio */
struct equipArray_s {
    int inUso;
    int * vettEq;
};


/* creatore e distruttore */
equipArray_t equipArray_init() {
    equipArray_t equipArray = (equipArray_t) malloc ( sizeof(struct equipArray_s));
    equipArray->inUso = 0;
    equipArray->vettEq = (int *) malloc ( EQUIP_SLOT * sizeof(int) );
    return equipArray;
};
void equipArray_free(equipArray_t equipArray) {
    free(equipArray);
};

/* quanti equipaggiamenti sono in uso */
int equipArray_inUse(equipArray_t equipArray) {
    return equipArray->inUso;
}

/* scrittura su file */
void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray) {
    int i;
    equipArray = equipArray_init();
    for (i=0; i< equipArray_inUse(equipArray); i++) {
        invArray_printByIndex(fp,  invArray, equipArray->vettEq[i]);
    }
};
/* modifica equipaggiamento scegliendo un oggetto da inventario */
void equipArray_update(equipArray_t equipArray, invArray_t invArray) {
    int n, i, j, flag, trovato=0;
    int index = equipArray_inUse(equipArray);
    char * name = (char *) malloc(LEN * sizeof(char));
    printf("Come si chiama l'equipaggiamento che vuoi cercare?\n");
    scanf("%s", name);
    flag = invArray_searchByName(invArray, name);
    if (flag == -1) {
        printf("Non è stato trovato un equipaggiamento con il nome digitato\n");
        return;
    }
    printf("Digitare 1 per aggiungere l'equipaggiamento, 2 per togliere l'equipaggiamento\n");
    scanf("%d", &n);
    n--;
    switch (n) {
        case 0:
            equipArray->vettEq[equipArray->inUso] = flag;
            equipArray->inUso++;
            break;
        case 1:
            for (i=0; i<index; i++) {
                if (equipArray_getEquipByIndex(equipArray, i) ==  flag) {
                    for (j=i; j<index; j++) {
                        equipArray->vettEq[j] = equipArray->vettEq[i+j];
                    }
                    equipArray->inUso--;
                    trovato = 1;
                    break;
                }
            }
            if (trovato == 0) {
                printf("Il personaggio non è equipaggiato con quell'oggetto\n");
            }
            break;
        default:
            printf("Comando non disponibile\n");
    }


    free(name);
}
/* torna indice (nel vettore inventario) dell'oggetto in posizione index (0..EQUIP_SLOT-1) di equipArray */
int equipArray_getEquipByIndex(equipArray_t equipArray, int index) {
    return equipArray->vettEq[index];
}

/* Personaggi */

int pg_read(FILE *fp, pg_t *pgp) {
    if (fp != stdin) {
        if (fscanf(fp, "PG%s %s %s", pgp->cod,  pgp->nome,  pgp->classe) != 3) {
            return 0;
        }
    }
    else {
        fprintf(fp, "PG");
        if (fscanf(fp, "%s %s %s", pgp->cod,  pgp->nome,  pgp->classe) != 3) {
            return 0;
        }
    }
    stat_read(fp, &(pgp->b_stat));
    pgp->equip = equipArray_init();
    return 1;
}
/* non essendo struct dinamica, pulisce chiamando il distruttore di equipArray */
void pg_clean(pg_t *pgp) {
    equipArray_free(pgp->equip);
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray) {
    int i=0;
    stat_t somma_stat = pgp->b_stat;
    fprintf(fp, "%s %s %s", pgp->cod, pgp->nome, pgp->classe);
    stat_print(fp, &(pgp->b_stat), 0);
    for (i=0; i<pgp->equip->inUso; i++) {
        inv_print(fp, invArray_getByIndex(invArray, pgp->equip->vettEq[i]));
        somma_stat = somma(somma_stat, inv_getStat(invArray_getByIndex(invArray, pgp->equip->vettEq[i])));
    }
    if (i>0) {
        pgp->eq_stat = somma_stat;
        stat_print(fp, &(pgp->eq_stat), 0);
    }

}
/* modifica personaggio aggiungendo/togliendo un equipaggiamento selezionato da inventario:
di fatto e' sufficiente chiamare l'opportuna funzione dal modulo equipArray */
void pg_updateEquip(pg_t *pgp, invArray_t invArray) {
    equipArray_update(pgp->equip, invArray);
};

/* Lista Personaggi */

typedef struct nodoPg {
    pg_t personaggio;
    link next;
} nodoPg_t;

struct pgList_s {
    link headPg;
    link tailPg;
    int nPg;
};

pgList_t pgList_init() {
    pgList_t pgList;
    pgList = (pgList_t) malloc(sizeof(struct pgList_s));
    pgList->headPg = NULL;
    pgList->tailPg = NULL;
    pgList->nPg = 0;
    return pgList;
};
void pgList_free(pgList_t pgList) {
    free(pgList);
}

/* lettura e scrittura su file */
void pgList_read(FILE *fp, pgList_t pgList) {
    pg_t * pgp;
    pgp = (pg_t *) malloc(sizeof(pg_t));
    while (pg_read(fp, pgp) == 1) {
        listInsTail(pgList, *pgp);
    }
}
void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray) {
    int i;
    link x;
    if (pgList->headPg == NULL) {
        printf("La lista è vuota: inserire dei personaggi\n");
    }
    else {
        printf("La lista è composta da\n");
        for (x = pgList->headPg; x != NULL; x = x->next) {
            fprintf(fp, "%s %s %s ", x->personaggio.cod, x->personaggio.nome, x->personaggio.classe);
            stat_print(fp, &(x->personaggio.b_stat), 0);
            equipArray_print(fp, x->personaggio.equip, invArray);
        }

    }
}

/* inserimento di un nuovo personaggio */
void pgList_insert(pgList_t pgList, pg_t pg) {
    listInsTail(pgList, pg);
}
/* cancellazione con rimozione */
void pgList_remove(pgList_t pgList, char * cod) {
    link x, h, p;
    h = pgList->headPg;
    if (h == NULL) {
        printf("La lista è vuota\n");
    } else {
        for (x = h, p = NULL; x != NULL; p = x, x = x->next) {
            if (strcmp(cod, x->personaggio.cod) == 0) {
                if (x == h) {
                    pgList->headPg = x->next;
                }
                else {
                    p->next = x->next;
                }
                pg_clean(&(x->personaggio));
                free(x);
                return;
            }
        }
    }
    printf("Personaggio non trovato\n");
}
/* ricerca per codice, ritornando il puntatore */
pg_t * pgList_searchByCode(pgList_t pgList, char * cod) {
    link x;
    for ( x=pgList->headPg; x != NULL ; x= x->next) {
        if (strcmp(cod, x->personaggio.cod) == 0) {
            return &(x->personaggio);
        }
    }
    return NULL;
}

link newNode (pg_t val, link next) {
    link x = (link) malloc(sizeof (nodoPg_t));
    if (x==NULL)
        return NULL;
    else {
        x->personaggio = val;
        x->next = next;
    }
    return x;
}

void listInsTail(pgList_t pgList, pg_t val) {
    link p;
    if (pgList->headPg == NULL ) {
        pgList->headPg = newNode(val, NULL);
        pgList->tailPg = pgList->headPg;
    }
    else {
        p = newNode(val, NULL);
        pgList->tailPg->next = p;
        pgList->nPg++;
        pgList->tailPg = p;
    }
}