#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR 30
#define NUMERO_COMANDI 7

typedef struct {
    int giorno;
    int mese;
    int anno;
} data;

typedef struct {
    char id[4+1];
    char nome[50];
    char cognome[50];
    data nascita;
    char via[50];
    char citta[50];
    int cap;
} persona;
typedef struct node * link;
typedef struct node {
    persona val;
    link next;
} node_t;

enum comando {
    acquisisci_tastiera=1,
    acquisisci_file,
    ricerca,
    cancella,
    cancella_date,
    stampa,
    fine
};

void menuParola(void);
int leggiComando(void);
link readAndAllocateDataFromTerminal(link head);
link readAndAllocateDataFromFile (link h);
int comparaDATA(data data1, data data2);
int comparaNumeri( int i, int j);
link newNode(persona val, link next);
link SortListIns(link h, persona val);
persona SortListSearch(link h, char * k);
persona PERSONAsetvoid(void);
void printSearchResult(persona individuo);
link SortListDel(link h, char * k);
char * getSearchInput(char * input);
data getDeleteInput(int i);
link cancellaDate(link head);
void showList(link h);
void showListFile(link h);
persona listExtrKeyP(link *hp, data giorno1, data giorno2);

int main (void) {
    menuParola();
    return 0;
}

void menuParola (void) {
    int continua=1;
    link head = NULL;
    persona individuo;
    char * input;
    input = (char*) malloc(5*sizeof(char));
    enum comando nomeComando;
    while (continua) {
        nomeComando = leggiComando();
        switch (nomeComando) {
            case acquisisci_tastiera:
                head = readAndAllocateDataFromTerminal(head);
                showList(head);
                break;
            case acquisisci_file:
                head = readAndAllocateDataFromFile(head);
                showList(head);
                break;
            case ricerca:
                individuo = SortListSearch(head, getSearchInput(input));
                printSearchResult(individuo);
                break;
            case cancella:
                head = SortListDel( head, getSearchInput(input));
                showList(head);
                break;
            case cancella_date:
                head = cancellaDate(head);
                showList(head);
                break;
            case stampa:
                showListFile(head);
                break;
            case fine:
                continua = 0;
                break;
            default:
                printf("Comando non valido\n");
        }
    }
    free(input);
}
int leggiComando(void) {
    int i;
    char input[MAX_STR+1];
    char comandi_disponibili[NUMERO_COMANDI][MAX_STR+1] = {"acquisisci_tastiera", "acquisisci_file", "ricerca", "cancella", "cancella_date", "stampa", "fine"};
    printf("Comando [acquisisci_tastiera/acquisisci_file/ricerca/cancella/cancella_date/stampa/fine]\n");
    scanf("%s", input);
    for (i=0; i<NUMERO_COMANDI; i++) {
        if (strcmp(input, comandi_disponibili[i]) == 0) {
            return i+1;
        };
    }
    return 0; // se non trova nessun uguaglianza uscirà dal for e ritornerà il valore zero
};
void showListFile(link h) {
    link x;
    FILE * fp;
    fp = fopen("lista.txt", "w");
    if (h == NULL) {
        fprintf(fp, "La lista è vuota: inserire dei dati anagrafici o da file o da tastiera\n");
    }
    else {
        fprintf(fp, "La lista è composta da\n");
        for (x = h; x->next != NULL; x = x->next) {
            fprintf(fp, "A%s %s %s %d/%d/%d %s %s %d\n", x->val.id, x->val.nome, x->val.cognome, (x->val.nascita.giorno), (x->val.nascita.mese), (x->val.nascita.anno), x->val.via, x->val.citta, (x->val.cap));
        }
        fprintf(fp, "A%s %s %s %d/%d/%d %s %s %d\n", x->val.id, x->val.nome, x->val.cognome, (x->val.nascita.giorno), (x->val.nascita.mese), (x->val.nascita.anno), x->val.via, x->val.citta, (x->val.cap));
    }
}
link readAndAllocateDataFromTerminal (link h) {
    int counter=0, number, i;
    persona * individui;
    printf("Quante persone vuoi inserire\n");
    fscanf(stdin, "%d", &number);
    for ( i=0; i<number; i++) {
    individui = (persona *) malloc(number*sizeof(persona));
    printf("Qual'è il codice dell'individuo?[4 caratteri]\nA");
    fscanf(stdin, "%s", individui[counter].id);
    printf("Quali sono nome e cognome dell'individuo?[Separati da uno spazio]\n");
    fscanf(stdin, "%s %s", individui[counter].nome , individui[counter].cognome);
    printf("Qual è la data di nascita dell'individuo?[Formato gg/mm/aaaa]\n");
    fscanf(stdin, "%d/%d/%d", &(individui[counter].nascita.giorno), &(individui[counter].nascita.mese), &(individui[counter].nascita.anno));
    printf("Qual è la via dove abita?[Senza spazi]\n");
    fscanf(stdin, "%s", individui[counter].via);
    printf("Qual è la città dove abita e il cap della città?[Separati da uno spazio]\n");
    fscanf(stdin, "%s %d", individui[counter].citta, &(individui[counter].cap));
    h = SortListIns(h, individui[counter]);
    }
    free(individui);
    printf("Dati anagrafici acquisiti con successo!\n");
    return h;
}
link readAndAllocateDataFromFile (link h) {
    FILE * fp;
    int counter=0, n=1;
    char * filename=NULL;
    persona * individui;
    filename = (char * ) malloc(MAX_STR*sizeof(char));
    individui = (persona *) malloc(n*sizeof(persona));
    printf("Come si chiama il nome del file che vuoi aprire?\n");
    fscanf(stdin, "%s", filename);
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Il programma non è riuscito ad aprire il file dell'anagrafica\n");
        exit(1);
    }
    while (fscanf(fp, "A%s %s %s %d/%d/%d %s %s %d\r", (individui[counter].id), individui[counter].nome, individui[counter].cognome, &(individui[counter].nascita.giorno), &(individui[counter].nascita.mese), &(individui[counter].nascita.anno), individui[counter].via, individui[counter].citta, &(individui[counter].cap)) == 9) {
        h = SortListIns(h, individui[counter]);
        counter++;
        if (n == counter) {
            n = n*2;
            individui = (persona *) realloc(individui, n*sizeof(persona *));
        }
    }
    free(filename);
    free(individui);
    fclose(fp);
    printf("Dati anagrafici contenuti nel file acquisiti con successo!\n");
    return h;
}
void printSearchResult(persona individuo) {
    if (strcmp(individuo.id, "////") == 0) {
        printf("Nessuna persona registrata ha quel codice identificativo\n");
    }
    else {
        printf("A%s %s %s %d/%d/%d %s %s %d\n", individuo.id, individuo.nome, individuo.cognome, individuo.nascita.giorno,
               individuo.nascita.mese, individuo.nascita.anno, individuo.via, individuo.citta, individuo.cap);
    }
}
data getDeleteInput(int i) {
    data input;
    printf("Data %d: [Formato gg/mm/aaaa]\n", i);
    fscanf(stdin, "%d/%d/%d", &(input.giorno), &(input.mese), &(input.anno));
    return input;
}
char * getSearchInput(char * input) {

    printf("Digitare il codice identificativo della persona: [Formato numerico]\n");
    fscanf(stdin, "%s", input);
    return input;
}
persona SortListSearch(link h, char * k) {
    link x;
    for (x=h; (x!=NULL); x=x->next) {
        if (strcmp(x->val.id, k) == 0) {
            return x->val;
        }
    }
    return PERSONAsetvoid();
}
persona PERSONAsetvoid() {
    persona individuo;
    strcpy(individuo.id,  "////");
    return individuo;
}
int comparaNumeri(int i, int j) {
    if ( i > j) {
        return 1;
    }
    else if (i < j) {
        return -1;
    }
    else {
        return 0;
    }
}
int comparaDATA (data data1, data data2) {  // ritorna 1 se il primo è maggiore del secondo, -1 se vale il contrario, 0 se sono uguali
    if ( comparaNumeri(data1.anno, data2.anno) == 0) {
        if (comparaNumeri(data1.mese, data2.mese) == 0) {
            return comparaNumeri(data1.giorno, data2.giorno);
        }
        else {
            return comparaNumeri(data1.mese, data2.mese);
        }
    }
    else {
        return comparaNumeri(data1.anno, data2.anno);
    }
}
link newNode(persona val, link next) {
    link x = (link) malloc(sizeof (node_t));
    if (x==NULL)
        return NULL;
    else {
        x->val = val;
        x->next = next;
    }
    return x;
}
link SortListIns(link h, persona val) {
    link x, p;
    data k = val.nascita;
    if (h == NULL || comparaDATA( k, h->val.nascita) > 0 ) {
        return newNode(val, h);
    }
    for (x=h->next, p=h; x!=NULL && comparaDATA(x->val.nascita, k ) > 0; p=x, x=x->next);
    p->next = newNode(val, x);
    return h;
}
void showList (link h) {
    link x;
    if (h == NULL) {
        printf("La lista è vuota: inserire dei dati anagrafici o da file o da tastiera\n");
    }
    else {
        printf("La lista è composta da\n");
        for (x = h; x->next != NULL; x = x->next) {
            printf("A%s %s %s %d/%d/%d %s %s %d\n", x->val.id, x->val.nome, x->val.cognome, (x->val.nascita.giorno),
                   (x->val.nascita.mese), (x->val.nascita.anno), x->val.via, x->val.citta, (x->val.cap));
        }
        printf("A%s %s %s %d/%d/%d %s %s %d\n", (x->val.id), x->val.nome, x->val.cognome, (x->val.nascita.giorno),
               (x->val.nascita.mese), (x->val.nascita.anno), x->val.via, x->val.citta, (x->val.cap));
    }
}
link SortListDel(link h, char * k) {
    int trovato=0;
    link x, p;
    if (h == NULL) {
        printf("La lista è gia vuota\n");
        return NULL;
    }
    for (x=h, p=NULL; x!=NULL; p=x, x=x->next) {
        if (strcmp((x->val.id),k) == 0) {
            if (x==h) {
                h = x->next;
            }
            else {
                p->next = x->next;
            }
            printf("Cancellato: A%s %s %s %d/%d/%d %s %s %d\n", x->val.id, x->val.nome, x->val.cognome, (x->val.nascita.giorno),
                   (x->val.nascita.mese), (x->val.nascita.anno), x->val.via, x->val.citta, (x->val.cap));
            free(x);
            trovato=1;
            break;
        }
    }
    if (trovato == 0) {
       printf("Non è stato possibile cancellare alcun elemento con tale codice\n");
    }
    return h;
}
link cancellaDate(link head) {
    persona individuo;
    int counter = 0;
    printf("Vuoi cancellare le persone nate tra le date:\n");
    data data1 = getDeleteInput(1);
    data data2 = getDeleteInput(2);
    individuo = listExtrKeyP(&head, data1, data2);
    while (strcmp(individuo.id,  "////") != 0) {
        printf("Cancellato: A%s %s %s %d/%d/%d %s %s %d\n", individuo.id, individuo.nome, individuo.cognome, (individuo.nascita.giorno),
               (individuo.nascita.mese), (individuo.nascita.anno), individuo.via, individuo.citta, (individuo.cap));
        counter++;
        individuo = listExtrKeyP(&head, data1, data2);
    }
    if (counter == 0) {
        printf("Non è stato possibile eliminare alcun elemento della lista\n");
    }
    return head;
}
persona listExtrKeyP(link *hp, data giorno1, data giorno2) {
    link *xp, t;
    persona i = PERSONAsetvoid();
    for ( xp=hp; (*xp)!=NULL; xp=&((*xp)->next) ) {
        if ((comparaDATA((*xp)->val.nascita, giorno1) >= 0) && (comparaDATA((*xp)->val.nascita, giorno2) <= 0) ) {
            t = *xp;
            *xp = (*xp)->next;
            i = t->val;
            free(t);
            break;
        }
    }
    return i;
}