// Find minimum or maximum in array

#include <stdio.h>

int main(){
    int i, n, min, max, a[100];

    printf("enter array size = ");
    scanf("%d", &n);
    

    printf("\nenter array values = ");
    for(i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }

    min = a[1];
    max = a[1];

    for(i = 0; i < n; i++){
        if (a[i] > max){
            max = a[i];
        }
        if (a[i] < min){
            min = a[i];
        }        
    }

    printf("\nmax value in array = %d\n", max);
    printf("min value in array = %d", min);

    return 0;
}