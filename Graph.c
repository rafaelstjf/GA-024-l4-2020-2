#include "Graph.h"
#define WHITE 0
#define GRAY 1
#define BLACK 2
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
    int d; //discovery time
    int t; //end time
    int visited;
} Vertex;
struct graph
{
    Vertex *vertices;
    unsigned int num_vertices;
};
static Vertex *create_vertex(int id, Vertex *next, Edge *edges, int num_edges)
{
    Vertex *n = (Vertex *)malloc(sizeof(Vertex));
    n->id = id;
    n->next = next;
    n->edges = edges;
    n->num_edges = num_edges;
    n->d = 0;
    n->t = 0;
    return n;
}
static Edge *create_edge(int id, Edge *next, int weight)
{
    Edge *e = (Edge *)malloc(sizeof(Edge));
    e->id = id;
    e->next = next;
    e->weight = weight;
}
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
        g->vertices = create_vertex(0, NULL, NULL, 0);
        Vertex *it = g->vertices;
        for (int i = 1; i < n; i++)
        {
            it->next = create_vertex(i, NULL, NULL, 0);
            it = it->next;
        }
    }
    return g;
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
                    {
                        it->edges = create_edge(v2, NULL, weight);
                        it->num_edges++;
                    }
                    else
                    {
                        Edge *ed = create_edge(v2, ant->next, weight);
                        ant->next = ed;
                        it->num_edges++;
                    }
                }
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
                    (*a)[ind] = (int *)ed->id;
                    ind++;
                    ed = ed->next;
                }
                return it->num_edges;
            }
            it = it->next;
        }
    }
    (*a) = NULL;
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
static void set_dfsDiscoverytime(Graph *g, int id, int time)
{
    if (g)
    {
        int i = 0;
        Vertex *it = g->vertices;
        while (it->id != id)
        {
            it = it->next;
        }
        if (it)
            it->d = time;
    }
}
static int get_dfsDiscoverytime(Graph *g, int id)
{
    if (g)
    {
        int i = 0;
        Vertex *it = g->vertices;
        while (it->id != id)
        {
            it = it->next;
        }
        if (it)
            return it->d;
        else
            return -1;
    }
}
static void set_dfsEndtime(Graph *g, int id, int time)
{
    if (g)
    {
        int i = 0;
        Vertex *it = g->vertices;
        while (it->id != id)
        {
            it = it->next;
        }
        if (it)
            it->t = time;
    }
}
static int get_dfsEndtime(Graph *g, int id)
{
    if (g)
    {
        int i = 0;
        Vertex *it = g->vertices;
        while (it->id != id)
        {
            it = it->next;
        }
        if (it)
            return it->t;
        else
            return -1;
    }
}
static int get_id(Graph *g, int pos)
{
    if (!g)
        return -1;
    if (g->num_vertices < pos)
        return -1;
    Vertex *it = g->vertices;
    int i = 0;
    while (it && i < pos)
    {
        it = it->next;
    }
    if (it)
        return it->id;
}
static int get_pos(Graph *g, int id)
{
    if (!g)
        return -1;
    Vertex *it = g->vertices;
    int i = 0;
    while (it && it->id != id)
    {
        it = it->next;
        i++;
    }
    if (it)
        return i;
    return -1;
}
static int dfs_visit(Graph *g, int u, int total_t, int *color)
{
    color[u] = GRAY;
    set_dfsDiscoverytime(g, get_id(g, u), ++total_t);
    int *arr = NULL;
    int n = graph_getAdjacentVertices(g, get_id(g, u), &arr);
    if (arr)
    {
        for (int i = 0; i < n; i++)
        {
            int v = get_pos(g, arr[i]);
            if (color[v] == WHITE)
                total_t = dfs_visit(g, v, total_t, color);
        }
        free(arr);
    }
    printf("No visitado: %d\n", get_id(g, u));
    color[u] = BLACK;
    set_dfsEndtime(g, get_id(g, u), ++total_t);
    return total_t;
}
void graph_dfs(Graph *g)
{
    int total_t = 0;
    int num_vertices = graph_getVertexCount(g);
    int *color = (int *)malloc(sizeof(int *) * num_vertices);
    for (int i = 0; i < num_vertices; i++)
        color[i] = WHITE;
    for (int u = 0; u < num_vertices; u++)
    {
        if (color[u] == WHITE)
            total_t = dfs_visit(g, u, total_t, color);
    }
    fprintf(stdout, "Total t: %d\n", total_t);
    free(color);
}
static Vertex *get_vertex(Graph *g, int id)
{
    if (!g)
        return NULL;
    Vertex *it = g->vertices;
    while (it && it->id != id)
        it = it->next;
    return it;
}
void graph_dfs_stack(Graph *g)
{
    if (!g)
        return;
    Vertex *it = g->vertices;
    while (it)
    {
        it->visited = 0;
        it = it->next;
    }
    it = g->vertices;
    Stack *s = stack_create(g->num_vertices);
    while (it)
    {
        if (!it->visited)
        {
            stack_push(s, it->id);
            while (!stack_empty(s))
            {
                int *arr = NULL;
                int id = 0;
                if (!stack_pop(s, &id))
                    return;
                Vertex *temp = get_vertex(g, id);
                temp->visited = 1;
                int n = graph_getAdjacentVertices(g, id, &arr);

                printf("No visitado: %d\n", id);
                if (arr)
                {
                    for (int i = 0; i < n; i++)
                    {
                        temp = get_vertex(g, arr[i]);
                        if (temp && !temp->visited)
                            stack_push(s, arr[i]);
                    }
                    free(arr);
                }
            }
        }
        it = it->next;
    }
}
int graph_checkCicle(Graph *g)
{
    if (!g)
        return 0;
    Vertex *it = g->vertices;
    while (it)
    {
        it->visited = 0;
        it = it->next;
    }
    it = g->vertices;
    Stack *s = stack_create(g->num_vertices);
    while (it)
    {
        if (!it->visited)
        {
            stack_push(s, it->id);
            while (!stack_empty(s))
            {
                int *arr = NULL;
                int id = 0;
                if (!stack_pop(s, &id))
                    return 0;
                Vertex *temp = get_vertex(g, id);
                temp->visited = 1;
                int n = graph_getAdjacentVertices(g, id, &arr);
                if (arr)
                {
                    for (int i = 0; i < n; i++)
                    {
                        temp = get_vertex(g, arr[i]);
                        if (temp && !temp->visited)
                            stack_push(s, arr[i]);
                        else
                            return 1;
                    }
                    free(arr);
                }
            }
        }
        it = it->next;
        Vertex *it2 = g->vertices;
        while (it2)
        {
            it2->visited = 0;
            it2 = it2->next;
        }
    }
    return 0;
}