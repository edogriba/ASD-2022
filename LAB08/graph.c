#include "symbtab.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct graph {
    int numero_archi;
    int numero_vertici;
    int ** matrix;
    link * adj_list;
    link sentinella;
};

struct node {
    int value;
    link next;
};

static link NEW(int v, link next) {
    link x = (link) malloc(sizeof (*x));
    x->value = v;
    x->next = next;
    return x;
}
void showList(link head, ST st) {
    while (head->value != -1) {
        STprintNodeName(st, head->value);
        head = head->next;
    }
}
int searchList(link head, int i) {
    while (head->value != -1) {
        if (head->value == i ) {
            return 1;
        }
        head = head->next;
    }
    return 0;
}

GRAPH GRAPHinitialize(GRAPH G, ST st) {
    int i, j;
    G = (GRAPH) malloc (sizeof(struct graph));
    G->numero_vertici = 0;
    G->numero_archi = 0;
    G->matrix = (int **) malloc(STcount(st) * sizeof(int*));
    for (i=0; i<STcount(st); i++) {
        (G->matrix)[i] = (int *) malloc( STcount(st) * sizeof(int));
    }
    return G;
}
void GRAPHgenerateAdjList(GRAPH G, ST st) {
    int i, j;
    int count = STcount(st);
    G->adj_list = malloc(count * sizeof(link));
    G->sentinella = NEW(-1,  NULL);
    for (i = 0; i < G->numero_vertici; i++) {
        G->adj_list[i] = G->sentinella;
    }
    for (i=0; i<count; i++) {
        for ( j=0; j<count; j++) {
            if (G->matrix[i][j] != 0 ) {
                G->adj_list[i] = NEW(j, G->adj_list[i]);
            }
        }
    }
}
void GRAPHshowListAdj(GRAPH G, ST st) {
    int i, count;
    count = STcount(st);
    for ( i=0; i<count; i++) {
        STprintNodeName(st, i);
        printf("-> ");
        showList(G->adj_list[i], st);
        printf("\n");
    }
}
void GRAPHread (GRAPH G, ST st) {
    int i;
    char * s1, * s2;
    FILE * fp;
    s1 = malloc(STRMAX * sizeof(char));
    s2 = malloc(STRMAX * sizeof(char));
    int a, b, w;
    G->numero_vertici =  STcount(st);
    fp = fopen("grafo.txt", "r");
    while ( fscanf(fp, "%s Net%*d %s Net%*d %d", s1, s2, &w) == 3) {
        a = STsearch(st, s1);
        b = STsearch(st, s2);
        G->matrix[a][b] = w;
        G->matrix[b][a] = w;
        G->numero_archi++;
    }
    fclose(fp);
    free(s1);
    free(s2);
}
void GRAPHstore(GRAPH G) {
    int i, j;
    for (i=0; i<G->numero_vertici; i++) {
        for ( j=0; j<G->numero_vertici; j++) {
            printf("%3d ", G->matrix[i][j]);
        }
        printf("\n");
    }
}
void GRAPHlistVert(GRAPH G, ST st) {
    int i, j, k, counter=0;
    int * vettore;
    int * vettore_copia;
    int * vettore_nodi;
    vettore_nodi = (int *) malloc ( G->numero_vertici * sizeof(int));
    vettore_copia = (int *) malloc ( G->numero_vertici * sizeof(int));
    vettore = (int *) malloc ( G->numero_vertici * sizeof(int));
    for (i=0; i<G->numero_vertici; i++) {
        vettore[i] = i;
        vettore_copia[i]= 0;
    }
    MergeSort(vettore, vettore_copia, G->numero_vertici, st);
    for (i=0; i<G->numero_vertici; i++) {
        counter = 0;
        STprintNodeName(st, vettore[i]);
        printf("\n");
        for (j=0; j<G->numero_vertici; j++ ) {
            if (G->matrix[j][vettore[i]] != 0) {
                vettore_nodi[counter] = j;
                counter++;
            }
        }
        MergeSort(vettore_nodi, vettore_copia, counter, st);
        for (k=0; k<counter; k++) {
            STprintNodeName(st, vettore_nodi[k]);
            STprintNodeName(st, vettore[i]);
            printf("%d", G->matrix[vettore[i]][vettore_nodi[k]]);
            printf("\n");
        }
        printf("\n");
    }
    free(vettore);
    free(vettore_copia);
}

int GRAPHverifyMatAdj(GRAPH G, ST st) {
    int a, b, c;
    char *s1, *s2, *s3;
    s1 = (char * ) malloc (STRMAX * sizeof(char ));
    s2 = (char * ) malloc (STRMAX * sizeof(char ));
    s3 = (char * ) malloc (STRMAX * sizeof(char ));
    printf("Come si chiama il primo nodo?\n");
    scanf("%s", s1);
    printf("Come si chiama il secondo nodo?\n");
    scanf("%s", s2);
    printf("Come si chiama il terzo nodo?\n");
    scanf("%s", s3);
    a = STsearch(st, s1);
    b = STsearch(st, s2);
    c = STsearch(st, s3);
    if ( a != -1 && b != -1 && c!= -1 ) {
        if ((G->matrix[a][b] != 0 && G->matrix[a][c] != 0 ) || (G->matrix[b][c] && G->matrix[b][a] != 0) || ( G->matrix[c][a] && G->matrix[c][b] != 0 )){
            return 1;
        }
    }
    else {
        printf("Almeno un nodo non è stato trovato\n");
    }
    return 0;
}
int GRAPHverifyListAdj(GRAPH G, ST st) {
    int a, b, c;
    char *s1, *s2, *s3;
    s1 = (char * ) malloc (STRMAX * sizeof(char ));
    s2 = (char * ) malloc (STRMAX * sizeof(char ));
    s3 = (char * ) malloc (STRMAX * sizeof(char ));
    printf("Come si chiama il primo nodo?\n");
    scanf("%s", s1);
    printf("Come si chiama il secondo nodo?\n");
    scanf("%s", s2);
    printf("Come si chiama il terzo nodo?\n");
    scanf("%s", s3);
    a = STsearch(st, s1);
    b = STsearch(st, s2);
    c = STsearch(st, s3);
    if ( a != -1 && b != -1 && c!= -1 ) {
        if ((searchList(G->adj_list[a], b) && (searchList(G->adj_list[b], c) ) ) || ((searchList(G->adj_list[b], c) && (searchList(G->adj_list[b], a)))) || ((searchList(G->adj_list[c], a) && (searchList(G->adj_list[c], b)) ))){
            return 1;
        }
    }
    else {
        printf("Almeno un nodo non è stato trovato\n");
    }
    return 0;
}
void GRAPHshow(GRAPH G, ST st) {
    printf("Il grafo ha %d archi\n", G->numero_archi);
    printf("Il grafo ha %d vertici\n", G->numero_vertici);
    printf("La matrice di adiacenze è\n");
    GRAPHstore(G);
    printf("L'elenco dei vertici in ordine alfabetico è: \n");
    GRAPHlistVert(G, st);
}

void GRAPHfree(GRAPH G) {
    int i;
    for (i=0; i<G->numero_vertici; i++) {
        free(G->matrix[i]);
    }
    free(G->matrix);
    free(G);
}

