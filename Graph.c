#include "Graph.h"

typedef struct edge
{
    int id;
    struct edge *next;
    int weight;
} Edge;
typedef struct vertex
{
    int id;
    struct vertex *next;
    Edge *edges;
    int num_edges;
} Vertex;
struct graph
{
    Vertex *vertices;
    unsigned int num_vertices;
};

Graph *graph_createEmpty()
{
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->vertices = NULL;
    g->num_vertices = 0;
    return g;
}
Graph *graph_create(int n)
{
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->vertices = NULL;
    g->num_vertices = n;
    if (n >= 1)
    {
        g->vertices = (Vertex *)malloc(sizeof(Vertex));
        g->vertices->edges = NULL;
        g->vertices->id = 0;
        g->vertices->next = NULL;
        g->vertices->num_edges = 0;
        Vertex *it = g->vertices;
        for (int i = 1; i < n; i++)
        {
            it->next = (Vertex *)malloc(sizeof(Vertex));
            it->next->edges = NULL;
            it->next->id = i;
            it->next->next = NULL;
            it->next->num_edges = 0;
            it = it->next;
        }
    }
    return g;
}
static Vertex *create_vertex(int id, Vertex *next, Edge *edges, int num_edges)
{
    Vertex *n = (Vertex *)malloc(sizeof(Vertex));
    n->id = id;
    n->next = next;
    n->edges = edges;
    n->num_edges = num_edges;
    return n;
}
static Edge *create_edge(int id, Edge *next, int weight)
{
    Edge *e = (Edge *)malloc(sizeof(Edge));
    e->id = id;
    e->next = next;
    e->weight = weight;
}
void graph_addVertex(Graph *g, int v)
{
    if (g)
    {
        Vertex *it = g->vertices;
        Vertex *ant = NULL;
        int exists = 0;
        if (it)
        {

            while (it && it->id <= v)
            {
                if (it->id == v)
                    exists = 1;
                ant = it;
                it = it->next;
            }
            if (!exists)
            {

                Vertex *n;
                if (it)
                    n = create_vertex(v, it, NULL, 0);
                else
                    n = create_vertex(v, NULL, NULL, 0);
                if (!ant)
                    g->vertices = n;
                else
                    ant->next = n;
            }
        }
        else
            g->vertices = create_vertex(v, NULL, NULL, 0);
        g->num_vertices++;
    }
}
void graph_removeVertex(Graph *g, int v)
{
    if (g)
    {
        Vertex *ant_v = NULL;
        Vertex *it = g->vertices;
        Vertex *temp = NULL;
        int clear = 0;
        while (it)
        {
            if (it->id == v)
            {
                if (ant_v == NULL)
                    g->vertices = it->next;
                else
                    ant_v->next = it->next;

                temp = it;
                clear = 1;
                g->num_vertices--;
            }
            else
            {
                Edge *ed = it->edges;
                Edge *ant_ed = NULL;
                Edge *temp_e = NULL;
                while (ed && ed->id <= v)
                {

                    if (ed->id == v)
                    {
                        if (!ant_ed)
                        {
                            it->edges = ed->next;
                        }
                        else
                        {
                            ant_ed->next = ed->next;
                        }
                        temp_e = ed;
                        it->num_edges--;
                        break;
                    }
                    if (temp_e)
                    {
                        free(temp_e);
                        temp_e = NULL;
                    }
                    else
                        ant_ed = ed;
                    ed = ed->next;
                }
            }
            if (clear)
                clear = 0;
            else
                ant_v = it;

            it = it->next;
        }
        free(temp);
    }
}
int graph_hasVertex(Graph *g, int v)
{
    if (g)
    {
        Vertex *it = g->vertices;
        while (it)
        {
            if (it->id == v)
                return 1;
            else if (it->id > v)
                return 0;
            it = it->next;
        }
    }
    return 0;
}
int graph_getVertexCount(Graph *g)
{
    return (g) ? g->num_vertices : 0;
}
void graph_addEdge(Graph *g, int v1, int v2, int weight)
{
    if (g)
    {
        Vertex *it = g->vertices;
        while (it && it->id <= v1)
        {
            if (it->id == v1)
            {
                if (graph_hasVertex(g, v2))
                {
                    Edge *e_it = it->edges;
                    Edge *ant = NULL;
                    while (e_it && e_it->id <= v2)
                    {
                        ant = e_it;
                        e_it = e_it->next;
                        if (e_it->id == v2)
                        {
                            //updates the weight
                            e_it->weight = weight;
                            break;
                        }
                    }
                    if (!ant)
                        it->edges = create_edge(v2, NULL, weight);
                    else
                    {
                        Edge *ed = create_edge(v2, ant->next, weight);
                        ant->next = ed;
                    }
                }
                it->num_edges++;
                break;
            }
            it = it->next;
        }
    }
}
void graph_removeEdge(Graph *g, int v1, int v2)
{
    if (g)
    {
        Vertex *it = g->vertices;
        while (it && it->id <= v1)
        {
            if (it->id == v1)
            {
                if (graph_hasVertex(g, v2))
                {
                    Edge *ed = it->edges;
                    Edge *ant_ed = NULL;
                    Edge *temp_e = NULL;
                    while (ed)
                    {
                        if (ed->id == v2)
                        {
                            if (!ant_ed)
                            {
                                it->edges = ed->next;
                            }
                            else
                            {
                                ant_ed->next = ed->next;
                            }
                            temp_e = ed;
                            break;
                        }
                        ed = ed->next;
                        free(temp_e);
                    }
                }
                it->num_edges--;
                break;
            }
            it = it->next;
        }
    }
}
int graph_hasEdge(Graph *g, int v1, int v2)
{
    if (g)
    {
        Vertex *it = g->vertices;
        while (it && it->id <= v1)
        {
            if (it->id == v1)
            {
                if (graph_hasVertex(g, v2))
                {
                    Edge *ed = it->edges;
                    while (ed)
                    {
                        if (ed->id == v2)
                        {
                            return 1;
                        }
                        else if (ed->id > v2)
                            return 0;
                    }
                }
                break;
            }
            it = it->next;
        }
    }
    return 0;
}
int graph_getEdgeWeight(Graph *g, int v1, int v2)
{
    if (g)
    {
        Vertex *it = g->vertices;
        while (it && it->id <= v1)
        {
            if (it->id == v1)
            {
                if (graph_hasVertex(g, v2))
                {
                    Edge *ed = it->edges;
                    while (ed)
                    {
                        if (ed->id == v2)
                        {
                            return ed->weight;
                        }
                        else if (ed->id > v2)
                            return 0;
                    }
                }
                break;
            }
            it = it->next;
        }
    }
    return 0;
}
int graph_getAdjacentVertices(Graph *g, int v, int **a)
{
    if (g)
    {
        Vertex *it = g->vertices;
        while (it && it->id <= v)
        {
            if (it->id == v)
            {
                if (it->num_edges == 0)
                {
                    (*a) = NULL;
                    return 0;
                }
                Edge *ed = it->edges;
                (*a) = (int *)malloc(sizeof(int) * it->num_edges);
                int ind = 0;
                while (ed)
                {
                    a[ind] = (int *)ed->id;
                    ind++;
                    ed = ed->next;
                }
                return it->num_edges;
            }
            it = it->next;
        }
    }
    return 0;
}
void graph_print(Graph *g)
{
    if (g)
    {
        Vertex *it = g->vertices;
        while (it)
        {
            fprintf(stdout, "Vertex: %d Edges: ", it->id);
            Edge *it_e = it->edges;
            while (it_e && it_e->next)
            {
                fprintf(stdout, "(%d, %d), ", it_e->id, it_e->weight);
                it_e = it_e->next;
            }
            if (it_e)
                fprintf(stdout, "(%d, %d)\n", it_e->id, it_e->weight);
            else
                fprintf(stdout, "\n");
            it = it->next;
        }
    }
}