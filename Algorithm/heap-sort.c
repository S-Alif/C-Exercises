// heap sort algorithm

#include<stdio.h>

void heapify(int array[], int n, int i){
  int largest = i;
  int left = (2 * i) + 1;
  int right = (2 * i) + 2;

  if (left < n && array[left] > array[largest]){
    largest = left;
  }

  if (right < n && array[right] > array[largest]){
    largest = right;
  }

  if (largest != i){
    int temp = array[i];
    array[i] = array[largest];
    array[largest] = temp;

    heapify(array, n, largest);
  }
}

void heapSort(int array[], int n){
  int i;

  for (i =(n / 2) - 1; i >= 0; i--){
    heapify(array, n, i);
  }

  for (i = n - 1; i > 0; i--){

    int temp = array[0];
    array[0] = array[i];
    array[i] = temp;

    heapify(array, i, 0);
  }
}

int main(){
  int n, i;
  printf("Enter array size : ");
  scanf("%d", &n);

  int array[n];

  printf("Enter array values : ");
  for (i = 0; i < n; i++){
    scanf("%d", &array[i]);
  }

  heapSort(array, n);

  printf("\nSorted array : ");
  for (i = 0; i < n; i++){
    printf("%d\t", array[i]);
  }

  return 0;
}