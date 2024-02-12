#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define NMAX 20
#define MAX_STR 30
#define ORDINAMENTI_RICHIESTI 4
#define NUMERO_COMANDI 9

struct tratta {
    char codice_tratta[4];
    char partenza[NMAX];
    char arrivo[NMAX];
    char data[NMAX];
    char ora_partenza[NMAX];
    char ora_arrivo[NMAX];
    int ritardo;

};

enum comando_e {r_contenuto_log=1, r_ordinamento_data_ora, r_ordinamento_codice_tratta, r_ordinamento_stazione_partenza, r_ordinamento_stazione_arrivo, r_ricerca_binaria, r_ricerca_lineare, r_leggi_file, r_fine};

void readFile(struct tratta **elenco_log, int * n);
void menuParola(void);
int leggiComando (void);
void showVector(struct tratta *vector[], int N);
void MergeSortR(struct tratta *vector_to_sort[], struct tratta *vector_copy[], int l, int r, int c);
void Merge(struct tratta *A[], struct tratta *B[], int l, int q, int r, int c);
void MergeSortTratte(struct tratta *vp[], struct tratta *v_copia[], int N);
void MergeSortData(struct tratta *vp[], struct tratta *v_copia[], int N);
void MergeSortPartenza(struct tratta *vp[], struct tratta *v_copia[], int N);
void MergeSortArrivo(struct tratta *vp[], struct tratta *v_copia[], int N);
int BinarySearch(struct tratta *src[], char * tofind, int n);
int BinSearch(struct tratta *src[], int l, int r, char * tofind);
void LinearSearch(struct tratta *src[], char * tofind, int n);
int Search( char * big, char * small);

int main (void) {
    menuParola();
    return 0;
}

