#include <stdio.h>
#include <math.h>

int main()
{
    int year;

    printf("A c-program to find out leap years \n");
    printf("\n");

    printf("Enter year= ");
    scanf("%d", &year);
    printf("\n");


    /*formula*/
    if(((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
    {
        printf("%d is a leap year", year);
    }
    else
    {
        printf("%d is not a leap year", year);
    }
    printf("\n");

    return 0;
}
