// prims algorithm

// Prim's Algorithm in C

#include<stdio.h>
#include<stdbool.h> 

int edge, vertex, i, j, start;

void prims(int array[vertex][vertex]){
  edge = 0;
  int selected[vertex];
  memset(selected, false, sizeof(selected));

  selected[start] = true;

  int x;
  int y;

  while (edge < vertex - 1) {

    int min = 1000000;
    x = 0;
    y = 0;

    for (i = 0; i < vertex; i++) {
      if (selected[i]) {

        for (j = 0; j < vertex; j++) {

          if (!selected[j] && array[i][j]) {  // not in selected and there is an edge
            if (min > array[i][j]) {
              min = array[i][j];
              x = i;
              y = j;
            }
          }

        }

      }
    }
    printf("%d - %d : %d\n", x, y, array[x][y]);
    selected[y] = true;
    edge++;
  }

}



int main() {
  printf("Enter no of vertices : ");
  scanf("%d", &vertex);

  int array[vertex][vertex];

  printf("\nEnter edges : \n");

  for (i = 0; i < vertex; i++){
    for (j = 0; j < vertex; j++){
      scanf("%d", &array[i][j]);
    }    
  }
  
  printf("\nStarting point : ");
  scanf("%d", &start);

  prims(array);

  return 0;
}