void readFile(struct tratta **elenco_log, int * n) {
    FILE *fp;
    struct tratta *m;
    int i;
    char s[30];
    printf("Come si chiama il file che vuoi aprire? [Massimo 30 caratteri]\n");
    scanf("%s", s);
    if ((fp = fopen(s, "r")) == NULL) {
        printf("Problemi nell'apertura del file");
        exit(1);
    }
    else {
        fscanf(fp, "%d\n", n);
        m = (struct tratta *) malloc(*n * sizeof(struct tratta));
        for (i=0; i<*n; i++) {
            fscanf(fp, "GTT%s %s %s %s %s %s %d\n", m[i].codice_tratta, m[i].partenza, m[i].arrivo, m[i].data, m[i].ora_partenza, m[i].ora_arrivo, &(m[i]).ritardo);
        }
        *elenco_log = m;
        printf("File aperto e letto con successo!\n");
    }
    fclose(fp);
}
void menuParola(void) {
    int i, n, j;
    int continua = 1;
    struct tratta *vettore_struct;
    struct tratta **vettore_pointer_fisso;
    struct tratta **vettore_copie;
    struct tratta ***vettore_pointer;
    char string_tbf[NMAX];
    readFile(&vettore_struct, &n);
    vettore_pointer_fisso = (struct tratta **) malloc(n*sizeof(struct tratta *));
    vettore_copie = (struct tratta **) malloc(n*sizeof(struct tratta *));
    for (i = 0; i < n; i++) {
        vettore_pointer_fisso[i] = &vettore_struct[i];
        vettore_copie[i] = &vettore_struct[i];
    }
    vettore_pointer = (struct tratta ***) malloc(ORDINAMENTI_RICHIESTI*(sizeof (struct tratta **)));
    for (i=0; i<ORDINAMENTI_RICHIESTI; i++) {
        vettore_pointer[i] = (struct tratta **) malloc(n * sizeof(struct tratta *));
        for (j=0; j<n; j++) {
            vettore_pointer[i][j] = &vettore_struct[j];
        }
    }
    enum comando_e nomeComando;
    while (continua) {
        nomeComando = leggiComando();
        switch (nomeComando) {
            case r_contenuto_log:
                printf("Contenuti del log-----------------------\n");
                showVector(vettore_pointer_fisso, n);
                printf("\n");
                break;
            case r_ordinamento_data_ora:
                printf("Ordinamento in base alla data della tratta-----------------------\n");
                MergeSortData(vettore_pointer[0], vettore_copie, n);
                showVector(vettore_pointer[0], n);
                printf("\n");
                break;
            case r_ordinamento_codice_tratta:
                printf("Ordinamento in base al codice della tratta-----------------------\n");
                MergeSortTratte(vettore_pointer[1], vettore_copie, n);
                showVector(vettore_pointer[1], n);
                printf("\n");
                break;
            case r_ordinamento_stazione_partenza:
                printf("Ordinamento in base alla stazione di partenza-----------------------\n");
                MergeSortPartenza(vettore_pointer[2], vettore_copie, n);
                showVector(vettore_pointer[2], n);
                printf("\n");
                break;
            case r_ordinamento_stazione_arrivo:
                printf("Ordinamento in base alla stazione di arrivo-----------------------\n");
                MergeSortArrivo(vettore_pointer[3], vettore_copie, n);
                showVector(vettore_pointer[3], n);
                printf("\n");
                break;
            case r_ricerca_binaria:
                printf("Stringa da cercare [Lunghezza massima: 20 caratteri]\n ");
                fscanf(stdin, "%s", string_tbf);
                printf("Ricerca dicotomica-----------------------\n");
                LinearSearch(vettore_pointer_fisso, string_tbf, n);
                printf("\n");
                break;
            case r_ricerca_lineare:
                printf("Stringa da cercare [Lunghezza massima: 20 caratteri]\n ");
                fscanf(stdin, "%s", string_tbf);
                printf("Ricerca lineare-----------------------\n");
                MergeSortPartenza(vettore_pointer[2], vettore_copie,
                                  n); // Per usare la Binary Search prima devo ordinare il vettore
                BinarySearch(vettore_pointer[2], string_tbf, n);
                printf("\n");
                break;
            case r_leggi_file:
                for ( i=0; i<n; i++) {
                    free(vettore_pointer[i]);
                }
                free(vettore_pointer);
                free(vettore_copie);
                free(vettore_pointer_fisso);
                free(vettore_struct);
                readFile(&vettore_struct, &n);
                vettore_pointer_fisso = (struct tratta **) malloc(n*sizeof(struct tratta *));
                vettore_copie = (struct tratta **) malloc(n*sizeof(struct tratta *));
                for (i = 0; i < n; i++) {
                    vettore_pointer_fisso[i] = &vettore_struct[i];
                    vettore_copie[i] = &vettore_struct[i];
                }
                vettore_pointer = (struct tratta ***) malloc(ORDINAMENTI_RICHIESTI*(sizeof (struct tratta **)));
                for (i=0; i<ORDINAMENTI_RICHIESTI; i++) {
                    vettore_pointer[i] = (struct tratta **) malloc(n * sizeof(struct tratta *));
                    for (j=0; j<n; j++) {
                        vettore_pointer[i][j] = &vettore_struct[j];
                    }
                }
                break;
            case r_fine:
                continua = 0;
                printf("Programma terminato\n");
                break;
            default:
                printf("Errore nel comando\n");
                break;
        }
    }
}
int leggiComando (void){
    int j;
    char input[MAX_STR+1];
    char comandi_disponibili[NUMERO_COMANDI][MAX_STR+1] = {"contenuto_log", "ordinamento_data_ora", "ordinamento_codice_tratta", "ordinamento_stazione_partenza", "ordinamento_stazione_arrivo", "ricerca_binaria", "ricerca_lineare", "leggi_file", "fine"};
    printf("Comando [contenuto_log/ordinamento_data_ora/ordinamento_codice_tratta/ordinamento_stazione_partenza/ordinamento_stazione_arrivo/ricerca_binaria/ricerca_lineare/leggi_file/fine] \n");
    scanf("%s", input);
    for (j=0; j<NUMERO_COMANDI; j++) {
        if (strcmp(input, comandi_disponibili[j]) == 0) {
            return j+1;
        };
    }
    return 0; // se non trova nessun uguaglianza uscirà dal for e ritornerà il valore zero
};
void MergeSortTratte(struct tratta *vp[], struct tratta *v_copia[], int N) {
    int l=0, r=N-1;
    MergeSortR(vp, v_copia, l, r, 0);
}
void MergeSortData(struct tratta *vp[], struct tratta *v_copia[], int N) {
    int l=0, r=N-1;
    MergeSortR(vp, v_copia, l, r, 1);
}
void MergeSortPartenza(struct tratta *vp[], struct tratta *v_copia[], int N) {
    int l=0, r=N-1;
    MergeSortR(vp, v_copia, l, r, 2);
}
void MergeSortArrivo(struct tratta *vp[], struct tratta *v_copia[], int N) {
    int l=0, r=N-1;
    MergeSortR(vp, v_copia, l, r, 3);
}
void MergeSortR(struct tratta *vector_to_sort[], struct tratta *vector_copy[], int l, int r, int c) {
    int q;
    if (l >= r) {
        return;
    }
    q = (l+r) / 2;
    MergeSortR(vector_to_sort, vector_copy, l, q, c);
    MergeSortR(vector_to_sort, vector_copy, q+1, r, c);
    Merge(vector_to_sort, vector_copy, l, q, r, c);

}
void Merge(struct tratta *A[], struct tratta *B[], int l, int q, int r, int c) { // perché non posso usare le frecce?
    int i, j, k;
    i = l;
    j = q+1;
    switch(c) {
        case 0:
            for (k = l; k <= r; k++) {
                if (i > q) {
                    B[k] = A[j++];
                }
                else if (j > r) {
                    B[k] = A[i++];
                }
                else if (strcmp(A[i]->codice_tratta, A[j]->codice_tratta) < 0 || strcmp(A[i]->codice_tratta, A[j]->codice_tratta) == 0) {
                    B[k] = A[i++];
                }
                else {
                    B[k] =  A[j++];
                }
            }
            break;
        case 1:
            for (k = l; k <= r; k++) {
                if (i > q) {
                    B[k] = A[j++];
                }
                else if (j > r) {
                    B[k] = A[i++];
                }
                else if (strcmp(A[i]->data, A[j]->data) < 0 ) {
                    B[k] = A[i++];
                }
                else if (strcmp(A[i]->data, A[j]->data) == 0) {
                    if (strcmp(A[i]->ora_partenza, A[j]->ora_partenza) < 0) {
                        B[k] = A[i++];
                    }
                    else {
                        B[k] =  A[j++];
                    }
                }
                else {
                    B[k] =  A[j++];
                }
            }
            break;
        case 2:
            for (k = l; k <= r; k++) {
                if (i > q) {
                    B[k] = A[j++];
                }
                else if (j > r) {
                    B[k] = A[i++];
                }
                else if (strcmp(A[i]->partenza, A[j]->partenza) < 0 || strcmp(A[i]->partenza, A[j]->partenza) == 0) {
                    B[k] = A[i++];
                }
                else {
                    B[k] =  A[j++];
                }
            }
            break;
        case 3:
            for (k = l; k <= r; k++) {
                if (i > q) {
                    B[k] = A[j++];
                }
                else if (j > r) {
                    B[k] = A[i++];
                }
                else if (strcmp(A[i]->arrivo, A[j]->arrivo) < 0 || strcmp(A[i]->arrivo, A[j]->arrivo) == 0) {
                    B[k] = A[i++];
                }
                else {
                    B[k] =  A[j++];
                }
            }
            break;
    }
    for ( k = l; k <= r; k++ ) {
        A[k] = B[k];
    }
    return;
}
void showVector(struct tratta *vector[], int N) {
    int i;
    for (i=0; i<N; i++) {
        printf("GTT%s %s %s %s %s %s %d\n", vector[i]->codice_tratta, vector[i]->partenza, vector[i]->arrivo, vector[i]->data, vector[i]->ora_partenza, vector[i]->ora_arrivo, vector[i]->ritardo);
    }
}
int BinSearch(struct tratta *src[], int l, int r, char * tofind) {
    int m;
    if (l > r) {
        return -1;
    }
    m = (l + r)/2;
    if (strncmp(src[m]->partenza, tofind, strlen((tofind))) == 0){
        return m;
    }
    if (strncmp(tofind, src[m]->partenza, strlen(tofind)) < 0) {
        return BinSearch(src, l, m - 1, tofind);
    }
    return BinSearch(src, m+1, r, tofind);
}
int BinarySearch(struct tratta *src[], char * tofind, int n) {
    int l=0, r=n-1, a, i, j;
    a = BinSearch(src, l, r, tofind);
    if (a == -1) {
        printf("Tratta non trovata\n");
    }
    else {
        printf("La tratta che corrisponde alla ricerca della stringa \'%s\': \nGTT%s %s %s %s %s %s %d\n", tofind,
               (src[a])->codice_tratta, src[a]->partenza, src[a]->arrivo, src[a]->data, src[a]->ora_partenza,
               src[a]->ora_arrivo, src[a]->ritardo);
        i = a;
        i++;
        j = a;
        j--;
        while (i <= r && (strncmp(src[i]->partenza, tofind, strlen(tofind)) == 0) ) {
            printf("GTT%s %s %s %s %s %s %d\n", (src[i])->codice_tratta, src[i]->partenza, src[i]->arrivo, src[i]->data,
                   src[i]->ora_partenza, src[i]->ora_arrivo, src[i]->ritardo);
            i++;
        }
        while (j >= l && (strncmp(src[j]->partenza, tofind, strlen(tofind)) == 0)) {
            printf("GTT%s %s %s %s %s %s %d\n", (src[j])->codice_tratta, src[j]->partenza, src[j]->arrivo, src[j]->data,
                   src[j]->ora_partenza, src[j]->ora_arrivo, src[j]->ritardo);
            j--;
        }
    }
}
int Search( char * big, char * small) {
    int l_small = strlen(small);
    int i, j, flag=1;
    for (i=0; i<l_small; i++) {
        if ( big[i] != small[i]) {
            flag = 0;
            break;
        }
    }
    if (flag == 1) {
        return 1;
    }
    return -1;
}
void LinearSearch(struct tratta *src[], char * tofind, int N) {
    int i, j , first =1, c;
    for (i=0; i<N; i++) {
        c = Search((src[i])->partenza, tofind);
        if (first && c==1) {
            printf("La/e tratta/e che corrisponde/ono alla ricerca della stringa \'%s\': \n", tofind);
            first = 0;
        }
        if ( c == 1 ) {
            printf("GTT%s %s %s %s %s %s %d\n",(src[i])->codice_tratta, src[i]->partenza, src[i]->arrivo, src[i]->data, src[i]->ora_partenza, src[i]->ora_arrivo, src[i]->ritardo);
        }
    }
    if ( first == 1) {
        printf("Tratta non trovata\n");
    }

}