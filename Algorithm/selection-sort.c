#include<stdio.h>

// selection algorithm fuction
int selectionSort(int a[], int n){
  int i, j, temp;
  for (i = 0; i < n; i++){
    for (j = i+1; j < n; j++){
      if(a[j] < a[i]){
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
      }      
    }
  }

  printf("Sorted array : ");
  for (i = 0; i < n; i++){
    printf("%d\t", a[i]);
  }
}

int main(){
  int n;
  printf("Enter array size : ");
  scanf("%d", &n);
  int array[n];

  printf("Enter array value : ");
  for (int i = 0; i < n; i++)  {
    scanf("%d", &array[i]);
  }

  selectionSort(array, n);
  
  return 0;
}