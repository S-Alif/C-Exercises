// dijkstra algorithm for shortest path

#include <stdio.h>
#include <stdbool.h>

int i, j, n;

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], bool visited[], int V) {
  int min = 100000, min_index;

  for (i = 0; i < V; i++) {
    if (!visited[i] && dist[i] < min) {
      min = dist[i];
      min_index = i;
    }
  }
  return min_index;
}

// Function to print the shortest path distances
void printSolution(int dist[]) {
  printf("\n\nVertex \t Distance from Source\n");
  for (i = 0; i < n; i++) {
    printf("%d \t %d\n", i+1, dist[i]);
  }
}

// Function to perform Dijkstra's algorithm
void dijkstra(int graph[n][n], int src) {
  int dist[n];
  bool visited[n];

  for (int i = 0; i < n; i++) {
    dist[i] = 100000;
    visited[i] = false;
  }

  dist[src] = 0;

  for (i = 0; i < n - 1; i++) {
    int u = minDistance(dist, visited, i);
    visited[u] = true;

    for (j = 0; j < n; j++) {
      if (!visited[j] && graph[u][j] && dist[u] != 100000 &&
        dist[u] + graph[u][j] < dist[j]) {
        dist[j] = dist[u] + graph[u][j];
      }
    }
  }

  printSolution(dist);
}

int main() {

  printf("Enter the number of vertices: ");
  scanf("%d", &n);

  int graph[n][n];

  printf("\nEnter the weighted graph adjacency matrix : \n");
  for (i = 0; i < n; i++){
    for (j = 0; j < n; j++){
      scanf("%d", &graph[i][j]);
    }
  }

  int src;

  printf("\nEnter the source vertex: ");
  scanf("%d", &src);

  if (src < 0 || src >= n){
    printf("\nInvalid source vertex. Please enter a valid vertex.\n");
    return 1;
  }

  dijkstra(graph, src);

  return 0;
}
