/*add matrixes*/

#include<stdio.h>

int main(){

    int i, j, r, c, elm1[100][100], elm2[100][100], sum[100][100];

    printf("enter matrix row = ");
    scanf("%d", &r);
    printf("enter matrix column = ");
    scanf("%d", &c);

    // storing 1st elements
    printf("\nwrite 1st elements : \n");
    for (i = 0; i < r; i++){
        for (j = 0; j < c; j++)
        {
            printf("position - [%d][%d] = ", i+1, j+1);
            scanf("%d", &elm1[i][j]);
        }
    }
    // storing 2nd elements
    printf("\nwrite 2nd elements : \n");
    for (i = 0; i < r; i++){
        for (j = 0; j < c; j++)
        {
            printf("position - [%d][%d] = ", i+1, j+1);
            scanf("%d", &elm2[i][j]);
        }
    }

    // showing elements
    printf("\n\nthe matrix :");
    for (i = 0; i < r; i++){
        printf("\n");
        for (j = 0; j < c; j++){
            printf("%d   ", elm1[i][j]);
        }            
    }

    printf("\n");

    for (i = 0; i < r; i++){
        printf("\n");
        for (j = 0; j < c; j++){
            printf("%d   ", elm2[i][j]);
        }
    }

    printf("\n\nthe process: \n");
    for (i = 0; i < r; i++){
        for (j = 0; j < c; j++){
            printf("%d + %d", elm1[i][j], elm2[i][j]);
            printf("\n");            
        }
        printf("\n");
    }   

    //sum of the matrix
    for (i = 0; i < r; i++){
        for (j = 0; j < c; j++){
            sum[i][j] = elm1[i][j] + elm2[i][j];
        }
    }

    // showing the sum of the matrix
    printf("\n\nSum of matrixes: \n");
    for (i = 0; i < r; i++){
        for (j = 0; j < c; j++){
            printf("%d   ", sum[i][j]);
        }
        printf("\n");
    }   


    return 0;
}