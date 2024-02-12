#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR 30
#define NUMERO_COMANDI 6

// variabili globali
int i;
// struct globali
struct tratta {
    char data[MAX_STR + 1];
    char codice_tratta[MAX_STR + 1];
    char partenza[MAX_STR + 1];
    char capolinea[MAX_STR + 1];
    int ritardo;
};
struct tratta elenco[1000];

void leggiFile(void);
int leggiComando(void);
void cercaCorseDate(void);
void cercaCorseCapolinea(void);
void cercaCorsePartenza(void);
void cercaCorseRitardo(void);
void cercaCorseRitardoTotale(void);
void strToLower(char s[]);

void menuParola();
enum comando_e {r_date=1, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine};
int main() {
    leggiFile();
    menuParola();
    return 0;
}

void leggiFile(void) {
    // variabili generali
    int righe;
    // aperture file
    FILE *fp;
    fp = fopen("log.txt", "r");
    fscanf(fp, "%d\n", &righe);
    for (i = 0; i < righe; i++) {
        struct tratta tratta1;
        fscanf(fp, "%s %s %s %s %*s %*s %d \n", tratta1.codice_tratta, tratta1.partenza, tratta1.capolinea,
               tratta1.data, &tratta1.ritardo);
        elenco[i] = tratta1;
    }
    fclose(fp);
}

void menuParola() {
    int continua=1;
    char riga[MAX_STR+1];
    enum comando_e nomeComando;
    while ( continua ) {
        nomeComando = leggiComando();
        switch (nomeComando) {
            case r_date:
                cercaCorseDate();
                break;
            case r_partenza:
                cercaCorsePartenza();
                break;
            case r_capolinea:
                cercaCorseCapolinea();
                break;
            case r_ritardo:
                cercaCorseRitardo();
                break;
            case r_ritardo_tot:
                cercaCorseRitardoTotale();
                break;
            case r_fine:
                continua = 0;
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
    char comandi_disponibili[NUMERO_COMANDI][MAX_STR+1] = {"date", "partenza", "capolinea", "ritardo", "ritardo_tot", "fine"};
    printf("Comando [date/partenza/capolinea/ritardo/ritardo_tot/fine] ");
    scanf("%s", input);
    for (j=0; j<NUMERO_COMANDI; j++) {
        if (strcmp(input, comandi_disponibili[j]) == 0) {
            return j+1;
        };
    }
    return 0; // se non trova nessun uguaglianza uscirà dal for e ritornerà il valore zero
};
void cercaCorseDate(void) {
    // variabile usata nel ciclo
    int k;
    // variabile flag
    int trovata = 0;
    char data1[MAX_STR], data2[MAX_STR];
    scanf(" %s %s", data1, data2);
    for (k=0; k<i; k++) {
        if (strcmp(elenco[k].data, data1) >= 0  && strcmp(elenco[k].data, data2) <= 0 ) {
            printf("%s %s %s %s \n", elenco[k].codice_tratta, elenco[k].partenza, elenco[k].capolinea,
                   elenco[k].data);
            trovata = 1;
        }
    }
    if (trovata == 0) {
        printf("Nessuna corsa trovata nell'intervallo considerato\n");
    }
}
void cercaCorsePartenza(void) {
    // variabili usate nei cicli
    int k, e;
    // variabile flag
    int trovata = 0;
    char partenza[MAX_STR];
    char vettore_copia[MAX_STR];
    scanf(" %s", partenza);
    for (k=0; k<i; k++) {
        for (e=0; e< strlen(elenco[k].partenza); e++) {
            vettore_copia[e] = elenco[k].partenza[e];
        }
        strToLower(vettore_copia);
        strToLower(partenza);
        if (strcmp(vettore_copia, partenza) == 0 ) {
            printf("%s %s %s %s \n", elenco[k].codice_tratta, elenco[k].partenza, elenco[k].capolinea,
                   elenco[k].data);
            trovata = 1;
        }
    }
    if (trovata == 0) {
        printf("Nessuna corsa trovata che abbia la partenza indicata\n");
    }
};
void cercaCorseCapolinea(void) {
    // variabili usate nei cicli
    int k, e;
    // variabile flag
    int trovata = 0;
    char capolinea[MAX_STR];
    scanf(" %s", capolinea);
    char vettore_copia[MAX_STR];
    for (e=0; e< strlen(elenco[k].capolinea); e++) {
        vettore_copia[e] = elenco[k].capolinea[e];
    }
    strToLower(vettore_copia);
    strToLower(capolinea);
    for (k=0; k<i; k++) {
        if (strcmp(vettore_copia, capolinea) == 0 ) {
            printf("%s %s %s %s \n", elenco[k].codice_tratta, elenco[k].partenza, elenco[k].capolinea,
                   elenco[k].data);
            trovata = 1 ;
        }
    }
    if (trovata == 0) {
        printf("Nessuna corsa trovata che abbia il capolinea indicato\n");
    }
};
void cercaCorseRitardo(void) {
    // variabile usata nel ciclo
    int k;
    // variabile flag
    int trovata = 0;
    char data1[MAX_STR], data2[MAX_STR];
    scanf(" %s %s", data1, data2);
    for (k=0; k<i; k++) {
        if (strcmp(elenco[k].data, data1) >= 0 && strcmp(elenco[k].data, data2) <= 0) {
            if (elenco[k].ritardo != 0 ) {
                printf("%s %s %s %s con ritardo: %d \n", elenco[k].codice_tratta, elenco[k].partenza, elenco[k].capolinea,
                       elenco[k].data, elenco[k].ritardo);
                trovata = 1;
            }
        }
    }
    if (trovata == 0) {
        printf("Nessuna corsa in ritardo trovata nell'intervallo considerato \n");
    }

};
void cercaCorseRitardoTotale(void) {
    int k, sum=0;
    char codice_tratta[MAX_STR];
    scanf(" %s", codice_tratta);
    for (k=0; k<i; k++) {
        if (strcmp(elenco[k].codice_tratta, codice_tratta) == 0) {
            sum += elenco[k].ritardo;
        }
    }
    printf("Il ritardo totale accumulato dalla linea %s è stato di %d minuti\n", codice_tratta, sum);
};
void strToLower(char s[]) {
    int c=0;
    while (s[c] != '\0') {
        s[c] = tolower(s[c]);
        c++;
    }
}