// quick sort algorithm

#include<stdio.h>
#include<stdlib.h>

int i, n;

void swap(int arr[], int a, int b) {
  int temp = arr[a];
  arr[a] = arr[b];
  arr[b] = temp;
}

int partition(int arr[], int low, int high){
  int pivot = arr[high];
  int i = low - 1;

  for (int j = low; j <= high - 1; j++)  {
    if (arr[j] <= pivot){
      i++;
      swap(arr, i, j);
    }
  }
  swap(arr, i + 1, high);
  return (i + 1);
}

void quickSort(int arr[], int low, int high){
    if (low < high) {
      int pi = partition(arr, low, high);

      quickSort(arr, low, pi - 1);
      quickSort(arr, pi + 1, high);
    }
}

// print the array
void print(int arr[]){
  for(i = 0; i < n; i++){
    printf("%d\t", arr[i]);
  }
}

int main(){
  printf("Enter the size of array : ");
  scanf("%d", &n);

  int array[n];

  printf("Enter array elements : ");
  for (i = 0; i < n; i++){
    scanf("%d", &array[i]);
  }

  quickSort(array, 0, n - 1);

  printf("Array after sorting : ");
  print(array);

  return 0;
}