// BFS and DFS using adjacency matrix
#include <stdio.h>
#define LIMIT 50
static int graph[LIMIT][LIMIT], visited[LIMIT], vertices;
static void depthFirst(int v) {
    visited[v] = 1;
    printf("%d ", v);
    for (int i = 0; i < vertices; ++i) if (graph[v][i] && !visited[i]) depthFirst(i);
}
static void breadthFirstComponent(int start) {
    int queue[LIMIT], front = 0, rear = 0;
    visited[start] = 1;
    queue[rear++] = start;
    while (front < rear) {
        int v = queue[front++];
        printf("%d ", v);
        for (int i = 0; i < vertices; ++i) if (graph[v][i] && !visited[i]) {
            visited[i] = 1;
            queue[rear++] = i;
        }
    }
}
int main(void) {
    int directed;
    printf("Number of vertices (1-%d): ", LIMIT);
    if (scanf("%d", &vertices) != 1 || vertices < 1 || vertices > LIMIT) return 1;
    printf("Directed graph? (1 yes, 0 no): ");
    if (scanf("%d", &directed) != 1 || (directed != 0 && directed != 1)) return 1;
    puts("Enter adjacency matrix values (0=no edge, 1=edge):");
    for (int i = 0; i < vertices; ++i) for (int j = 0; j < vertices; ++j) {
        if (scanf("%d", &graph[i][j]) != 1 || (graph[i][j] != 0 && graph[i][j] != 1)) {
            puts("Matrix values must be 0 or 1.");
            return 1;
        }
    }
    if (!directed) for (int i = 0; i < vertices; ++i) for (int j = i + 1; j < vertices; ++j) if (graph[i][j] != graph[j][i]) {
        puts("Undirected matrix must be symmetric.");
        return 1;
    }
    puts("Adjacency matrix:");
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) printf("%d ", graph[i][j]);
        putchar('\n');
    }
    int source;
    printf("Start vertex (0-%d): ", vertices - 1);
    if (scanf("%d", &source) != 1 || source < 0 || source >= vertices) {
        puts("Invalid vertex.");
        return 1;
    }
    printf("BFS order (source component first): ");
    breadthFirstComponent(source);
    for (int i = 0; i < vertices; ++i) if (!visited[i]) {
        printf("| ");
        breadthFirstComponent(i);
    }
    putchar('\n');
    for (int i = 0; i < vertices; ++i) visited[i] = 0;
    printf("DFS order (source component first): ");
    depthFirst(source);
    for (int i = 0; i < vertices; ++i) if (!visited[i]) {
        printf("| ");
        depthFirst(i);
    }
    putchar('\n');
    return 0;
}
