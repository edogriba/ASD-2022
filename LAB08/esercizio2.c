#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "symbtab.h"
int main() {
    GRAPH G;
    ST st;
    FILE * fp;
    int listAdj = 0;
    char * input;
    input = (char *) malloc(STRMAX*sizeof(char));
    st = STinit(1);
    fp = fopen("grafo.txt", "r");
    STread(st , fp);
    fclose(fp);
    G = GRAPHinitialize(G, st);
    GRAPHread(G, st);
    GRAPHshow(G, st);
    printf("Vuoi generare la lista di adiacenza del grafo? [ y / n ] ?\n");
    scanf("%s", input);
    if (strncmp(input, "y", 1) == 0) {
        GRAPHgenerateAdjList(G, st);
        GRAPHshowListAdj(G, st);
        listAdj = 1;
    }
    printf("Vuoi verificare l'adiacenza di 3 nodi [ y / n ] ?\n");
    scanf("%s", input);
    while (strncmp(input, "y", 1) == 0) {
        switch (listAdj) {
            case 0:
                if (GRAPHverifyMatAdj(G, st)) {
                    printf("I 3 nodi sono adiacenti\n");
                }
                else {
                    printf("I 3 nodi non sono adiacenti\n");
                }
                break;
            case 1:
                if (GRAPHverifyListAdj(G, st)) {
                    printf("I 3 nodi sono adiacenti\n");
                }
                else {
                    printf("I 3 nodi non sono adiacenti\n");
                }
                break;
        }
        printf("Vuoi verificare l'adiacenza di 3 nodi [ y / n ] \n");
        scanf("%s", input);
    }
    free(input);
    GRAPHfree(G);
    STfree(st);
    return 0;
}
