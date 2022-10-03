// array size with user input and display

#include <stdio.h>

int main(){

    int values[100], i, n;

    printf("enter the size of the array = ");
    scanf("%d", &n);

    printf("\nenter array values = ");

    for (i = 0; i < n; i++)
    {
        scanf("%d", &values[i]);
    }

    printf("displaying array values = ");

    for (i = 0; i < n; i++)
    {
        printf("%d ", values[i]);
    }
    
    return 0;
}