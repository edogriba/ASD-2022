#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "azioni.h"

struct TITOLO_s {
    char * nome;
    int valore;
    BST quotazioni_giornaliere;
};
struct collezione_titoli_s {
    link lista_valori;
    int numero_titoli;
};
struct nodo_s {
    TITOLO azione;
    link next;
};
TITOLO TITinit(void) {
    TITOLO azione = malloc(sizeof(*azione));
    azione->nome = malloc(STRMAX*sizeof(char));
    azione->valore = 0;
    azione->quotazioni_giornaliere = BSTinit();
    return azione;
}
TITOLO TITsetvoid(void) {
    TITOLO azione = malloc(sizeof(*azione));
    azione->nome = NULL;
    azione->valore = -1;
    return azione;
}
void TITfree(TITOLO azione) {
    free(azione->nome);
    BSTfree(azione->quotazioni_giornaliere);
}
TITOLO LISTSortSearch(link h, char * s) {
    link x;
    for (x=h; x!=NULL && strcmp(s, (x->azione->nome)) >= 0; x=x->next) {
        if (strcmp(s, (x->azione->nome)) == 0) {
            return x->azione;
        }
    }
    return TITsetvoid();
}
int leggiComando(void) {
    int input;
    printf("Cosa vuoi fare?\n");
    printf("Comandi disponibili [premere il numero tra parentesi: leggi_file [0], ricerca_titolo [1], ricerca_quotazione [2], ricerca_quotazione_max_min_int [3], ricerca_quotazione_max_min_totale [4], bilancia_bst_quotazioni [5], chiudi[6]]\n");
    fscanf(stdin, "%d", &input);
    return input;
}
link LISTnewNode(TITOLO val, link next) {
    link x;
    x = malloc (sizeof( *x));
    x->azione = val;
    x->next = next;
    return x;
}
link LISTsortIns(link h, TITOLO azione) {
    int i;
    link x, p;
    if (h == NULL || strcmp(azione->nome, h->azione->nome) < 0) {
        h = LISTnewNode(azione, h);
    }
    else {
        for ( x = h->next, p=h; x != NULL && strcmp( x->azione->nome, azione->nome) < 0; p=x, x = x->next );
        p->next = LISTnewNode(azione, x);
    }
    return h;
}
void LISTshow( link h) {
    link x;
    for (x = h; x->next != NULL; x=x->next) {
        printf("%s\n", x->azione->nome);
    }
    printf("%s\n", x->azione->nome);
}
COLLEZIONE_TIT COLLinit (void) {
    COLLEZIONE_TIT collezione;
    collezione = malloc(sizeof(*collezione));
    collezione->lista_valori = NULL;
    collezione ->numero_titoli =0;
    return collezione;
}
void COLLreadFile(COLLEZIONE_TIT collezione, FILE * fp) {
    int count, i, j, k, n_trans, y;
    data_t d;
    int quantita, valore;
    char * nome;
    nome = (char *) malloc (STRMAX * sizeof(char));
    fscanf(fp, "%d", &count);
    for (i=0; i<count; i++) {
        int match=0;
        fscanf(fp, "%s %d", nome, &n_trans);
        TITOLO azione = TITinit();
        strcpy(azione->nome, nome);
        if (LISTSortSearch(collezione->lista_valori, azione->nome)->valore == -1) {
            collezione->lista_valori = collezione->lista_valori = LISTsortIns(collezione->lista_valori, azione);
            collezione->numero_titoli++;
        };
        quotazione_giornaliera * vettore = malloc(n_trans* sizeof(quotazione_giornaliera));
        for ( k=0; k<n_trans; k++) {
            vettore[k].valori = malloc(n_trans * sizeof(int));
            vettore[k].quantita = malloc(n_trans * sizeof(int));
            vettore[k].transazioni = 0;
        }
        int counter = 0;
        for (j=0; j<n_trans; j++) {
            fscanf(fp, "%d/%d/%d %d:%d %d %d", &d.anno, &d.mese, &d.giorno, &d.ora, &d.minuti, &valore, &quantita);
            if ( j==0 ) {
                vettore[0].data = d;
                vettore[0].valori[vettore[k].transazioni] = valore;
                vettore[0].quantita[vettore[k].transazioni] = quantita;
                vettore[0].transazioni++;
                counter++;
            }
            else {
                for (k = 0; k < counter; k++) {
                    if (DATAcmp(vettore[k].data, d) == 0) {
                        vettore[k].valori[vettore[k].transazioni] = valore;
                        vettore[k].quantita[vettore[k].transazioni] = quantita;
                        vettore[k].transazioni++;
                        match = 1;
                        break;
                    }
                }
                if (match == 0) {
                    vettore[counter].data = d;
                    vettore[counter].valori[vettore[k].transazioni] = valore;
                    vettore[counter].quantita[vettore[k].transazioni] = quantita;
                    vettore[counter].transazioni++;
                    counter++;
                }
            }
        }
        for ( k=0; k<counter; k++ ) {
            int somma_v=0, somma_t=0;
            for( y=0; y<vettore[k].transazioni; y++ ) {
                somma_v += ( vettore[k].quantita[y] * vettore[k].valori[y] );
                somma_t +=  ( vettore[k].quantita[y] );
            }
            vettore[k].valore_eff  =somma_v/somma_t;
            TITOLO azione_in_questione = LISTSortSearch(collezione->lista_valori, azione->nome);
            if (azione_in_questione->valore != -1) {
                BSTinsertLeafR(azione_in_questione->quotazioni_giornaliere, vettore[k]);
            }
        }

    }
}
void COLLsearchTit(COLLEZIONE_TIT collezione, char * s) {
    TITOLO azione_cercata = LISTSortSearch(collezione->lista_valori, s);
    if (azione_cercata->valore != -1) {
        printf("%s è presente nella  lista dei titoli\n", azione_cercata->nome);
    }
    else {
        printf("Il titolo non è presente nella  lista dei titoli\n");
    }
}
void COLLsearchQuot(COLLEZIONE_TIT collezione, char * s) {
    TITOLO azione_cercata = LISTSortSearch(collezione->lista_valori, s);
    if ( azione_cercata->valore == -1) {
        printf("Titolo non trovato\n");
    }
    else {
        printf("In quale data vuoi cercare la quotazione di %s? [Formato aaaa/mm/gg]\n", s);
        data_t d;
        quotazione_giornaliera q;
        if (fscanf(stdin, "%d/%d/%d", &d.anno, &d.mese, &d.giorno) == 3) {
            q = BSTsearch(azione_cercata->quotazioni_giornaliere, d);
        }
        if (q.valore_eff != -1) {
            printf("La quotazione di %s in data %d/%d/%d è %d\n", azione_cercata->nome, d.anno, d.mese, d.giorno,
                   q.valore_eff);
        } else {
            printf("Non ci sono dati sulla quotazione di %s in data %d/%d/%d\n", azione_cercata->nome, d.anno, d.mese,
                   d.giorno);
        }
    }
}
void COLLsearchMinMax(COLLEZIONE_TIT collezione, char * s) {
    TITOLO azione_cercata = LISTSortSearch(collezione->lista_valori, s);
    if ( azione_cercata->valore == -1) {
        printf("Titolo non trovato\n");
    }
    else {
        data_t d1, d2;
        printf("Tra quali date vuoi cercare la quotazione di %s?\n", s);
        printf("Data 1 [Formato aaaa/mm/gg]: ");
        if (fscanf(stdin, "%d/%d/%d", &d1.anno, &d1.mese, &d1.giorno) != 3) {
            printf("Errore nell'inserimento della data\n");
            return;
        }
        printf("Data 2 [Formato aaaa/mm/gg]: ");
        if (fscanf(stdin, "%d/%d/%d", &d2.anno, &d2.mese, &d2.giorno) != 3) {
            printf("Errore nell'inserimento della data\n");
            return;
        }
        int x = 0, y = 100000000; // questi valori servono per evitare di usare una flag per impostare il massimo ed il minimo alla prima iterazione e fare tanti passaggi, si ipotizza verosimilmente che nessuna azione possa valere meno di zero o più di cento milioni
        int *max;
        int *min;
        max = &x;
        min = &y;
        BSTvisitMinMax(azione_cercata->quotazioni_giornaliere, d1, d2, max, min, 0);
        if (*max != 0 && *min != 0) {
            printf("Il massimo tra le date %d/%d/%d e %d/%d/%d è stato: %d\n", d1.anno, d1.mese, d1.giorno, d2.anno,
                   d2.mese, d2.giorno, *max);
            printf("Il minimo tra le date %d/%d/%d e %d/%d/%d è stato: %d\n", d1.anno, d1.mese, d1.giorno, d2.anno,
                   d2.mese,
                   d2.giorno, *min);
        } else {
            printf("Non sono state trovate quotazioni nelle date cercate\n");
        }
    }
}
void COLLsearchMinMaxTot(COLLEZIONE_TIT collezione, char * s) {
    TITOLO azione_cercata = LISTSortSearch(collezione->lista_valori, s);
    if ( azione_cercata->valore == -1) {
        printf("Titolo non trovato\n");
    }
    else {
        data_t d1, d2;
        int x = 0, y = 100000000;
        int *max;
        int *min;
        max = &x;
        min = &y;
        BSTvisitMinMax(azione_cercata->quotazioni_giornaliere, d1, d2, max, min, 1);
        if (*max != 0 && *min != 0) {
            printf("Il massimo tra le quotazioni è stato: %d\n", *max);
            printf("Il minimo tra le quotazioni è stato: %d\n", *min);
        }
    }

}
void COLLBalance( COLLEZIONE_TIT collezione, char * s, int S) {
    TITOLO azione_cercata = LISTSortSearch(collezione->lista_valori, s);
    if ( azione_cercata->valore == -1) {
        printf("Titolo non trovato\n");
    }
    else {
        if (BSTheight(azione_cercata->quotazioni_giornaliere) > S) {
            BSTbalance(azione_cercata->quotazioni_giornaliere);
            printf("Albero delle quotazioni ribilanciato\n");
        }
        else {
            printf("Ribilanciamento non necessario, l'altezza dell'albero é sotto la soglia data\n");
        }
    }
}
void COLLshow(COLLEZIONE_TIT collezione) {
    printf("La lista dei titoli è la seguente: \n");
    LISTshow(collezione->lista_valori);
}
void COLLfree(COLLEZIONE_TIT collezione) {
    link p;
    for ( p= collezione->lista_valori; p->next!= NULL; p= p->next) {
        TITfree(p->azione);
    }
    TITfree(p->azione);
}
