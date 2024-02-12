#include <stdio.h>
#include <stdlib.h>
#include "azioni.h"


int main(void) {
    COLLEZIONE_TIT collezione = COLLinit();
    char * filename, *titlename;
    int S;
    filename = (char *) malloc(STRMAX * sizeof(char));
    titlename = (char *) malloc(STRMAX * sizeof(char));
    FILE * fp;
    int continua = 1;
    enum comando_e comando;
    while (continua) {
        comando = leggiComando();
        switch (comando) {
            case leggi_file:
                printf("Come si chiama il file che vuoi aprire?\n");
                fscanf(stdin, "%s", filename);
                fp = fopen(filename, "r");
                COLLreadFile(collezione, fp);
                COLLshow(collezione);
                break;
            case ricerca_titolo:
                printf("Come si chiama il titolo che vuoi cercare?\n");
                fscanf(stdin, "%s", titlename);
                COLLsearchTit(collezione, titlename);
                break;
            case ricerca_quotazione:
                printf("Come si chiama il titolo di cui vuoi cercare la quotazione?\n");
                fscanf(stdin, "%s", titlename);
                COLLsearchQuot(collezione, titlename);
                break;
            case ricerca_quotazione_max_min_int:
                printf("Come si chiama il titolo di cui vuoi cercare la quotazione massima e minima tra due date?\n");
                fscanf(stdin, "%s", titlename);
                COLLsearchMinMax(collezione, titlename);
                break;
            case ricerca_quotazione_max_min_totale:
                printf("Come si chiama il titolo che vuoi cercare la quotazione massima e minima?\n");
                fscanf(stdin, "%s", titlename);
                COLLsearchMinMaxTot(collezione, titlename);
                break;
            case bilancia_bst_quotazioni:
                printf("Come si chiama il titolo di cui vuoi bilanciare l'albero delle quotazioni?\n");
                fscanf(stdin, "%s", titlename);
                printf("Qual è la soglia di ribilanciamento?\n");
                fscanf(stdin, "%d", &S);
                COLLBalance(collezione, titlename, S);
                break;
            case chiudi:
                continua = 0;
                break;
            default:
                printf("Comando sbagliato\n");
                break;
        }
    }
    COLLfree(collezione);
    free(filename);
    free(titlename);
    return 0;
}