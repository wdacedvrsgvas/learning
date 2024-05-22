#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100

typedef struct Edge
{
    int destination;
    int weight;
    struct Edge *next;
} Edge;

typedef struct Vertex
{
    int id;
    Edge *edges;
    struct Vertex *next;
} Vertex;

typedef struct Graph
{
    Vertex *vertices[MAX_VERTICES];
    int vertex_count;
} Graph;

// Function prototypes
Graph *create_graph();
Vertex *create_vertex(int id);
Edge *create_edge(int destination, int weight);
void add_vertex(Graph *graph, int id);
void add_edge(Graph *graph, int src, int dest, int weight);
void delete_edge(Graph *graph, int src, int dest);
void delete_vertex(Graph *graph, int id);
void dfs(Graph *graph, int start_vertex);
void bfs(Graph *graph, int start_vertex);
void find_path(Graph *graph, int start_vertex, int end_vertex);
void print_graph(Graph *graph);
void free_graph(Graph *graph);

int main()
{
    Graph *graph = create_graph();

    add_vertex(graph, 0);
    add_vertex(graph, 1);
    add_vertex(graph, 2);
    add_vertex(graph, 3);
    add_vertex(graph, 4);

    add_edge(graph, 0, 1, 10);
    add_edge(graph, 0, 4, 20);
    add_edge(graph, 1, 2, 30);
    add_edge(graph, 1, 3, 40);
    add_edge(graph, 3, 4, 50);

    print_graph(graph);

    printf("DFS starting from vertex 0:\n");
    dfs(graph, 0);

    printf("BFS starting from vertex 0:\n");
    bfs(graph, 0);

    printf("Finding path from vertex 0 to vertex 3:\n");
    find_path(graph, 0, 3);

    delete_edge(graph, 1, 2);
    delete_vertex(graph, 3);

    print_graph(graph);

    free_graph(graph);

    return 0;
}

Graph *create_graph()
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->vertex_count = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
    {
        graph->vertices[i] = NULL;
    }
    return graph;
}

Vertex *create_vertex(int id)
{
    Vertex *vertex = (Vertex *)malloc(sizeof(Vertex));
    vertex->id = id;
    vertex->edges = NULL;
    vertex->next = NULL;
    return vertex;
}

Edge *create_edge(int destination, int weight)
{
    Edge *edge = (Edge *)malloc(sizeof(Edge));
    edge->destination = destination;
    edge->weight = weight;
    edge->next = NULL;
    return edge;
}

void add_vertex(Graph *graph, int id)
{
    if (graph->vertex_count >= MAX_VERTICES)
    {
        printf("Max vertices limit reached.\n");
        return;
    }
    Vertex *vertex = create_vertex(id);
    graph->vertices[graph->vertex_count++] = vertex;
}

void add_edge(Graph *graph, int src, int dest, int weight)
{
    Vertex *vertex = graph->vertices[src];
    if (vertex == NULL)
    {
        printf("Source vertex not found.\n");
        return;
    }
    Edge *edge = create_edge(dest, weight);
    edge->next = vertex->edges;
    vertex->edges = edge;
}

void delete_edge(Graph *graph, int src, int dest)
{
    Vertex *vertex = graph->vertices[src];
    if (vertex == NULL)
    {
        printf("Source vertex not found.\n");
        return;
    }
    Edge *prev_edge = NULL;
    Edge *edge = vertex->edges;
    while (edge != NULL && edge->destination != dest)
    {
        prev_edge = edge;
        edge = edge->next;
    }
    if (edge == NULL)
    {
        printf("Edge not found.\n");
        return;
    }
    if (prev_edge == NULL)
    {
        vertex->edges = edge->next;
    }
    else
    {
        prev_edge->next = edge->next;
    }
    free(edge);
}

void delete_vertex(Graph *graph, int id)
{
    if (graph->vertices[id] == NULL)
    {
        printf("Vertex not found.\n");
        return;
    }
    for (int i = 0; i < graph->vertex_count; i++)
    {
        if (graph->vertices[i] != NULL)
        {
            delete_edge(graph, i, id);
        }
    }
    free(graph->vertices[id]);
    graph->vertices[id] = NULL;
}

void dfs_util(Graph *graph, int vertex, int *visited)
{
    visited[vertex] = 1;
    printf("%d ", vertex);

    Edge *edge = graph->vertices[vertex]->edges;
    while (edge != NULL)
    {
        if (!visited[edge->destination])
        {
            dfs_util(graph, edge->destination, visited);
        }
        edge = edge->next;
    }
}

void dfs(Graph *graph, int start_vertex)
{
    int visited[MAX_VERTICES] = {0};
    dfs_util(graph, start_vertex, visited);
    printf("\n");
}

void bfs(Graph *graph, int start_vertex)
{
    int visited[MAX_VERTICES] = {0};
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    visited[start_vertex] = 1;
    queue[rear++] = start_vertex;

    while (front < rear)
    {
        int vertex = queue[front++];
        printf("%d ", vertex);

        Edge *edge = graph->vertices[vertex]->edges;
        while (edge != NULL)
        {
            if (!visited[edge->destination])
            {
                visited[edge->destination] = 1;
                queue[rear++] = edge->destination;
            }
            edge = edge->next;
        }
    }
    printf("\n");
}

void find_path_util(Graph *graph, int start_vertex, int end_vertex, int *visited, int *path, int *path_index)
{
    visited[start_vertex] = 1;
    path[(*path_index)++] = start_vertex;

    if (start_vertex == end_vertex)
    {
        for (int i = 0; i < *path_index; i++)
        {
            printf("%d ", path[i]);
        }
        printf("\n");
    }
    else
    {
        Edge *edge = graph->vertices[start_vertex]->edges;
        while (edge != NULL)
        {
            if (!visited[edge->destination])
            {
                find_path_util(graph, edge->destination, end_vertex, visited, path, path_index);
            }
            edge = edge->next;
        }
    }

    (*path_index)--;
    visited[start_vertex] = 0;
}

void find_path(Graph *graph, int start_vertex, int end_vertex)
{
    int visited[MAX_VERTICES] = {0};
    int path[MAX_VERTICES];
    int path_index = 0;
    find_path_util(graph, start_vertex, end_vertex, visited, path, &path_index);
}

void print_graph(Graph *graph)
{
    for (int i = 0; i < graph->vertex_count; i++)
    {
        if (graph->vertices[i] != NULL)
        {
            printf("Vertex %d:\n", graph->vertices[i]->id);
            Edge *edge = graph->vertices[i]->edges;
            while (edge != NULL)
            {
                printf("  -> %d (weight %d)\n", edge->destination, edge->weight);
                edge = edge->next;
            }
        }
    }
}

void free_graph(Graph *graph)
{
    for (int i = 0; i < graph->vertex_count; i++)
    {
        if (graph->vertices[i] != NULL)
        {
            Edge *edge = graph->vertices[i]->edges;
            while (edge != NULL)
            {
                Edge *temp = edge;
                edge = edge->next;
                free(temp);
            }
            free(graph->vertices[i]);
        }
    }
    free(graph);
}
