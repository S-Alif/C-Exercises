// priority scheduling - preemptive

#include <stdio.h>
#include<stdlib.h>
#include <stdbool.h>

typedef struct srtf{
  char process[10];
  int arrival_time;
  int burst_time;
  int remaining_time;
  int completion_time;
  int waiting_time;
  int turnaround_time;
  int priority;

  bool completed;
} srtf;

srtf *array;
int current_time = 0, n;

// find shortest job
int high_priority(srtf array[], int current_time){
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

  printf("enter priority : ");
  scanf("%d", &array[indexPosition].priority);

  printf("enter arrival time : ");
  scanf("%d", &array[indexPosition].arrival_time);

  printf("enter burst time : ");
  scanf("%d", &array[indexPosition].burst_time);

  array[indexPosition].remaining_time = array[indexPosition].burst_time;

  printf("----------------------------\n");
}
// calculate data
void calculate(int highPriority, int current_time){

  if(array[highPriority].remaining_time == 0){
    array[highPriority].completion_time = current_time + 1;
    array[highPriority].turnaround_time = array[highPriority].completion_time - array[highPriority].arrival_time;
    array[highPriority].waiting_time = array[highPriority].turnaround_time - array[highPriority].burst_time;
    array[highPriority].completed = true;
  }
}

void show_result(){
  srtf sorted;
  float avgTat = 0, avgWt = 0;
  int i, j;

  for(i = 0; i < n; i++){
    avgTat = avgTat + array[i].turnaround_time;
    avgWt = avgWt + array[i].waiting_time;
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

  printf("\n\nAverage turnaround time : %.2f", avgTat/n);
  printf("\nAverage waiting time : %.2f", avgWt/n);

}

int main(){
  int i;

  printf("Enter the number of array: ");
  scanf("%d", &n);
  printf("\n");

  array = malloc(sizeof(srtf) * n);

  printf("\n[Note : lower value higher priority]\n\n");

  // Input process details
  for (i = 0; i < n; i++){
    enterData(i);
  }

  while (true){
    int priority = high_priority(array, current_time);

    if (priority == -1){
      break;
    }

    array[priority].remaining_time--;
    calculate(priority, current_time);
    current_time++;  
  }

  show_result();

  return 0;
}