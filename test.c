#include <stdio.h>
#include <stdbool.h>

#define MAX_CITIES 100 // maximum number of cities

int graph[MAX_CITIES][MAX_CITIES]; // adjacency matrix
bool visited[MAX_CITIES]; // to keep track of visited nodes

// function to add an edge between two cities
void addEdge(int u, int v) {
    graph[u][v] = 1; // adding edge from u to v
}

// function to perform BFS traversal
void BFS(int start, int n) {
    int queue[MAX_CITIES], front = 0, rear = 0; // initialize queue for BFS
    visited[start] = true; // mark the starting node as visited
    queue[rear++] = start; // add the starting node to the queue

    while (front < rear) { // repeat until the queue is empty
        int u = queue[front++]; // get the next node to process
        printf("%d ", u); // print the node
        for (int v = 0; v < n; v++) { // iterate through all nodes
            if (graph[u][v] == 1 && !visited[v]) { // if there is an edge from u to v and v is not visited
                visited[v] = true; // mark v as visited
                queue[rear++] = v; // add v to the queue
            }
        }
    }
}

int main() {
    int choice, n, start;
    printf("Graph Menu\n");
    printf("1. Create a graph of cities\n");
    printf("2. BFS\n");
    printf("3. Exit\n");

    do {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("\nEnter the number of cities: ");
                scanf("%d", &n);
                printf("Enter the adjacency matrix:\n");
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        scanf("%d", &graph[i][j]);
                    }
                }
                break;

            case 2:
                printf("\nEnter the starting node: ");
                scanf("%d", &start);
                start = start - 1;
                for (int i = 0; i < n; i++) {
                    visited[i] = false; // initialize visited array
                }
                printf("Nodes reachable from node %d using BFS method:\n", start);
                BFS(start, n);
                printf("\n");
                break;

            case 3:
                printf("\nExiting program...\n");
                break;

            default:
                printf("\nInvalid choice. Try again.\n");
        }
    } while (choice != 3);

    return 0;
}
