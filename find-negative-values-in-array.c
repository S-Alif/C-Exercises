/*show and count negative elements in an array*/

#include<stdio.h>

int main(){

    int i , n, a[100], negative_count = 0;

    printf("enter array size = ");
    scanf("%d", &n);
    

    printf("\nenter array values = ");
    for(i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }

    // finding negative values
    printf("\nnegative values in the array = ");
    for(i = 0; i < n; i++){
        if(a[i] < 0){
            negative_count++;
            printf("%d, ", a[i]);
        }
    }

    printf("\ntotal negative values in the array = %d", negative_count);

    return 0;
}