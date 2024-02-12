#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int verticesx;
    int verticedx;
} arco;

arco * readAndAllocateData(int * N, int * E);
void freeData(arco * vettore);
int powerset(int *val, int n, int *sol, arco * vettore_archi);
int powerset_r(int* val, int n, int *sol, int j, int pos,int start, arco * vettore_archi);
void checkVertex( int * vettore, int lunghezza_vettore, arco * vettore_archi, int n, int * vettore_coppie);
int check(int * vettore, int lunghezza_vettore, arco * vettore_archi, int n);

int main() {
    int N, E, i;
    arco * vect_archi;
    vect_archi = readAndAllocateData(&N, &E);
    int * valori;
    int * soluzioni;
    valori = (int *) malloc(N*sizeof(int));
    for (i=0; i<N; i++) {
        valori[i] = i;
    }
    soluzioni = (int *) malloc(N*sizeof(int));
    printf("I vertex cover del grafo dato sono i seguenti: \n");
    powerset(valori, N, soluzioni, vect_archi);
    freeData(vect_archi);
    free(soluzioni);
    free(valori);
    return 0;
}
arco * readAndAllocateData(int * N, int * E) {
    FILE *fp;
    arco *vect_archi;
    int i;
    fp = fopen("grafo.txt", "r");
    if (fp == NULL) {
        printf("Problemi nell'apertura del file");
        exit(1);
    }
    fscanf(fp, "%d %d", N, E);
    vect_archi = (arco *) malloc(*E * sizeof(arco) );
    for (i=0; i<*E; i++) {
        fscanf(fp, "%d %d", &(vect_archi[i].verticesx), &(vect_archi[i].verticedx));
    }
    fclose(fp);
    return &vect_archi[0];
}
void freeData(arco * vettore) {
    free(vettore);
}
int powerset(int *val, int n, int *sol, arco * vettore_archi){
    int cnt = 0, j;
    for(j = 1; j <= n; j++) {
        cnt += powerset_r(val, n, sol, j, 0, 0, vettore_archi);
    }
    return cnt;
}
int powerset_r(int * val, int n, int *sol, int j, int pos, int start, arco * vettore_archi) {
    int cnt = 0, i;
    if (pos >= j) {
        if (check(sol, j, vettore_archi, n)) {
            printf("{ ");
            for (i = 0; i < j; i++) {
                printf("%d ", sol[i]);
            }
            printf("}\n");
            return 1;
        }
    }
    for (i = start; i < n; i++){
        sol[pos] = val[i];
        cnt += powerset_r(val, n, sol, j, pos+1, i+1, vettore_archi);
    }
    return cnt;
}
int check(int * vettore, int lunghezza_vettore, arco * vettore_archi, int n) {
    int * vettore_soluzioni;
    int i;
    vettore_soluzioni = (int *) calloc(n, sizeof(int));
    checkVertex( vettore, lunghezza_vettore, vettore_archi, n, vettore_soluzioni);
    for ( i=0; i<n; i++){
        if( vettore_soluzioni[i] == 0) {
            return 0;
        }
    }
    free(vettore_soluzioni);
    return 1;
}
void checkVertex( int * vettore, int lunghezza_vettore, arco * vettore_archi, int n, int * vettore_coppie) {
    int i, j;
    for ( i=0; i<n; i++) {
        for (j=0; j<lunghezza_vettore; j++) {
            if (vettore_archi[i].verticesx == vettore[j] || vettore_archi[i].verticedx == vettore[j]) {
                vettore_coppie[i] = 1;
            }
        }
    }
}