// find the average of an array

#include <stdio.h>

int main(){

    int i, n;
    float value[100],avg, sum = 0;

    printf("enter array size = ");
    scanf("%d", &n);

    printf("\nenter array values = \n");

    // storing data in the array
    for (i = 0; i < n; i++)
    {
        scanf("%f", &value[i]);
    }

    // getting the average
    for (i = 0; i < n; i++)
    {
        sum = sum + value[i];
        avg = sum / n;
    }

    printf("\naverage = %.2f", avg);
    
    return 0;
}