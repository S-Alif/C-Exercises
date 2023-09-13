/* CPU Scheduling Algorithm */
/* SJF : Shortest Job First */

#include <stdio.h>
#include <stdbool.h>

// Structure to represent a process
struct Process {
    int arrival_time;
    int burst_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    bool completed;
};

// Function to find the process with the shortest burst time in the ready queue
int findShortestJob(struct Process processes[], int n, int current_time) {
    int shortest_job_index = -1;
    int shortest_job_time = -1;

    for (int i = 0; i < n; i++) {
        if (!processes[i].completed && processes[i].arrival_time <= current_time) {
            if (shortest_job_index == -1 || processes[i].burst_time < shortest_job_time) {
                shortest_job_index = i;
                shortest_job_time = processes[i].burst_time;
            }
        }
    }

    return shortest_job_index;
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].completed = false;
    }

    int current_time = 0;

    // Execute processes
    while (true) {
        int shortest_job_index = findShortestJob(processes, n, current_time);

        if (shortest_job_index == -1)
            break;

        processes[shortest_job_index].completion_time = current_time + processes[shortest_job_index].burst_time;
        processes[shortest_job_index].turnaround_time = processes[shortest_job_index].completion_time - processes[shortest_job_index].arrival_time;
        processes[shortest_job_index].waiting_time = processes[shortest_job_index].turnaround_time - processes[shortest_job_index].burst_time;

        current_time = processes[shortest_job_index].completion_time;
        processes[shortest_job_index].completed = true;
    }

    // Display results
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, processes[i].arrival_time,
               processes[i].burst_time, processes[i].completion_time,
               processes[i].waiting_time, processes[i].turnaround_time);
    }

    return 0;
}