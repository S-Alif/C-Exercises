// graph BFS algorithm

#include<stdio.h>
#include<stdlib.h>

int matrix[10][10], n, visit[10];

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

// BFS
void bfs(){
    int start, j, front = -1, rear = -1, queue[n];
    printf("Enter the starting vertex : ");
    scanf("%d", &start);
    start = start - 1;

    queue[++rear] = start;
    visit[start] = 1;

    printf("The reachable vertices are :");
    while(front != rear){

        j = queue[++front];
        for(int i = 0; i < n; i++){
            if(matrix[j][i] == 1 && visit[i] == 0){
                queue[++rear] = i;
                visit[i] = 1;
                printf("\t%d", i+1);
            }
        }
    }

    printf("\n\n");
}

int main(){
    int action = 1, choice;

    printf("Perform actions on graph : \n");
    printf("\t1. Create a graph\n\t2. BFS\n\t3. Exit\n\n");

    while(action == 1){
        printf("Your Choice : ");
        scanf("%d", &choice);

        switch (choice){
        case 1:
            create_graph();
            break;
        case 2:
            for(int i = 0; i < n; i++){
                visit[i] = 0;
            }
            bfs();
            break;
        case 3:
            printf("Program Ends");
            action = 0;
            break;
        default: printf("\nInvalid Choice\n\n");
            break;
        }
    }
}