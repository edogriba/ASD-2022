#include <stdio.h>
#include <stdlib.h>



void ottieniValore(int * pietra);
int fZ (int z,  int r, int t, int s, char *sol, int ** memo, int pos, int cnt);
int fS (int z,  int r, int t, int s, char *sol, int ** memo, int pos, int cnt);
int fT (int z,  int r, int t, int s, char *sol, int ** memo, int pos, int cnt);
int fR (int z,  int r, int t, int s, char *sol, int ** memo, int pos, int cnt);
int max (int a, int b, int c, int d);
int ** allocMemoize(int ** vettore, int n);
void freeMemoizer(int ** vettore, int n);

int main (void) {
    int zaffiri=0, rubini=1, topazi=2, smeraldi=3;
    int totale, massimo;
    ottieniValore(&zaffiri);
    ottieniValore(&rubini);
    ottieniValore(&topazi);
    ottieniValore(&smeraldi);
    totale = zaffiri+rubini+topazi+smeraldi;
    massimo = max(zaffiri, rubini, topazi, smeraldi);
    printf("Totale pietre preziose disponibili per la collana: %d\n", totale);
    char * soluzioni0 = (char *) malloc(totale * sizeof(char));
    char * soluzioni1 = (char *) malloc(totale * sizeof(char));
    char * soluzioni2 = (char *) malloc(totale * sizeof(char));
    char * soluzioni3 = (char *) malloc(totale * sizeof(char));
    int ** memoizer;
    memoizer = allocMemoize(memoizer, 1000*massimo + 100*massimo + 10*massimo +massimo  );
    if (totale == 0) {
        printf("Nessuna perlina disponibile, non è possibile costruire alcun tipo di collana\n");
    }
    else {
        printf("La massima lunghezza della collana possibile con i filtri prestabiliti e le perline disponibili è la seguente: \n");
        printf("%d", max(fZ(zaffiri, rubini, topazi, smeraldi, soluzioni0, memoizer, 0,  0), fS(zaffiri, rubini, topazi, smeraldi, soluzioni1, memoizer, 0,  0), fT(zaffiri, rubini, topazi, smeraldi, soluzioni2, memoizer, 0,  0), fR(zaffiri, rubini, topazi, smeraldi, soluzioni3, memoizer, 0,  0)));
    }
    free(soluzioni0);
    free(soluzioni1);
    free(soluzioni2);
    free(soluzioni3);
    freeMemoizer(memoizer, 1000*massimo + 100*massimo + 10*massimo +massimo);
    return 0;

}
void ottieniValore(int * pietra) {
    switch (*pietra) {
        case 0:
            printf("Quanti zaffiri vuoi nella tua collana?\n");
            scanf("%d", pietra);
            break;
        case 1:
            printf("Quanti rubini vuoi nella tua collana?\n");
            scanf("%d", pietra);
            break;
        case 2:
            printf("Quanti topazi vuoi nella tua collana?\n");
            scanf("%d", pietra);
            break;
        case 3:
            printf("Quanti smeraldi vuoi nella tua collana?\n");
            scanf("%d", pietra);
            break;
    }
}
int ** allocMemoize(int ** vettore, int n) {
    int i, j;
    vettore = (int **) malloc ( 4 * sizeof(int *));
    for ( i=0; i<4; i++) {
        vettore[i] = (int *) malloc(n*sizeof(int));
        for (j=0; j<n; j++) {
            vettore[i][j] = -1;
        }
    }
    return vettore;
}
void freeMemoizer(int ** vettore, int n) {
    int i;
    for ( i=0; i<4; i++) {
        free(vettore[i]);
    }
    free(vettore);
}
int max (int a, int b, int c, int d) {
    switch (0) {
        case 0:
            if (a >= b && a >= c && a >= d) {
                return a;
            }
        case 1:
            if (b >= a && b >= c && b >= d) {
                return b;
            }
        case 2:
            if (c >= b && c >= a && c >= d) {
                return c;
            }
        case 3:
            if (d >= a && d >= c && d >= b) {
                return d;
            }
        default:
            return NULL;
    }
}
int fZ (int z, int r, int t, int s, char *sol, int ** memo, int pos, int cnt) {
    if ( z == 0 && r ==0 && t==0 && s==0 ) {
        return 1;
    }
    else if ( z==0 ) {
        return cnt;
    }
    if (memo[0][z+10*r+100*t+1000*s] != -1) {
        return memo[0][z+10*r+100*t+1000*s];
    }
    sol[pos] = 'z';
    z--;
    if (z>0){

        cnt = fZ(z, r, t, s, sol, memo, pos + 1, cnt + 1);
    }
    else if (r >0){
        cnt = fR(z, r, t, s, sol, memo, pos + 1, cnt + 1);
    }
    else {
        cnt++;
    }
    memo[0][(z+1)+10*r+100*t+1000*s] = cnt;
    return cnt;
}
int fS (int z, int r, int t, int s, char *sol, int ** memo, int pos, int cnt) {
    if ( z == 0 && r ==0 && t==0 && s==0  ) {
        return 1;
    }
    else if ( s==0) {
        return cnt;
    }
    if (memo[1][z+10*r+100*t+1000*s] != -1) {
        return memo[1][z+10*r+100*t+1000*s];
    }
    sol[pos] = 's';
    s--;
    if (s>0){
        cnt = fS(z, r, t, s, sol, memo, pos + 1, cnt+1);
    }
    else if (t>0){
        cnt = fT(z, r, t, s, sol, memo, pos + 1, cnt+1);
    }
    else {
        cnt++;
    }
    memo[1][z+10*r+100*t+1000*(s+1)] = cnt;
    return cnt;
};

int fT (int z, int r, int t, int s, char *sol, int ** memo, int pos, int cnt) {
    if (  z == 0 && r ==0 && t==0 && s==0  ) {
        return 1;
    }
    else if ( t==0) {
        return cnt;
    }
    if (memo[2][z+10*r+100*t+1000*s] != -1) {
        return memo[2][z+10*r+100*t+1000*s];
    }
    sol[pos] = 't';
    t--;
    if (z>0){
        cnt = fZ(z, r, t, s, sol, memo, pos + 1, cnt+1);
    }
    else if (r>0){
        cnt = fR(z, r, t, s, sol, memo, pos + 1, cnt+1);
    }
    else {
        cnt++;
    }
    memo[2][z+10*r+100*(t+1)+1000*s] = cnt;
    return cnt;
}
int fR (int z, int r, int t, int s, char *sol, int ** memo, int pos, int cnt) {
    if (  z == 0 && r ==0 && t==0 && s==0  ) {
        return 1;
    }
    else if ( r==0) {
        return cnt;
    }
    if (memo[3][z+10*r+100*t+1000*s] != -1) {
        return memo[3][z+10*r+100*t+1000*s];
    }
    sol[pos] = 'r';
    r--;
    if (s > 0 ) {
        cnt = fS(z, r, t, s, sol, memo, pos + 1, cnt+1);
    }
    else if ( t>0) {
        cnt = fT(z, r, t, s, sol, memo, pos + 1, cnt+1);
    }
    else {
        cnt++;
    }
    memo[3][z+10*(r+1)+100*t+1000*s] = cnt;
    return cnt;
}
