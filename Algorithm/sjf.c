/* CPU Scheduling Algorithm */
/* SJF : Shortest Job First */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int n;

// Structure to represent a process
typedef struct process {
    char process[10];
    int arrival_time;
    int burst_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;

    bool completed;
}process;

process *processes;

int calculate(int shortest_job, int current_time){

    processes[shortest_job].completion_time = current_time + processes[shortest_job].burst_time;
    processes[shortest_job].turnaround_time = processes[shortest_job].completion_time - processes[shortest_job].arrival_time;
    processes[shortest_job].waiting_time = processes[shortest_job].turnaround_time - processes[shortest_job].burst_time;

    current_time = processes[shortest_job].completion_time;
    processes[shortest_job].completed = true;

    return current_time;
}

// Function to find the process with the shortest burst time in the ready queue
int shortestJob(process array[], int current_time) {
    int shortest_job = -1;
    int shortest_job_time = -1;

    for (int i = 0; i < n; i++) {
        if (!array[i].completed && array[i].arrival_time <= current_time) {
            if (shortest_job == -1 || array[i].burst_time < shortest_job_time) {
                shortest_job = i;
                shortest_job_time = array[i].burst_time;
            }
        }
    }

    return shortest_job;
}

// enter data
void enterData(int indexPosition){
  printf("enter process name : ");
  scanf("%s", processes[indexPosition].process);

  printf("enter burst time : ");
  scanf("%d", &processes[indexPosition].burst_time);

  printf("enter arrival time : ");
  scanf("%d", &processes[indexPosition].arrival_time);

  printf("\n----------------------------\n\n");
}

int main() {
  process sorted;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    processes = malloc(sizeof(process) * n);

    // Input process details
    for (int i = 0; i < n; i++) {
      enterData(i);
    }
    int current_time = processes[0].arrival_time;

    for (int i = 0; i < n; i++){
      if(processes[i].arrival_time < current_time){
        current_time = processes[i].arrival_time;
      }
    }


    // Execute processes
    while (true) {
        int shortest_job = shortestJob(processes, current_time);
        if (shortest_job == -1){
          break;
        }
        current_time = calculate(shortest_job, current_time);
    }

    for (int i = 0; i < n; i++){
    for(int j = i+1; j < n; j++){
      if(processes[i].completion_time > processes[j].completion_time){
        sorted = processes[i];
        processes[i] = processes[j];
        processes[j] = sorted;
      }
    }
  }

    // Display results
    printf("\nprocess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process, processes[i].arrival_time,
               processes[i].burst_time, processes[i].completion_time,
               processes[i].turnaround_time, processes[i].waiting_time);
    }

    return 0;
}