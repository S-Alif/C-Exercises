// priority scheduling - non preemptive

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int n;

// Structure to represent a process
typedef struct process {
  char process[10];
  int arrival_time;
  int burst_time;
  int priority;
  int completion_time;
  int waiting_time;
  int turnaround_time;

  bool completed;
}process;

process *array;

int calculate(int high_priority, int current_time){
  array[high_priority].completion_time = current_time + array[high_priority].burst_time;
  array[high_priority].turnaround_time = array[high_priority].completion_time - array[high_priority].arrival_time;
  array[high_priority].waiting_time = array[high_priority].turnaround_time - array[high_priority].burst_time;

  current_time = array[high_priority].completion_time;
  array[high_priority].completed = true;

  return current_time;
}

// find the most priority process
int most_priority(process array[], int current_time) {
  int highest_priority = -1;
  int current_priority = 100;

  for (int i = 0; i < n; i++) {
    if (!array[i].completed && array[i].arrival_time <= current_time) {
      if (highest_priority == -1 || array[i].priority < current_priority) {
        highest_priority = i;
        current_priority = array[i].priority;
      }
    }
  }

  return highest_priority;
}

// enter data
void enterData(int indexPosition){
  printf("enter process name : ");
  scanf("%s", array[indexPosition].process);

  printf("enter burst time : ");
  scanf("%d", &array[indexPosition].burst_time);

  printf("enter arrival time : ");
  scanf("%d", &array[indexPosition].arrival_time);

  printf("enter priority : ");
  scanf("%d", &array[indexPosition].priority);

  printf("----------------------------\n");
}

int main() {
  process sorted;
  float avgTat=0, avgWt=0;
  printf("Enter the number of process: ");
  scanf("%d", &n);

  array = malloc(sizeof(process) * n);

  printf("\n[Note : lower value higher priority]\n\n");

  // Input process details
  for (int i = 0; i < n; i++){
    enterData(i);
  }
  int current_time = array[0].arrival_time;

  for (int i = 0; i < n; i++) {
    if (array[i].arrival_time < current_time){
      current_time = array[i].arrival_time;
    }
  }

  // Execute array
  while (true){
    int high_priority = most_priority(array, current_time);
    if (high_priority == -1){
      break;
    }
    current_time = calculate(high_priority, current_time);
  }

  for (int i = 0; i < n; i++){
    for(int j = i+1; j < n; j++){
      if(array[i].completion_time > array[j].completion_time){
        sorted = array[i];
        array[i] = array[j];
        array[j] = sorted;
      }
    }
  }


  // Display results
  printf("\nprocess\tPriority\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
  for (int i = 0; i < n; i++){
    printf("%s\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", array[i].process, array[i].priority, array[i].arrival_time,
               array[i].burst_time, array[i].completion_time,
               array[i].turnaround_time, array[i].waiting_time);
  }

  for (int i = 0; i < n; i++){
    avgTat = avgTat + array[i].turnaround_time;
    avgWt = avgWt + array[i].waiting_time;
  }

  printf("\n\nAverage turn around time : %.2f", avgTat / n);
  printf("\nAverage turn waiting time : %.2f", avgWt / n);

  return 0;
}