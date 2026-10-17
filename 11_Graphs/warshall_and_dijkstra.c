// Warshall and Dijkstra
#include <limits.h>
#include <stdio.h>
#define LIMIT 50
#define INF (LLONG_MAX / 4)
static void warshall(int n, int weight[LIMIT][LIMIT]) {
    int reach[LIMIT][LIMIT];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            reach[i][j] = (i == j || weight[i][j] != 0);
        }
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);
            }
        }
    }
    puts("Transitive closure (1 means a path exists; diagonal includes each vertex itself):");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) printf("%d ", reach[i][j]);
        putchar('\n');
    }
}
static void dijkstra(int n, int weight[LIMIT][LIMIT], int source) {
    long long distance[LIMIT];
    int visited[LIMIT] = {0};
    for (int i = 0; i < n; ++i) distance[i] = INF;
    distance[source] = 0;
    for (int step = 0; step < n; ++step) {
        int nearest = -1;
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && (nearest < 0 || distance[i] < distance[nearest])) {
                nearest = i;
            }
        }
        if (nearest < 0 || distance[nearest] == INF) break;
        visited[nearest] = 1;
        for (int next = 0; next < n; ++next) {
            if (weight[nearest][next] > 0 && distance[nearest] + weight[nearest][next] < distance[next]) {
                distance[next] = distance[nearest] + weight[nearest][next];
            }
        }
    }
    printf("Shortest distances from vertex %d:\n", source);
    for (int i = 0; i < n; ++i) {
        if (distance[i] == INF) printf("%d: unreachable\n", i);
        else printf("%d: %lld\n", i, distance[i]);
    }
}
int main(void) {
    int n, weight[LIMIT][LIMIT], directed, source;
    printf("Number of vertices (1-%d): ", LIMIT);
    if (scanf("%d", &n) != 1 || n < 1 || n > LIMIT) return 1;
    printf("Directed graph? (1 yes, 0 no): ");
    if (scanf("%d", &directed) != 1 || (directed != 0 && directed != 1)) return 1;
    puts("Enter weighted adjacency matrix; use 0 for no edge and non-negative weights for edges:");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (scanf("%d", &weight[i][j]) != 1 || weight[i][j] < 0) {
                puts("Invalid weight.");
                return 1;
            }
        }
    }
    if (!directed) {
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (weight[i][j] != weight[j][i]) {
                    puts("Undirected matrix must be symmetric.");
                    return 1;
                }
            }
        }
    }
    printf("Source vertex (0-%d): ", n - 1);
    if (scanf("%d", &source) != 1 || source < 0 || source >= n) {
        puts("Invalid vertex.");
        return 1;
    }
    puts("\nWarshall:");
    warshall(n, weight);
    puts("\nDijkstra:");
    dijkstra(n, weight, source);
    return 0;
}
