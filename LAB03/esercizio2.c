#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NMAX 255

typedef struct  {
    int numero_canzoni;
    int *scelte;
} Amico;

int princ_molt(int pos, Amico *val, int *sol, int k, int count, char buffer[]);

int main(void) {
    int i, j, k=0, A, total;
    int *sol;
    FILE * fp;
    fp = fopen("brani.txt", "r");
    fscanf(fp, "%d", &A);
    Amico * vettore_amici;
    vettore_amici = (Amico *) malloc(A * sizeof(Amico));
    char buffer[NMAX*A*5]; // buffer unico sovradimensionato
    char canzone[NMAX];
    for ( i=0; i<A; i++) {
        fscanf(fp, "%d", &(vettore_amici[i].numero_canzoni));
        vettore_amici[i].scelte = (int *) malloc((vettore_amici[i].numero_canzoni)*sizeof(int));
        for (j=0; j < vettore_amici[i].numero_canzoni; j++) {
            fscanf(fp, "%s", canzone);
            strcat(canzone, "|\0");
            if (j==0 && i==0)
            {
                strcpy(buffer, canzone);
            }
            else {
                strcat(buffer, canzone);
            }
            vettore_amici[i].scelte[j] = k;
            k = k + (int) strlen(canzone);
        }

    }
    fclose(fp);
    sol = (int *) malloc(A*sizeof(int ));
    printf("Tutte le playlist possibili sono: \n\n");
    total = princ_molt(0, vettore_amici, &sol[0], A, 0, &buffer[0]);
    printf("In totale le playlist possibili sono %d \n", total);
    free(sol);
    for (i = 0; i < A; i++)
        free(vettore_amici[i].scelte);
    free(vettore_amici);

    return 0;
}


int princ_molt(int pos, Amico *val, int *sol, int k, int count, char buffer[]) {
    int i;
    if (pos >= k) {
        for (i = 0; i < k; i++) {
            int s=0;
            printf("Canzone amico %d: ", i+1);
            while (buffer[sol[i]+s] != '|') {
                printf("%c", buffer[sol[i] + s]);
                s++;
            }
            printf("\n");
        }
        printf("--------------------------------------------\n");
        return count+1;
    }
    for (i = 0; i < val[pos].numero_canzoni; i++) {
        sol[pos] = val[pos].scelte[i];
        count = princ_molt(pos+1, val, sol, k, count, buffer);
    }
    return count;
}
