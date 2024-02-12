#include <stdio.h>
#ifndef _SYMBTAB_h
#define _SYMBTAB_h
#define STRMAX 30

typedef struct symbtab_s * ST;

ST STinit(int maxN);
int STsearch(ST st, char * nome);
int STfill(ST st, char * nome);
void STread(ST st, FILE * fp);
int STcount(ST st);
void STprintNodeName(ST st, int i);
void STfree(ST st);
void MergeSort(int A[], int B[], int N, ST st);
void MergeSortR(int a[], int b[], int l, int r, ST st);
void Merge(int a[], int b[], int l, int q, int r, ST st);


#endif