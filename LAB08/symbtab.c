#include "symbtab.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct symbtab_s {
    char ** vettore;
    int N;
    int M;
} symbtab_t;

ST STinit(int maxN) {
    ST st;
    int i;
    st = malloc( sizeof(symbtab_t));
    st->M=maxN;
    st->N=0;
    st->vettore = (char ** )malloc(st->M * sizeof(char * ));
    for (i=0; i<st->M; i++) {
        st->vettore[i] = (char *) malloc(STRMAX * sizeof(char));
    }
    return st;
}
int STfill(ST st, char * nome) {
    int i;
    if (st->N == st->M ) {
        st-> M *= 2;
        st->vettore = (char **) realloc(st->vettore, st->M);
        for (i=0; i<st->N; i++) {
            st->vettore[i] = (char *) realloc ( st->vettore[i], STRMAX);
        }
        for (i=st->N; i<st->M; i++) {
            st->vettore[i] = (char *) malloc ( STRMAX* sizeof(char));
        }
    }
    strcpy(st->vettore[st->N], nome);
    st->N++;
    return st->N-1;
}
int STsearch(ST st, char * nome) {
    int i;
    for (i=0; i<st->N; i++) {
        if ( strcmp(nome, st->vettore[i]) == 0) {
            return i;
        }
    }
    return -1;
}
void STread(ST st, FILE * fp) {
    int a, b;
    char * s1;
    char * s2;
    s1 = malloc(STRMAX * sizeof(char));
    s2 = malloc(STRMAX * sizeof(char));
    while ( fscanf(fp, "%s %*s %s %*s %*d", s1, s2) == 2) {
        a = STsearch(st, s1);
        if (a == -1) {
            a = STfill(st, s1);
        }
        b = STsearch(st, s2);
        if (b == -1) {
            b = STfill(st, s2);
        }
    }
    free(s1);
    free(s2);
}

int STcount(ST st) {
    return st->N;
}
void STprintNodeName(ST st, int i) {
    printf("%s ", st->vettore[i]);
}
void STfree(ST st) {
    int i;
    for (i=0; i<st->M; i++) {
        free(st->vettore[i]);
    }
    free(st->vettore);
    free(st);
}
void MergeSort(int A[], int B[], int N, ST st) {
    int l=0, r=N-1;
    MergeSortR(A, B, l, r, st);
}
void MergeSortR(int A[], int B[], int l, int r, ST st) {
    int q;
    if (l >= r)
        return;
    q = (l + r)/2;
    MergeSortR(A, B, l, q,  st);
    MergeSortR(A, B, q+1, r,  st);
    Merge(A, B, l, q, r,  st);
}
void Merge(int A[], int B[], int l, int q, int r, ST st) { int i, j, k;
    i = l;
            j = q+1;
    for (k = l; k <= r; k++) {
        if (i > q) {
            B[k] = A[j++];
        }
        else if (j > r) {
            B[k] = A[i++];
        }
        else if (strcmp(st->vettore[A[i]], st->vettore[A[j]]) <= 0) {
            B[k] = A[i++];
        }
        else {
            B[k] = A[j++];
        }
    }
    for ( k = l; k <= r; k++ ) {
        A[k] = B[k];
    }
}