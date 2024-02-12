#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int inizio;
    int fine;
} att;

att * getInput(int n);
void powerset_r(att * val, int n, att *sol, int j, int pos, int start, int *max, att * migliore, int * lunghezza_migliore);
void powerset(att *val, int n, att *sol, int * max, att * migliore, int * lunghezza_migliore);
int independenceCheckerATT( att * v, int lunghezza);
int valueCalculatorATT(att * v, int lunghezza);
void attSel(int N, att *v);
void copiaATT(att * v1, att * v2, int j);

int main() {
    int num;
    printf("Quante attività ci sono?\n");
    scanf("%d", &num);
    att * v;
    v = getInput(num);
    attSel(num, v);
    free(v);
    return 0;
}

att * getInput(int n) {
    int i;
    att * v;
    v = (att *) malloc (n*sizeof(att));
    for (i=0; i<n; i++) {
        printf("Inizio attività numero %d: \n", i+1);
        scanf("%d", &(v[i].inizio));
        printf("Fine attività numero %d: \n", i+1);
        scanf("%d", &(v[i].fine));
    }
    return v;
}

void attSel(int N, att *v) {
    int i;
    int *mark = (int *) malloc(N * sizeof(int));
    att *sol = (att *) malloc(N * sizeof(att));
    att * migliore = (att *) malloc(N * sizeof(att));
    int max=0;
    int lunghezza_migliore=0;
    powerset(v, N, sol, &max, migliore, &lunghezza_migliore);
    free(sol);
    free(migliore);
    free(mark);
}
void copiaATT(att * v1, att * v2, int j) {
    int i;
    for (i=0; i<j; i++) {
        v2[i].inizio = v1[i].inizio;
        v2[i].fine = v1[i].fine;
    }
}
void powerset(att *val, int n, att *sol, int * max, att * migliore, int * lunghezza_migliore){
    int  j, i;
    printf("Tutte le partizioni possibili sono:\n");
    for (j = 1; j <= n; j++) {
        powerset_r(val, n, sol, j, 0, 0, max, migliore, lunghezza_migliore);

    }
    printf("Uno dei sottoinsiemi di attività compatibili che massimizza la durata è il seguente \n");
    printf("{ ");
    for (i = 0; i < *lunghezza_migliore; i++) {
        printf("(%d %d) ", migliore[i].inizio, migliore[i].fine);
    }
    printf("}\n");
    printf("La cui durata massima è %d\n", *max);
}
void powerset_r(att * val, int n, att *sol, int j, int pos, int start, int * max, att * migliore, int  * lunghezza_migliore) {
    int i;
    if (pos >= j) {
        printf("{ ");
        for (i = 0; i < j; i++) {
            printf("(%d %d) ", sol[i].inizio, sol[i].fine);
        }
        printf("}\n");
        if (independenceCheckerATT(sol, j) && valueCalculatorATT(sol, j) >= *max) {
            *max = valueCalculatorATT(sol, j);
            copiaATT( sol, migliore, j);
            *lunghezza_migliore = j;
        }
        return;
    }
    for (i = start; i < n; i++) {
        if ( i == 0) {
            sol[pos] = val[i];
            powerset_r(val, n, sol, j, pos + 1, i + 1, max, migliore, lunghezza_migliore);
        }
        else {
            if (independenceCheckerATT(sol, pos)) {
                sol[pos] = val[i];
                powerset_r(val, n, sol, j, pos + 1, i + 1, max, migliore, lunghezza_migliore);
            }
        }
    }
}
int independenceCheckerATT( att * v, int lunghezza) {
    int i;
    for (i=0; i<lunghezza-1; i++) {
        if (v[i].fine > v[i+1].inizio) {
            return 0;
        }
    }
    return 1;
}
int valueCalculatorATT(att * v, int lunghezza) {
    int i, count=0;
    for (i=0; i<lunghezza; i++) {
        count += (v[i].fine - v[i].inizio);
    }
    return count;
}

