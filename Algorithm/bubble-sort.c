/* Bubble sort algorithm */

#include<stdio.h>

// bubble sort function 
void bubble_sort(int data[], int n){
    int k, ptr;

    for(k = 0; k < n-1; k++){
        ptr = 0;

        while (ptr < n-k-1){
            if(data[ptr] >= data[ptr + 1]){
                int temp = data[ptr];
                data[ptr] = data[ptr + 1];
                data[ptr + 1] = temp;
            }
            ptr = ptr + 1;
        }
    }
}

// main function
int main(){
    int n;
    printf("Enter array size : ");
    scanf("%d", &n);

    int data[n];

    printf("Enter Array values : ");
    for(int i = 0; i < n; i++){
        scanf("%d", &data[i]);
    }

    // call the bubble_sort function
    bubble_sort(data, n);

    // display the sorted array
    printf("After Sort : ");
    for(int i = 0; i < n; i++){
        printf("%d\t", data[i]);
    }

    return 0;
}