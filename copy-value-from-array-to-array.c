/*copy values of an array to another array*/

#include<stdio.h>

int main(){

    int i, n, a[100], b[100];

    printf("enter array size = ");
    scanf("%d", &n);

    printf("\nenter array values = ");
    for(i = 0; i < n; ++i){
        scanf("%d", &a[i]);
    }

    // copying values to other array
    printf("\nenter array values = ");
    for(i = 0; i < n; i++){
        b[i] = a[i];
        printf("%d ", b[i]);
    }

    return 0;
}