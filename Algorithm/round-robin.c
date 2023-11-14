#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct process {
    char process[10];
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    bool completed;
} process;

process *array;
int current_time = 0, n, time_quantum;

void enterData(int indexPosition) {
    printf("Enter process name: ");
    scanf("%s", array[indexPosition].process);

    printf("Enter arrival time: ");
    scanf("%d", &array[indexPosition].arrival_time);

    printf("Enter burst time: ");
    scanf("%d", &array[indexPosition].burst_time);

    array[indexPosition].remaining_time = array[indexPosition].burst_time;
    printf("----------------------------\n");
}

void calculate(int index) {
    array[index].completion_time = current_time;
    array[index].turnaround_time = array[index].completion_time - array[index].arrival_time;
    array[index].waiting_time = array[index].turnaround_time - array[index].burst_time;
    array[index].completed = true;
}

void algorithm() {
    int remaining = n, i, j;

    while (remaining > 0) {
        for (i = 0; i < n; i++) {
            if (array[i].arrival_time <= current_time && array[i].remaining_time > 0) {
                int execution_time = (array[i].remaining_time < time_quantum) ? array[i].remaining_time : time_quantum;
                array[i].remaining_time = array[i].remaining_time - execution_time;
                current_time = current_time + execution_time;

                if (!array[i].completed && array[i].remaining_time == 0) {
                    remaining--;
                    calculate(i);
                }
            }
            else{
                current_time++;
            }
        }
    }

    for(i = 0; i < n; i++){
        for(j=i+1; j < n; j++){
            if(array[i].completion_time > array[j].completion_time){
                process sorted = array[i];
                array[i] = array[j];
                array[j] = sorted;
            }
        }
    }

    // Display results
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", array[i].process, array[i].arrival_time,
               array[i].burst_time, array[i].completion_time,
               array[i].turnaround_time, array[i].waiting_time);
    }
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);
    printf("\n");

    array = malloc(sizeof(process) * n);

    // Input process details
    for (int i = 0; i < n; i++) {
        enterData(i);
    }

    algorithm();

    return 0;
}
