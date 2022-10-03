/*mode of an array*/

#include<stdio.h>

int main(){

    int i, n;
    float sum = 0, a, b, median, array[100], avg, mode;

    printf("enter the size of an array = ");
    scanf("%d", &n);

    printf("\nenter array values\n");
    printf("--------------------\n");

    for(i = 0; i < n; i++){
        scanf("%f", &array[i]);
    }

    // find median
    if(n%2 == 0){           /*if array size is even*/
        a = array[(n/2) - 1];
        b = array[n/2];
        median = (a+b) / 2;

        printf("\nmedian = %.2f", median);
    }
    if(n%2 != 0){           /*if array size is odd*/
        median = array[(n-1) / 2];

        printf("\nmedian = %.2f", median);
    }

    // loop for average
    for(i = 0; i < n; i++){
        sum = sum + array[i];
        avg = sum / n;
    }
    printf("\naverage = %.2f", avg);

    // mode
    mode = 3 * (median - 2) * avg;

    printf("\nmode = %.2f", mode);

    
    return 0;
}