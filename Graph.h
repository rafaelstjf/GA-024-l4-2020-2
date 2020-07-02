#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
typedef struct graph Graph;

Graph *graph_createEmpty(); //cria grafo vazio
Graph *graph_create( int n ); //cria com n vértices (ids 0 a n-1); e 0 arestas
void graph_addVertex( Graph *g, int v );
void graph_removeVertex( Graph *g, int v ); //remove tb arestas associadas
int graph_hasVertex( Graph *g, int v );
int graph_getVertexCount(Graph* g);
void graph_addEdge( Graph *g, int v1, int v2, int weight );
void graph_removeEdge( Graph *g, int v1, int v2 );
int graph_hasEdge( Graph *g, int v1, int v2 );
int graph_getEdgeWeight( Graph *g, int v1, int v2 );
int graph_getAdjacentVertices( Graph *g, int v, int **a ); //lista de vértices adjacentes a v devolvida em a (alocada dinamicamente)
// ou NULL, eretorno é o tamanho dessa lista
void graph_print(Graph* g);
void graph_dfs(Graph *g);
void graph_dfs_stack(Graph *g);
int graph_checkCicle(Graph* g);
#endif