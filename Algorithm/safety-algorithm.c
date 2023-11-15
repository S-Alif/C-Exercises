// Bankers algorithm - safety algorithm
#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int processes, resources;
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int max_allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];

// Function to check if the system is in a safe state
int isSafe(int safeSeq[]){
  int work[MAX_RESOURCES];
  int finish[MAX_PROCESSES] = {0};

  // Initialize work and available
  for (int i = 0; i < resources; ++i){
    work[i] = available[i];
  }

  int count = 0;
  while (count < processes){
    int found = 0;

    for (int i = 0; i < processes; ++i){
      if (!finish[i]){
        int j;
        for (j = 0; j < resources; ++j){
          if (need[i][j] > work[j]){
            break;
          }
        }

        if (j == resources){
          // Process i can finish
          for (int k = 0; k < resources; ++k){
            work[k] += allocation[i][k];
          }

          finish[i] = 1;
          safeSeq[count++] = i;
          found = 1;
        }
      }
    }

    if (!found){
      // No safe sequence found
      return 0;
    }
  }

  // System is in a safe state
  return 1;
}

// Function to allocate resources to a process
void allocateResources(int process){
  printf("Enter resource allocation for process P%d:\n", process);
  for (int i = 0; i < resources; ++i){
    scanf("%d", &allocation[process][i]);
  }

  printf("Enter maximum resource allocation for process P%d:\n", process);
  for (int i = 0; i < resources; ++i){
    scanf("%d", &max_allocation[process][i]);
    need[process][i] = max_allocation[process][i] - allocation[process][i];
  }
}

// Function to print the safe sequence
void printSafeSequence(int safeSeq[]){
  printf("Safe Sequence: ");
  for (int i = 0; i < processes - 1; ++i){
    printf("P%d -> ", safeSeq[i]);
  }
  printf("P%d\n", safeSeq[processes - 1]);
}

int main(){
  printf("Enter the number of processes: ");
  scanf("%d", &processes);

  printf("Enter the number of resources: ");
  scanf("%d", &resources);

  printf("Enter available resources:\n");
  for (int i = 0; i < resources; ++i){
    scanf("%d", &available[i]);
  }

  for (int i = 0; i < processes; ++i){
    allocateResources(i);
  }

  int safeSeq[MAX_PROCESSES];
  if (isSafe(safeSeq)){
    printf("\nSystem is in a safe state.\n");
    printSafeSequence(safeSeq);
  }
  else{
    printf("System is not in a safe state.\n");
  }

  return 0;
}