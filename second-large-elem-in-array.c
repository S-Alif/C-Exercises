// Write a function to find the second largest element in an array

#include<stdio.h>

// function to find the element
int find_elem(int array[], int n){
    int max1 = 0, max2 = 0;


    for(int i = 0; i < n; i++){
        if(array[i] > max1){
            max2 = max1;
            max1 = array[i];
        }
        if(array[i] > max2 && array[i] < max1){
            max2 = array[i];
        }
    }

    printf("\nSecond Largest element : %d", max2);
}

int main(){
    int n;

    printf("Enter array size : ");
    scanf("%d", &n);
    int array[n];

    printf("Enter array values : ");
    for(int i = 0; i < n; i++){
        scanf("%d", &array[i]);
    }

    find_elem(array, n);
}