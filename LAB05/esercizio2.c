#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char orizzontale_colore;
    int orizzontale_punti;
    char verticale_colore;
    int verticale_punti;
} tile;

typedef struct {
    int indice;
    int ruotato;
} casella;

typedef struct{
    int * vettore_rotazione_finale;
    int * vettore_indice_tasselli_finale;
} configurazione;

configurazione scacchiera_finale; // la dichiaro globale per evitare di passare una struct di due vettori attraverso tante ricorsioni cosa che potrebbe diventare pesante

// funzioni di allocazione
int * creaVettoreInteri(int n);
tile * creaVettoreTile(int n);
casella * creaVettoreCasella(int n);
// funzioni di lettura dati
tile * readDataVector(int * n, tile * tile_disponibili);
casella * readDataBoard(int * r, int * c, casella * board);
int * readDataRotazioni(int R, int C, int *  mark);
// funzione di formattazione di val per costruire un vettore di indici da 0 a 9
void formatVal(int * val, int n);
// funzioni di display
void showConfigurazione(configurazione scacchiera, int n);
void showVector(tile * tile_disponibili, int n);
// funzioni di calcolo combinatorio per l'esplorazione dello spazio delle soluzioni
int disp ( int pos, int *val, int *sol, int *mark, int n, int k, int cnt, casella * board, tile * tile_disponibili, int righe, int colonne, int * max, int * rotazioni);
int princ_molt(int pos, int *val, int *soluzioni, int n, int cnt, int *vett_disposto, tile * tile_disponibili, int righe, int colonne, int * max, int * rotazioni);
// funzioni di validazione delle soluzioni per il problema di ottimizzazione
int checkTile(casella tassello, int * sol, int posizione);
int checkBoard(casella * board, int * sol, int n); // controlla se le tessere sono al posto giusto
int checkBoardRot(int * val, int * rotazioni, int n); // controlla se le tessere al posto giusto sono anche girate nel modo giusto
int checkMax(int *indici_candidati, int *rotazioni, tile * tile_disponibili, int righe, int colonne, int * max);
int checkRow(int *indici_candidati, int righe, int colonne, int *rotazioni, tile * disponibili);
int checkColumn(int *indici_candidati, int righe, int colonne, int *rotazioni, tile * disponibili);
// funzioni di deallocazione
void liberaVettoreInteri(int * vettore);
void liberaVettoreTile(tile * vettore);
void liberaVettoreCasella (casella * vettore);


int main(void) {
    int R, C, n, max=0;
    int *rotazioni=NULL, *mark, *val, *sol;
    tile * tile_disponibili=NULL;
    casella *board=NULL;
    tile_disponibili = readDataVector(&n, tile_disponibili);
    board = readDataBoard(&R, &C, board);
    rotazioni = readDataRotazioni(R, C, rotazioni);
    scacchiera_finale.vettore_rotazione_finale = creaVettoreInteri(R*C);
    scacchiera_finale.vettore_indice_tasselli_finale = creaVettoreInteri(R*C);
    printf("I tasselli disponibili sono i seguenti\n");
    showVector(tile_disponibili, n);
    val = creaVettoreInteri(n);
    formatVal(val, n);
    sol = creaVettoreInteri(n);
    mark = calloc(n, sizeof(int));
    printf("Con le tessere e la scacchiera date, il massimo del punteggio ottenibile é %d\n", disp(0, &val[0], &sol[0], &mark[0], n, R*C, 0, board, &tile_disponibili[0], R, C, &max, &rotazioni[0])); // giusto per vedere se dispone bene e lo fa
    printf("La configurazione che assicura questo punteggio è: \n");
    showConfigurazione(scacchiera_finale, R*C);
    printf("[Il primo numero indica l'indice della tessera nell'elenco e il secondo numero se è stata ruotata (1) oppure no (0)] \n");
    liberaVettoreTile(tile_disponibili);
    liberaVettoreCasella(board);
    liberaVettoreInteri(rotazioni);
    liberaVettoreInteri(mark);
    liberaVettoreInteri(scacchiera_finale.vettore_rotazione_finale);
    liberaVettoreInteri(scacchiera_finale.vettore_indice_tasselli_finale);
    return 0;
}


