#include <stdio.h>
#include "symbtab.h"
#ifndef _GRAPH_h
#define _GRAPH_h

typedef struct node * link;
typedef struct graph * GRAPH;


static link NEW(int v, link next);
void showList(link head, ST st);
int searchList(link head, int i);
GRAPH GRAPHinitialize(GRAPH G, ST st);
void GRAPHread(GRAPH G, ST st);
void GRAPHshow(GRAPH G, ST st);
void GRAPHshowListAdj(GRAPH G, ST st);
void GRAPHlistVert(GRAPH G, ST st);
void GRAPHgenerateAdjList(GRAPH G, ST st);
int GRAPHverifyMatAdj(GRAPH G, ST st);
int GRAPHverifyListAdj(GRAPH G, ST st);
void GRAPHfree(GRAPH G);


#endif