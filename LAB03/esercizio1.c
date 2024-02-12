#include <stdio.h>
#include <stdlib.h>

void majority(int * vect, int N);
void Recursion(int * vect, int l, int r );

int *vector_counter;

int main (void) {
    int n, i=0, flag=1, max, first=1;
    printf("Quanti elementi ha il tuo vettore?\n");
    scanf("%d", &n);

    int vettore[n-1];
    while (i<n) {
        printf("Elemento numero %d \n", i+1);
        if (scanf("%d", &vettore[i]) != 1) {
            printf("Input errato");
            exit(1);
        }
        i++;
    }
    for ( i=0; i<n; i++) {
        if (first) {
            max = vettore[i];
            first = 0;
        }
        else {
            if (max < vettore[i]) {
                max = vettore[i];
            }
        }
    }
    vector_counter = (int *) malloc(max*sizeof(int));
    if (vector_counter == NULL) {
        printf("Troppa poca memoria");
        exit(1);
    }
    majority(vettore, n);
    for (i=0; i<max; i++) {
        if ((float)(vector_counter[i]) > (float)(n/2) ) {
            printf("%d è l'elemento maggioritario del vettore dato", i);
            flag=0;
        }
    }
    if (flag==1) {
        printf("Non esiste maggioritario");
    }
    return 0;
}

void Recursion(int * vect, int l, int r ) {
    int m;
    if (l > r || l == r) {
        vector_counter[vect[l]]++;
    }
    else {
        m = (r+l)/2;
        Recursion(vect, l, m);
        Recursion(vect, m+1, r);
    }
}
void majority(int * vect, int N) {
    int left= 0, right=N-1;
    Recursion(vect, left, right);
}