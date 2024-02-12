#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *cercaRegexp(char *src, char *regexp);
int typeOf(char carattere);
int strlenModified(char * stringa);

int main() {
    char parola[40];
    printf("La tua parola è: \n");
    scanf("%s", parola);
    char stringa[40];
    printf("La stringa da cercare è: \n");
    scanf("%s", stringa);
    if (cercaRegexp(parola, stringa) == NULL) {
        printf("La prima stringa non contiene la seconda");
    } else {
        printf("La lettera è %c all'indirizzo %p\n", *cercaRegexp(parola, stringa), cercaRegexp(parola, stringa));
    }
    return 0;
}
char *cercaRegexp(char *src, char *regexp) {
    char *p_src = src;
    char *p_regexp = regexp;
    char *p_NULL = NULL;
    int len_src, len_regexp, LEN_regexp, i, j, k, l, counter=0, equals=1, atleast=0, different=1;
    len_regexp = strlen(regexp);
    len_src = strlen(src);
    LEN_regexp = strlenModified(regexp);
    if (LEN_regexp > len_src) {    // controllo sulla lunghezza
        return p_NULL;
    }
    for (i=0; i<(len_src-LEN_regexp)+1; i++) {
        counter = 0;
        for (j=0; j<LEN_regexp; j++) {
                switch(typeOf(*(p_regexp + j))) {
                    case 0:
                        counter++;
                        break;
                    case 1:
                        if (*(p_src+i+j) == *(p_regexp+j)) {
                            counter++;
                        }
                        else {
                            equals = 0;
                        }
                        break;
                    case 2:
                        if ((*(p_regexp+j+1) == 'A' && isupper(*(p_src+i+j))) || (*(p_regexp+j+1) == 'a' && islower(*(p_src+i+j)))) {
                            counter++;
                        }
                        else {
                            equals=0;
                        }
                        p_regexp++;
                        break;
                    case 3:
                        if (*(p_regexp + j + 1) != '^') {
                            for (k = 0; k < len_regexp - LEN_regexp; k++) {
                                if (*(p_regexp + j + 1 + k) == *(p_src + i + j)) {
                                    counter++;
                                    atleast = 1;
                                }
                            }
                            if (atleast == 0) {
                                equals = 0;
                            }
                            p_regexp = p_regexp + k;
                            break;
                        }
                        else {
                            for (l = 1; l < len_regexp - LEN_regexp - 1; l++) { // qua il counter parte da 1 invece di aggiungere 1
                                if (*(p_regexp + j + 1 + l ) == *(p_src + i + j)) {
                                    different = 0;
                                }
                            }
                            if (different == 0) {
                                equals = 0;
                            }
                            if (different == 1) {
                                counter++;
                            }
                            p_regexp = p_regexp + l + 1;
                            break;
                        }
                    case 4:
                        printf("n4");
                        break;
                    default:
                        return p_NULL; // handling di eventuali errori
                }
                if (!equals) {
                    equals=1;
                    break;

                }
        }
        if (counter == LEN_regexp) {
            return src+i;
        }
        p_src = src;
        p_regexp = regexp;
    }
    return p_NULL; // handling di altri eventuali errori (al massimo ritorna un puntatore null)
}
int typeOf(char carattere) {
    if (carattere == '.') {
        return 0;
    }
    else if (isalnum(carattere)) {
        return 1;
    }
    else if (carattere == '\\') {
        return 2;
    }
    else if (carattere == '[') {
        return 3;
    }
    else if (carattere == '^') {
        return 4;
    }
    return NULL;
}
int strlenModified(char * stringa) { // capire la reale lunghezza del secondo ciclo for (quello che itera sulla j)
    int i, j, flag=1, c=0;
    j = strlen(stringa);
    for (i=0; i<j; i++) {
        if (stringa[i] == '[')
            flag = 0;
        else if (stringa[i] == ']') {
            flag = 1;
            c++;
        }
        else if ((isalpha(stringa[i]) || stringa[i] == '.')&& flag && stringa[i] != '\\') {
            c++;
        }
    }
    return c;
}