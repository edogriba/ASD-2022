#include <stdio.h>
#include <stdlib.h>

int nr, nc;

int ** ReadAlloc(FILE * fp);
void separa(int ** mat, int nrighe, int ncolonne, int ** bianchi, int ** neri);
void showVect(int * vect, int n);

int main(void) {
    FILE * filename;
    int ** pointer;
    filename = fopen("mat.txt", "r");
    pointer = ReadAlloc(filename);
    int * caselle_bianche;
    int * caselle_nere;
    caselle_bianche = (int *) malloc(sizeof(int));
    caselle_nere = ( int *) malloc(sizeof(int));
    if (caselle_bianche == NULL || caselle_nere == NULL) {
        exit(1);
    }
    separa(pointer, nr, nc, &caselle_bianche, &caselle_nere);
    printf("Le caselle bianche sono: ");
    if ((nr * nc)%2 == 0) {
        showVect(caselle_bianche, ( (nr * nc) / 2));
        printf("\n");
    }
    else {
        showVect(caselle_bianche, ( ((nr * nc) / 2) + 1));
        printf("\n");
    }
    printf("Le caselle nere sono: ");
    showVect(caselle_nere, ((int)nr * nc)/2);
    free(caselle_nere);
    free(caselle_bianche);
    fclose(filename);
    return 0;
}

int ** ReadAlloc(FILE * fp) {
    int i, j;
    int **p;
    fscanf(fp, "%d %d", &nr, &nc);
    p = (int **) malloc(nr*sizeof( int *));
    for (i=0; i<nr; i++) {
        p[i] = (int *) malloc(nc*sizeof(int));
        for (j=0; j<nc; j++) {
            fscanf(fp, "%d", &p[i][j]);
        }
    }
    for (i=0; i<nr; i++) { // printing just to check if I stored it well
        for ( j=0; j<nc; j++) {
            printf("%d ", p[i][j]);
        }
        printf("\n");
    }
    return p;
}
void separa(int ** mat, int nrighe, int ncolonne, int ** bianchi, int ** neri) {
    int counter_bianchi=0, counter_neri=0;
    int lunghezza_bianchi = 1;
    int lunghezza_neri = 1;
    int i, j;
    for (i=0; i<nrighe; i++) {
        for (j=0; j<ncolonne; j++) {
            if ((i+j) % 2 == 0) {
                if (counter_bianchi+1 > lunghezza_bianchi) {
                    lunghezza_bianchi =2*lunghezza_bianchi;
                    *bianchi = (int *)realloc(*bianchi, lunghezza_bianchi*sizeof(int));
                    if (*bianchi == NULL) {
                        exit(1);
                    }
                    (*bianchi)[counter_bianchi] = mat[i][j];
                }
                else {
                    (*bianchi)[counter_bianchi] = mat[i][j];
                }
                counter_bianchi++;
            }
            else {
                if (counter_neri+1 > lunghezza_neri) {
                    lunghezza_neri = 2*lunghezza_neri;
                    *neri = (int *)realloc(*neri, lunghezza_neri*sizeof(int));
                    if (*neri == NULL) {
                        exit(1);
                    }
                    (*neri)[counter_neri] = mat[i][j];
                }
                else {
                    (*neri)[counter_neri] = mat[i][j];
                }
                counter_neri++;
            }
        }
    }
}
void showVect(int * vect, int n) {
    int i;
    for (i=0; i<n; i++) {
        printf("%d ", vect[i]);
    }
}