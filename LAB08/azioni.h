#include <stdio.h>
#include <stdlib.h>
#define STRMAX 30
#include "quotazioni.h"

enum comando_e {
    leggi_file,
    ricerca_titolo,
    ricerca_quotazione,
    ricerca_quotazione_max_min_int,
    ricerca_quotazione_max_min_totale,
    bilancia_bst_quotazioni,
    chiudi
};

typedef struct nodo_s * link;
typedef struct TITOLO_s * TITOLO;
typedef struct collezione_titoli_s * COLLEZIONE_TIT;

int leggiComando(void);
TITOLO TITinit(void);
TITOLO TITsetvoid();
void TITfree(TITOLO azione);
void COLLreadFile(COLLEZIONE_TIT collezione, FILE * fp);
void COLLsearchTit(COLLEZIONE_TIT collezione, char * s);
void COLLsearchQuot(COLLEZIONE_TIT collezione, char * s);
void COLLsearchMinMax(COLLEZIONE_TIT collezione, char * s);
void COLLsearchMinMaxTot(COLLEZIONE_TIT collezione, char * s);
void COLLBalance( COLLEZIONE_TIT collezione, char * s, int S);
COLLEZIONE_TIT COLLinit(void);
void COLLshow(COLLEZIONE_TIT collezione);
void COLLfree(COLLEZIONE_TIT collezione);
link LISTnewNode(TITOLO val, link next);
link LISTsortIns(link h, TITOLO azione);
void LISTshow(link h);
