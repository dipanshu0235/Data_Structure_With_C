// Prim and Kruskal
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#define LIMIT 50
#define MAX_EDGES (LIMIT * (LIMIT - 1) / 2)
typedef struct Edge {
    int from, to, weight;
} Edge;
static int vertices, weight[LIMIT][LIMIT];
static int compareEdges(const void *left, const void *right) {
    const Edge *a = left, *b = right;
    return (a->weight > b->weight) - (a->weight < b->weight);
}
static void prim(void) {
    int used[LIMIT] = {
        0
    }, chosen = 0;
    long long total = 0;
    puts("Prim selected edges (minimum spanning forest):");
    for (int start = 0; start < vertices; ++start) if (!used[start]) {
        used[start] = 1;
        for (;;) {
            int bestWeight = INT_MAX, from = -1, to = -1;
            for (int i = 0; i < vertices; ++i) if (used[i]) for (int j = 0; j < vertices; ++j)
            if (!used[j] && weight[i][j] != 0 && weight[i][j] < bestWeight) {
                bestWeight = weight[i][j];
                from = i;
                to = j;
            }
            if (to < 0) break;
            used[to] = 1;
            ++chosen;
            total += bestWeight;
            printf("%d -- %d (weight %d)\n", from, to, bestWeight);
        }
    }
    if (vertices == 1) puts("No edges are needed.");
    if (chosen == vertices - 1) printf("MST total cost: %lld\n", total);
    else printf("Graph is disconnected; minimum spanning forest cost: %lld\n", total);
}
static int findRoot(int parent[], int v) {
    if (parent[v] != v) parent[v] = findRoot(parent, parent[v]);
    return parent[v];
}
static int unite(int parent[], int rank[], int a, int b) {
    a = findRoot(parent, a);
    b = findRoot(parent, b);
    if (a == b) return 0;
    if (rank[a] < rank[b]) parent[a] = b;
    else if (rank[a] > rank[b]) parent[b] = a;
    else {
        parent[b] = a;
        ++rank[a];
    }
    return 1;
}
static void kruskal(void) {
    Edge edges[MAX_EDGES];
    int count = 0, parent[LIMIT], rank[LIMIT] = {
        0
    }, chosen = 0;
    long long total = 0;
    for (int i = 0; i < vertices; ++i) {
        parent[i] = i;
        for (int j = i + 1; j < vertices; ++j) if (weight[i][j] != 0) edges[count++] = (Edge) {
            i, j, weight[i][j]
        };
    }
    qsort(edges, (size_t)count, sizeof(edges[0]), compareEdges);
    puts("Kruskal selected edges (minimum spanning forest):");
    for (int i = 0; i < count && chosen < vertices - 1; ++i) if (unite(parent, rank, edges[i].from, edges[i].to)) {
        ++chosen;
        total += edges[i].weight;
        printf("%d -- %d (weight %d)\n", edges[i].from, edges[i].to, edges[i].weight);
    }
    if (vertices == 1) puts("No edges are needed.");
    if (chosen == vertices - 1) printf("MST total cost: %lld\n", total);
    else printf("Graph is disconnected; minimum spanning forest cost: %lld\n", total);
}
int main(void) {
    printf("Number of vertices (1-%d): ", LIMIT);
    if (scanf("%d", &vertices) != 1 || vertices < 1 || vertices > LIMIT) return 1;
    puts("Enter undirected weighted adjacency matrix; 0 means no edge (nonzero weights, including negatives, are allowed):");
    for (int i = 0; i < vertices; ++i) for (int j = 0; j < vertices; ++j) if (scanf("%d", &weight[i][j]) != 1) return 1;
    for (int i = 0; i < vertices; ++i) for (int j = i + 1; j < vertices; ++j) if (weight[i][j] != weight[j][i]) {
        puts("Undirected matrix must be symmetric.");
        return 1;
    }
    puts("\nPrim's algorithm:");
    prim();
    puts("\nKruskal's algorithm:");
    kruskal();
    return 0;
}
