// product of matrix

#include<stdio.h>

int main(){

    int i, j, r, c, p, elm1[100][100], elm2[100][100], sum[100][100];

    printf("enter matrix row = ");
    scanf("%d", &r);
    printf("enter matrix column = ");
    scanf("%d", &c);

    // storing 1st element
    printf("\nwrite 1st elements : \n");
    for (i = 0; i < r; i++){
        for (j = 0; j < c; j++){
            printf("position - (%d,%d) = ", i+1, j+1);
            scanf("%d", &elm1[i][j]);
        }
    }
    // storing 2nd elements
    printf("\nwrite 2nd elements : \n");
    for (i = 0; i < r; i++){
        for (j = 0; j < c; j++){
            printf("position - (%d,%d) = ", i + 1, j + 1);
            scanf("%d", &elm2[i][j]);
        }
    }
    
    // showing elements
    printf("\n\nthe matrix = \n");
    for (i = 0; i < r; i++){
        for (j = 0; j < c; j++){
            printf("%d  ", elm1[i][j]);
        }
        printf("\n");  
    }

    printf("\n");

    for (i = 0; i < r; i++){
        for (j = 0; j < c; j++){
            printf("%d  ", elm2[i][j]);
        }
        printf("\n");
    }

    // matrix products
    for (i = 0; i < r; i++){
        for (j = 0; j < c; j++){
            sum[i][j] = 0;
            for (p = 0; p < r; p++){
                sum[i][j] += elm1[i][p] * elm2[p][j];
            }            
        }
    }

    // showing the matrix product
    printf("\n\nthe matrix product :");
    for (i = 0; i < r; i++){
        printf("\n");
        for (j = 0; j < c; j++){
            printf("%d  ", sum[i][j]);
        }
    }

    return 0;
}