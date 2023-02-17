#include<stdio.h>
#include<stdlib.h>

void bubble_sort(int data[], int n){
    int k, ptr, flag = 0; /* ignore the flag variable */

    for(k = 0; k < n-1; k++){
        ptr = 0;

        while (ptr < n-k-1){
            flag = 0;
            printf("loop count - %d --> ", ptr+1);

            if(data[ptr] >= data[ptr + 1]){
                int temp = data[ptr];

                /* ignore this line */
                printf("before sort : %d > %d | ", data[ptr], data[ptr+1]);   

                data[ptr] = data[ptr + 1];
                data[ptr + 1] = temp;

                /* ignore this line and the one after */
                printf("after sort : %d < %d", data[ptr], data[ptr + 1]);
                flag = 1;
            }

            printf("\n"); /*ignore this line*/
            ptr = ptr + 1;
        }

        printf("\n\n-----------------------\nINNER LOOP RUN %d COMPLETE\n-----------------------\n\n\n", k + 1);
        
        /* ignore this */
        // if(flag == 0){
        //     break;
        // }
    }
}

int main(){
    int n;
    printf("Enter array size : ");
    scanf("%d", &n);

    int data[n];

    printf("\nEnter Array values : ");
    for(int i = 0; i < n; i++){
        scanf("%d", &data[i]);
    }
    printf("\n");

    bubble_sort(data, n);

    printf("\nAfter Applying Bubble Sort : \n");
    for(int i = 0; i < n; i++){
        printf("%d\t", data[i]);
    }

    return 0;
}