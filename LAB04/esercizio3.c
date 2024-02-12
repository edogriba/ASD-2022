#include <stdio.h>
#include <stdlib.h>


void ottieniValore(int * pietra);
int perm_rip_tutte(int pos, char *dist_val, char *sol, int *mark, int n, int n_dist, int cnt);
int perm_rip_una_sola(int pos, char *dist_val, char *sol, int *mark, int n, int n_dist, int count);
int check ( char * vettore, int lunghezza);
int Filter1(char * vettore, int lunghezza);
int Filter2(char * vettore, int lunghezza);
int leggiComando(void);
int main (void) {
    int zaffiri=0, rubini=1, topazi=2, smeraldi=3, n_distinti = 4;
    int totale, count=0, i, comando, p;
    ottieniValore(&zaffiri);
    ottieniValore(&rubini);
    ottieniValore(&topazi);
    ottieniValore(&smeraldi);
    totale = zaffiri+rubini+topazi+smeraldi;
    printf("Totale pietre preziose disponibili per la collana: %d\n", totale);
    char * soluzioni = (char *) malloc(totale * sizeof(char));
    char * distinti = (char *) malloc(4 * sizeof(char));
    int * mark = (int *) malloc(4 * sizeof(int));
    distinti[0]  = 'z';
    distinti[1] = 'r';
    distinti[2] = 't';
    distinti[3] = 's';
    mark[0]  = zaffiri;
    mark[1] = rubini;
    mark[2] = topazi;
    mark[3] = smeraldi;
    if (totale == 0) {
        printf("Nessuna perlina disponibile, non è possibile costruire alcun tipo di collana\n");
    }
    else {
        comando = leggiComando();
        if ( comando == 1) {
            printf("Le varie collane di lunghezza massima possibile con i filtri prestabiliti sono le seguenti: \n");
            for (i = 0; i <totale ; i++) {
                p = perm_rip_tutte(0, distinti, soluzioni, mark, i, n_distinti, 0);
                if ( p > count) {
                    count = p;
                }
                if (count != 0) {
                    printf("Le collane sono tutte di lunghezza massima %d e in totale sono: %d\n", i, count);
                    printf("[LEGENDA: 'z' indica uno zaffiro, 'r' indica 1 rubino, 't' indica uno topazio, 's' indica 1 smeraldo]\n");
                    break;
                }
            }
        }
        else {
            printf("Una collana di lunghezza massima possibile con i filtri prestabiliti è la seguente: \n");
            for (i = totale; i > 0; i--) {
                count = perm_rip_una_sola(0, distinti, soluzioni, mark, i, n_distinti, count);
                if (count != 0) {
                    printf("La collana è lunga %d\n", i);
                    printf("[LEGENDA: 'z' indica uno zaffiro, 'r' indica 1 rubino, 't' indica uno topazio, 's' indica 1 smeraldo]\n");
                    break;
                }
            }
        }
    }
    free(soluzioni);
    free(distinti);
    free(mark);
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
int leggiComando(void) {
    int i;
    printf("Vuoi stampare tutte le collane di lunghezza massima o una qualsiasi collana di lunghezza massima?\n[Premere 1 per la prima opzione, premere 2 per la seconda]\n");
    fscanf(stdin, "%d", &i);
    if (i != 1 && i != 2) {
        printf("Comando sbagliato! ");
        exit(1);
    }
    return i;
}
int check ( char * vettore, int lunghezza) {
    if (Filter1(vettore, lunghezza) && Filter2(vettore, lunghezza)) {
        return 1;
    }
    return 0;
}
int perm_rip_tutte(int pos, char *dist_val, char *sol, int *mark, int n, int n_dist, int cnt){
    int i;
    if (pos >= n) {
        if (check(sol, n) == 1) {
            printf("{ ");
            for (i=0; i<n; i++) {
                printf("%c ", sol[i]);
            }
            printf("}\n");
            return cnt+1;
        }
        return cnt;
    }
    for (i=0; i<n_dist; i++) {
        if (mark[i] > 0) {
            mark[i]--;
            sol[pos] = dist_val[i];
            cnt = perm_rip_tutte(pos+1, dist_val, sol, mark, n, n_dist, cnt);
            mark[i]++;
        }
    }
    return cnt;
}
int perm_rip_una_sola(int pos, char *dist_val, char *sol, int *mark, int n, int n_dist, int count){
    int i;
    if ( check(sol, pos) == 0 && pos > 0) {
        return 0;
    }
    if (pos >= n) {
        if (check(sol, n) == 1) {
            printf("{ ");
            for (i=0; i<n; i++) {
                printf("%c ", sol[i]);
            }
            printf("}\n");
            return 1;
        }
        else {
            return 0;
        }
    }
    for (i=0; i<n_dist; i++) {
        if (mark[i] > 0) {
            mark[i]--;
            sol[pos] = dist_val[i];
            if (perm_rip_una_sola(pos + 1, dist_val, sol, mark, n, n_dist, count)) {
                return 1;
            };
            mark[i]++;
        }
    }
    return 0;
}
int Filter1(char * vettore , int lunghezza) {
    int i;
    for (i=0; i<lunghezza-1; i++) {
        if ((vettore[i] == 'z'  || vettore[i] == 't' ) && (vettore[i+1] == 's' || vettore[i+1] == 't')) {
            return 0;
        }
    }
    return 1;
}
int Filter2(char * vettore, int lunghezza) {
    int i;
    for (i=0; i<lunghezza-1; i++) {
        if ((vettore[i] == 'r' || vettore[i] == 's' ) && (vettore[i+1] == 'z' || vettore[i+1] == 'r')) {
            return 0;
        }
    }
    return 1;
}
