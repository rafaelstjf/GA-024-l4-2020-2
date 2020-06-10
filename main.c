#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(){
    Graph* g = graph_create(10);
    fprintf(stdout, "Criando Grafo vazio.\n");
    graph_print(g);
    fprintf(stdout, "Inserindo um novo vertice de id 32.\n");
    graph_addVertex(g, 32);
    graph_print(g);
    fprintf(stdout, "Inserindo as arestas de peso 1 (32,2), (0,32), (0,15).\n");
    graph_addEdge(g, 32, 2, 1);
    graph_addEdge(g, 0, 32, 1);
    graph_addEdge(g, 0, 15, 1);
    graph_print(g);
    fprintf(stdout, "Removendo o vertice com id 32.\n");
    graph_removeVertex(g, 32);
    graph_print(g);

    return 0;
}