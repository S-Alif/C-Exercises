// find the median of an array

#include <stdio.h>

int main(){

    int i, n;
    float a, b, median, array[100];

    printf("enter the size of array = ");
    scanf("%d", &n);

    printf("enter array values = \n");

    for (i = 0; i < n; i++){
        scanf("%f", &array[i]);
    }
    
    // if the array size is even
    if (n%2 == 0){
        a = array[(n / 2) - 1];
        b = array[n / 2];
        median = (a+b) / 2;

        printf("\nmedian = %.2f", median);
    }

    // if the array size is not even
    if (n%2 != 0){
        median = array[(n - 1) / 2];

        printf("\nmedian = %.2f", median);
    }

    return 0;
}