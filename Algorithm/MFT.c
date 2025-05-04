// Multiprogramming first fit

#include <stdio.h>
#include <stdlib.h>

int total_memory, n, memory_partition;

typedef struct process{
  int size, wastage;
}process;

process * array;

void enter_data(int i){
  printf("Memory for process - %d : ", i);
  scanf("%d", &array[i].size);

  array[i].wastage = (memory_partition < array[i].size) ? -1 : (memory_partition - array[i].size);
}

int main() {
  int total_memory_waste = 0, i;
  printf("Enter total memory: ");
  scanf("%d", &total_memory);

  printf("Enter number of process: ");
  scanf("%d", &n);

  array = malloc(sizeof(process) * n);
  memory_partition = total_memory / n;

  for (i = 0; i < n; i++){
    enter_data(i);
  }

  for (i = 0; i < n; i++){
    if(array[i].wastage != -1){
      printf("\nMemory wastage for process - %d = %d", i, array[i].wastage);
      total_memory_waste = total_memory_waste + array[i].wastage;
    }
    else{
      printf("\nprocess - %d cannot execute", i);
    }
  }

  printf("\n total memory wastage = %d", total_memory_waste);

  return 0;  
}