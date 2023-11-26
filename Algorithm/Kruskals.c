// kruskals algorithm for shortest path

#include <stdio.h>

#define MAX_NODES 100
#define MAX_EDGES 1000

int parent[MAX_NODES];
int rank[MAX_NODES];

typedef struct {
    int source;
    int destination;
    int weight;
} Edge;

Edge edges[MAX_EDGES];

void makeSet(int node) {
    parent[node] = node;
    rank[node] = 0;
}

int findSet(int node) {
    if (node != parent[node]) {
        parent[node] = findSet(parent[node]);
    }
    return parent[node];
}

void unionSets(int node1, int node2) {
    int root1 = findSet(node1);
    int root2 = findSet(node2);

    if (rank[root1] < rank[root2]) {
        parent[root1] = root2;
    } else if (rank[root1] > rank[root2]) {
        parent[root2] = root1;
    } else {
        parent[root1] = root2;
        rank[root2]++;
    }
}

void kruskalsAlgorithm(int numNodes, int numEdges) {
    // Sort edges in non-decreasing order of weight
    for (int i = 0; i < numEdges - 1; i++) {
        for (int j = 0; j < numEdges - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    // Initialize parent and rank arrays
    for (int i = 0; i < numNodes; i++) {
        makeSet(i);
    }

    int mstWeight = 0;
    int mstEdges = 0;

    // Iterate through all edges in sorted order
    for (int i = 0; i < numEdges; i++) {
        int source = edges[i].source;
        int destination = edges[i].destination;
        int weight = edges[i].weight;

        // Check if including this edge forms a cycle
        if (findSet(source) != findSet(destination)) {
            printf("Edge (%d, %d) with weight %d included in MST\n", source, destination, weight);
            mstWeight += weight;
            mstEdges++;
            unionSets(source, destination);
        }
    }

    printf("Total weight of MST: %d\n", mstWeight);
    printf("Total number of edges in MST: %d\n", mstEdges);
}

int main() {
    int numNodes, numEdges;

    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    printf("Enter the edges in the format (source destination weight):\n");
    for (int i = 0; i < numEdges; i++) {
        scanf("%d %d %d", &edges[i].source, &edges[i].destination, &edges[i].weight);
    }

    kruskalsAlgorithm(numNodes, numEdges);

    return 0;
}