int * creaVettoreInteri(int n) {
    int * vettore;
    vettore = (int *) malloc(n * sizeof(int));
    return vettore;
}
tile * creaVettoreTile(int n) {
    tile * vettore;
    vettore = (tile * ) malloc(n* sizeof(tile ));
    return vettore;
}
casella * creaVettoreCasella(int n) {
    casella * vettore;
    vettore = (casella * ) malloc(n* sizeof(casella ));
    return vettore;
}
/////////////////////////////////////////////
tile * readDataVector(int * n, tile * tile_disponibili) {
    FILE * fp;
    int i;
    fp = fopen("tiles.txt", "r");
    if (fp == NULL) {
        printf("File non trovato\n");
        exit(1);
    }
    fscanf(fp, "%d\r", n);
    tile_disponibili = creaVettoreTile((*n));
    for (i=0; i<(*n); i++) {
        if (fscanf(fp, "%c %d %c %d\r", &(tile_disponibili[i].orizzontale_colore), &(tile_disponibili[i].orizzontale_punti), &(tile_disponibili[i].verticale_colore), &(tile_disponibili[i].verticale_punti)) != 4)
            break;
    }
    return tile_disponibili;
}
casella * readDataBoard(int * R, int * C, casella * board) {
    FILE * fp;
    int i, j;
    fp = fopen("board.txt", "r");
    if (fp == NULL) {
        printf("File non trovato\n");
        exit(1);
    }
    fscanf(fp, "%d %d\r", R, C);
    board = creaVettoreCasella((*R)*(*C));
    for (i=0; i<*R; i++) {
        for ( j=0; j<*C; j++) {
            fscanf(fp, "%d/%d", &(board[(*C)*i+j].indice), &(board[(*C)*i+j].ruotato));
        }
        fscanf(fp, "\r");
    }
    fclose(fp);
    return board;
}
int * readDataRotazioni( int R, int C, int *  mark) {
    FILE * fp;
    int i, j, a, b;
    mark = creaVettoreInteri(R*C);
    fp = fopen("board.txt", "r");
    fscanf(fp, "%*d %*d\r");
    for ( i=0; i<R; i++) {
        for ( j=0; j<C; j++) {
            fscanf(fp, "%d/%d\r", &a, &b);
            if ( a == -1 && b== -1) {
                mark[i * C + j] = -1;
            }
            else {
                mark[i * C + j] = b;
            }
        }
    }
    fclose(fp);
    return mark;
}
/////////////////////////////////////////////
void formatVal(int * val, int n) {
    int i;
    for ( i=0; i<n; i++) {
        val[i] = i;
    }
}
////////////////////////////////////////////
void showVector(tile * tile_disponibili, int n) {
    int i;
    for (i=0; i<n; i++) {
        printf("%c %d %c %d\n", tile_disponibili[i].orizzontale_colore, tile_disponibili[i].orizzontale_punti, tile_disponibili[i].verticale_colore, tile_disponibili[i].verticale_punti);
    }
}
void showConfigurazione(configurazione scacchiera, int n) {
    int i;
    for (i=0; i<n; i++) {
        printf("%d/%d ", scacchiera.vettore_indice_tasselli_finale[i], scacchiera.vettore_rotazione_finale[i]);
    }
}
/////////////////////////////////////////////
int disp ( int pos, int *val, int *sol, int *mark, int n, int k, int cnt, casella * board, tile * tile_disponibili, int righe, int colonne, int * max, int * rotazioni ) {
    int i;
    if (pos >= k) {
        if (checkBoard(board, sol, k) == 1) {
            int * valori, *soluzioni;
            valori = malloc(k*sizeof(int));
            soluzioni = malloc(k*sizeof(int));
            *max = princ_molt(0, valori, soluzioni, k, 0, sol, tile_disponibili, righe, colonne, max, rotazioni);
        }
        return *max;
    }
    for (i=0; i<n; i++){
        if (mark[i] == 0) {
            mark[i] = 1;
            sol[pos] = val[i];
            *max = disp(pos + 1, val, sol, mark, n, k, cnt, board, tile_disponibili, righe, colonne, max, rotazioni);
            mark[i] = 0;
        }
    }
    return *max;
}

