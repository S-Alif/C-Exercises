#include <stdio.h>

int matrix[10][10]; // adjacency matrix to store the graph
int visit[10]; // array to keep track of visit vertices
int n; // number of vertices in the graph

// create a graph
void create_graph(){
    printf("Enter number of vertices : ");
    scanf("%d", &n);

    printf("Enter adjacency matrix values : \n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &matrix[i][j]);
        }
    }
    
    printf("\nvalues have been entered\n\n");
}

//DFS
void dfs(int start){
    visit[start] = 1; // mark the start as visit
    
    // explore all adjacent vertices
    for(int i = 0; i < n; i++){
        if(matrix[start][i] == 1 && visit[i] == 0){
            printf("%d -> %d\n", start+1, i+1); // print the edge from the visited vertex to the adjacent start
            dfs(i); // recursive call to the adjacent vertex
        }
    }
}

int main(){
    int action = 1, choice, start;

    printf("Perform actions on graph : \n");
    printf("\t1. Create a graph\n\t2. DFS\n\t3. Exit");

    while(action == 1){
        printf("\nYour Choice : ");
        scanf("%d", &choice);

        switch (choice){
        case 1:
            create_graph();
            break;
        case 2:
            for(int i = 0; i < n; i++){
                visit[i] = 0;
            }
            printf("Enter the starting vertex : ");
            scanf("%d", &start);
            start = start - 1;
            dfs(start);
            break;
        case 3:
            printf("Program Ends");
            action = 0;
            break;
        default: printf("\nInvalid Choice\n\n");
            break;
        }
    }
    return 0;
}