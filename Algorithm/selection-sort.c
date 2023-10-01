#include<stdio.h>
#include<stdlib.h>

int n;
int *array;

void selectionSort(){
  int i, j, point, temp;

  for (i = 0; i < n; i++){
    point = i;
    for (j = i+1; j < n; j++){
      if (array[j] > array[point]){
        point = j;
      }
    }
    temp = array[i];
    array[i] = array[point];
    array[point] = temp;
  }

  printf("\nSorted array : ");
  for(i = 0; i < n; i++){
    printf("\t%d", array[i]);
  }
}

int main(){
  int i;
  printf("Enter array size: ");
  scanf("%d", &n);

  array = malloc(sizeof(int) * n);  

  printf("Enter array values : ");
  for (i = 0; i < n; i++){
    scanf("%d", &array[i]);
  }

  selectionSort();

  return 0;
}