int princ_molt(int pos, int *val, int *soluzioni, int n, int cnt, int *vett_disposto, tile * tile_disponibili, int righe, int colonne, int * max , int * rotazioni) {
    int i, max_candidate;
    if (pos >= n) {
        if (checkBoardRot(soluzioni, rotazioni, n) == 1) {
            max_candidate = checkMax(vett_disposto, soluzioni, tile_disponibili, righe, colonne, max);
            if ( max_candidate!= -1) {
                *max = max_candidate;
                for (i = 0; i < n; i++) {
                    scacchiera_finale.vettore_indice_tasselli_finale[i] = vett_disposto[i];
                    scacchiera_finale.vettore_rotazione_finale[i] = soluzioni[i];
                }
            }
        }
        return *max;
    }
    soluzioni[pos] = 1;
    *max = princ_molt(pos + 1, val, soluzioni, n, cnt, vett_disposto, tile_disponibili, righe, colonne, max, rotazioni);
    soluzioni[pos] = 0;
    *max = princ_molt(pos + 1, val, soluzioni, n, cnt, vett_disposto, tile_disponibili, righe, colonne, max, rotazioni);
    return *max;
}
///////////////////////////////////////////////////
int checkBoard(casella * board, int * sol, int n) {
    int i;
    for (i=0; i<n; i++) {
        if (board[i].indice != -1) {
            if (checkTile(board[i], sol, i) == 0){
                return 0;
            }
        }
    }
    return 1;
}
int checkTile(casella tassello, int * sol, int posizione) {
    if (tassello.indice == sol[posizione]) {
        return 1;
    }
    return 0;
}
int checkBoardRot(int * val, int * rotazioni, int n) {
    int i;
    for (i=0; i<n; i++) {
        if (rotazioni[i] != -1) {
            if ( val[i] != rotazioni[i] ) {
                return 0;
            }
        }
    }
    return 1;

}
int checkMax(int *indici_candidati, int *rotazioni, tile * tile_disponibili, int righe, int colonne, int * max) {
    int i, j;
    int somma=0;
    for (i=0; i<righe; i++) {
        somma += checkRow(indici_candidati, i, colonne, rotazioni, tile_disponibili);
    }
    for (j=0; j<colonne; j++) {
        somma += checkColumn(indici_candidati, j, colonne, rotazioni, tile_disponibili);
    }
    if (somma > *max) {
        return somma;
    }
    return -1;
}
int checkRow(int *indici_candidati, int righe, int colonne, int *rotazioni, tile * disponibili) {
    char a;
    int i, somma=0, first=1;
    for ( i=0; i<colonne; i++) {
        if (first) {
            if ( rotazioni[indici_candidati[i+righe*colonne]] == 0) {
                a = disponibili[indici_candidati[i+righe*colonne]].orizzontale_colore;
                somma += disponibili[indici_candidati[i+righe*colonne]].orizzontale_punti;
            }
            else {
                a = disponibili[indici_candidati[i+righe*colonne]].verticale_colore;
                somma += disponibili[indici_candidati[i+righe*colonne]].verticale_punti;
            }
            first=0;
        }
        else {
            if ( rotazioni[indici_candidati[i+righe*colonne]] == 0) {
                if (disponibili[indici_candidati[i+righe*colonne]].orizzontale_colore != a) {
                    return 0;
                }
                else {
                    somma += disponibili[indici_candidati[i+righe*colonne]].orizzontale_punti;
                }
            }
            else {
                if (disponibili[indici_candidati[i+righe*colonne]].verticale_colore != a) {
                    return 0;
                }
                else {
                    somma += disponibili[indici_candidati[i+righe*colonne]].verticale_punti;
                }
            }
        }
    }
    return somma;
}
int checkColumn(int *indici_candidati, int righe, int colonne, int *rotazioni, tile * disponibili) {
    int i, somma=0, first=1;
    char a;
    for ( i=0; i<colonne; i++) {
        if (first) {
            if ( rotazioni[indici_candidati[righe+colonne*i]] == 0) {
                a = disponibili[indici_candidati[righe+colonne*i]].verticale_colore;
                somma += disponibili[indici_candidati[righe+colonne*i]].verticale_punti;
            }
            else {
                a = disponibili[indici_candidati[righe+colonne*i]].orizzontale_colore;
                somma += disponibili[indici_candidati[righe+colonne*i]].orizzontale_punti;
            }
            first=0;
        }
        else {
            if ( rotazioni[indici_candidati[righe+colonne*i]] == 0) {
                if (disponibili[indici_candidati[righe+colonne*i]].verticale_colore != a) {
                    return 0;
                }
                else {
                    somma += disponibili[indici_candidati[righe+colonne*i]].verticale_punti;
                }
            }
            else {
                if (disponibili[indici_candidati[righe+colonne*i]].orizzontale_colore != a) {
                    return 0;
                }
                else {
                    somma += disponibili[indici_candidati[righe+colonne*i]].orizzontale_punti;
                }
            }
        }
    }
    return somma;
}
/////////////////////////////////////////////
void liberaVettoreInteri(int * vettore) { // provare se possibile fare un'unica funzione che ha come parametro un puntatore a null che viene convertito implicitamente a seconda dei casi
    free(vettore);
}
void liberaVettoreTile(tile * vettore) {
    free(vettore);
}
void liberaVettoreCasella (casella * vettore) { // provare se possibile fare un'unica funzione che ha come parametro un puntatore a null che viene convertito implicitamente a seconda dei casi
    free(vettore);
}
