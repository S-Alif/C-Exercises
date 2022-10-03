// reverse an array

#include <stdio.h>

int main(){
    int i, j, k, n, a[100], rev[100];

    printf("enter array size = ");
    scanf("%d", &n);
    

    printf("\nenter array values = ");
    for(i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }

    j = i - 1;

    printf("array values reversed : \n");
    for(k = 0; k < i; k++){
        rev[k] = a[j];
        printf("%d ", rev[k]);
        j--;
    }

    return 0;
}