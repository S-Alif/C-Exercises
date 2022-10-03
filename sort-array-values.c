// sort array values in both orders

#include <stdio.h>

int main(){
    int i, j, n, a[100], sorted;

    printf("enter array size = ");
    scanf("%d", &n);
    

    printf("\nenter array values = ");
    for(i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }

    printf("\n\narray values sorted in ascending order : \n");
    for(i = 0; i < n; i++){
        for(j = i+1; j < n; j++){
            if(a[j] < a[i]){
                sorted = a[i];
                a[i] = a[j];
                a[j] = sorted;
            }
        }
        printf("%d ", a[i]);
    }

    printf("\n\narray values sorted in descending order : \n");
    for(i = 0; i < n; i++){
        for(j = i+1; j < n; j++){
            if(a[j] > a[i]){
                sorted = a[i];
                a[i] = a[j];
                a[j] = sorted;
            }
        }
        printf("%d ", a[i]);
    }
    

    return 0;
}