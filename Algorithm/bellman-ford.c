// bellman ford algorithms

#include <stdio.h>
#include <limits.h>

// Function to implement the Bellman-Ford algorithm
void bellmanFord(int graph[][3], int V, int E, int src) {
    int dist[V];

    // Initialize distance array
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
    }

    // Set the distance of the source vertex to 0
    dist[src] = 0;

    // Relax all edges V-1 times
    for (int i = 0; i < V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph[j][0];
            int v = graph[j][1];
            int weight = graph[j][2];

            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Check for negative-weight cycles
    for (int i = 0; i < E; i++) {
        int u = graph[i][0];
        int v = graph[i][1];
        int weight = graph[i][2];

        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("Graph contains negative-weight cycle\n");
            return;
        }
    }

    // Print the distances from the source vertex
    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d\t%d\n", i, dist[i]);
    }
}

int main() {
    int V, E;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    printf("Enter the number of edges: ");
    scanf("%d", &E);

    int graph[E][3];
    printf("Enter the edges (source, destination, weight):\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &graph[i][0], &graph[i][1], &graph[i][2]);
    }

    int src;
    printf("Enter the source vertex: ");
    scanf("%d", &src);

    bellmanFord(graph, V, E, src);

    return 0;
}
