/* shortest remaining time first */

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

  bool completed;
} srtf;

srtf *array;
int current_time = 0, n;

// find shortest job
int findShortestJob(srtf array[], int current_time){
  int shortest_job_index = -1;
  int shortest_job_time = -1;

  for (int i = 0; i < n; i++){
    if (!array[i].completed && array[i].arrival_time <= current_time){
      if (shortest_job_index == -1 || array[i].remaining_time < shortest_job_time){
        shortest_job_index = i;
        shortest_job_time = array[i].remaining_time;
      }
    }
  }

  return shortest_job_index;
}

// enter data
void enterData(int indexPosition){
  printf("enter process name : ");
  scanf("%s", array[indexPosition].process);

  printf("enter arrival time : ");
  scanf("%d", &array[indexPosition].arrival_time);

  printf("enter burst time : ");
  scanf("%d", &array[indexPosition].burst_time);

  array[indexPosition].remaining_time = array[indexPosition].burst_time;

  printf("----------------------------\n");
}
// calculate data
void calculate(int shortest_job, int current_time){

  if(array[shortest_job].remaining_time == 0){
    array[shortest_job].completion_time = current_time + 1;

    array[shortest_job].turnaround_time = array[shortest_job].completion_time - array[shortest_job].arrival_time;

    array[shortest_job].waiting_time = array[shortest_job].turnaround_time - array[shortest_job].burst_time;

    array[shortest_job].completed = true;
  }
}

void show_result(){
  srtf sorted;
  float avgTat = 0, avgWt = 0;
  int i, j;

  for (i = 0; i < n; i++){
    for (j = i + 1; j < n; j++){
      if(array[i].completion_time > array[j].completion_time){
        sorted = array[i];
        array[i] = array[j];
        array[j] = sorted;
      }
    }
  }

  printf("\nprocess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
  for (int i = 0; i < n; i++){
    printf("%s\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", array[i].process, array[i].arrival_time,
           array[i].burst_time, array[i].completion_time,
           array[i].turnaround_time, array[i].waiting_time);
  }

  for(i = 0; i < n; i++){
    avgTat = avgTat + array[i].turnaround_time;
    avgWt = avgWt + array[i].waiting_time;
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

  // Input process details
  for (i = 0; i < n; i++) {
    enterData(i);
  }

  while (true){
    int shortest_job_index = findShortestJob(array, current_time);

    if (shortest_job_index == -1){
      break;
    }

    array[shortest_job_index].remaining_time--;
    calculate(shortest_job_index, current_time);
    current_time++;  
  }

  show_result();

  return 0;
}