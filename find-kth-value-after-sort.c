// finde k(th) value in an array after sort

#include <stdio.h>

int main(){
    int i, j, n, a[100], sorted, k, ans;

    printf("enter array size = ");
    scanf("%d", &n);
    

    printf("\nenter array values = ");
    for(i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }

    printf("\narray values sorted in ascending order : \n");
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

    printf("\n\nwant to find the k(th) largest value ? \n");
    printf("1. yes\n");
    printf("2. no\n");
    scanf("\n%d", &ans);

    switch (ans){
        case 1:
            printf("\nenter the position = ");
            scanf("%d", &k);

            printf("%d (th) largest value = %d", k, a[k-1]);
            break;
        case 2:
            printf("\nthanks for using the program");
            break;
        default:
            printf("\ndid not choose valid option");
    }
    
    return 0;
}