/* FCFS : First Come First Serve */

#include <stdio.h>
#include <stdlib.h>

int n, *duplicateArray;

// function prototypes
void showData(int i);
void calculate();
void enterData(int indexPosition);

// declare a structure for fsfs
typedef struct fcfs{
  char processName[10];
  int burstTime;
  int arrivalTime;
  int completionTime;
  int turnAroundTime;
  int waitingTime;
}fcfs;

// declare array of type fcfs
fcfs *array;

int main(){
  fcfs sorted;

  /* the number of processes will be the array size */
  printf("Enter the amount of processes : ");
  scanf("%d", &n);

  // creating array of n size
  array = malloc(sizeof(fcfs) * n);
  duplicateArray = malloc(sizeof(fcfs) * n);

  /* call 'enter data' function to take data input */
  printf("\nenter all the required data: \n\n");
  for (int i = 0; i < n; i++){
    enterData(i);
  }

  for (int i = 0; i < n; i++){
    for(int j = i+1; j < n; j++){
      if(array[i].arrivalTime > array[j].arrivalTime){
        sorted = array[i];
        array[i] = array[j];
        array[j] = sorted;
      }
    }
  }
  
  calculate();

  /* data table */
  printf("\nprocess name \t\tburst time \t\tarrival time \t\tCT \t\tTAT \t\tWT\n");
  for (int i = 0; i < n; i++){
    showData(i);
  }

}

// enter data
void enterData(int indexPosition){
  printf("enter process name : ");
  scanf("%s", &array[indexPosition].processName);

  printf("enter burst time : ");
  scanf("%d", &array[indexPosition].burstTime);

  printf("enter arrival time : ");
  scanf("%d", &array[indexPosition].arrivalTime);

  printf("\n----------------------------\n\n");
}

// show data
void showData(int i){
  printf("%s \t\t%10d \t\t%10d \t\t%10d \t\t%5d \t\t%5d\n", array[i].processName, array[i].burstTime, array[i].arrivalTime, array[i].completionTime, array[i].turnAroundTime, array[i].waitingTime);
}

// calculate data
void calculate(){
  for (int i = 0; i < n; i++){
    if(i == 0){
      array[i].completionTime = array[i].burstTime;

      // calculate turn around time
      array[i].turnAroundTime = array[i].completionTime - array[i].arrivalTime;

      // calculate burst time
      array[i].waitingTime = array[i].turnAroundTime - array[i].burstTime;
    }
    else{
      // calculate completion time
      array[i].completionTime = array[i].burstTime + array[i-1].completionTime;

      // calculate turn around time
      array[i].turnAroundTime = array[i].completionTime - array[i].arrivalTime;

      // calculate burst time
      array[i].waitingTime = array[i].turnAroundTime - array[i].burstTime;
    }
  }
}