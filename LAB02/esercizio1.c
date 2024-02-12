#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b);
int main() {
    int i, j, z, w;
    printf("Numero 1: ");
    z = scanf("%d", &i);
    if ( z != 1 ) {
        printf("Il dato inserito numero 1 non va bene");
        exit(1);
    }
    printf("Numero 2: ");
    w = scanf("%d", &j);
    if ( w != 1 ) {
        printf("Il dato inserito numero 2 non va bene");
        exit(1);
    }
    else if (i > 0 && j> 0) {
        printf("Il massimo comun divisore di %d e %d è %d", i, j, gcd(i, j));
    }
    else {
        printf("I dati inseriti devono essere maggiori di zero");
    }
    return 0;
}
int gcd( int a, int b) {
    if ( a % b < 0.1 ) {
        return b;
    }
    else if (a % 2 == 0 && b % 2 == 0) {
        return 2*gcd(a/2, b/2);
    }
    else if (a % 2 == 1 && b % 2 == 0) {
        return gcd(a, b/2);
    }
    else if (a % 2 == 1 && b % 2 == 1) {
        if ((a-b)/2 < b) {
            return gcd(b, (a-b)/2);
        }
        else {
            return gcd((a-b)/2, b);
        }
    }
    else if (a % 2 == 0 && b % 2 == 1) {
        if ( a/2 > b) {
            return gcd(a/2, b);
        }
        else {
            return gcd(b, a/2);
        }
    }
}