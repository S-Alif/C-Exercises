/* C program to enter marks of five subjects and show total result */

#include <stdio.h>

int main()
{
    int sub1, sub2, sub3, sub4, sub5, total;
    float percent;

    printf("A c-program to show full results of  subjects \n");
    printf("\n");

    printf("Enter five subjects marks = ");
    scanf("%d%d%d%d%d", &sub1, &sub2, &sub3, &sub4, &sub5);
    printf("\n");


    /*total*/
    total = sub1 + sub2 + sub3 + sub4 + sub5;
    /* Calculate percentage */
    percent = (sub1 + sub2 + sub3 + sub4 + sub5) / 5.0;

    printf("You have got %d out of a total of 500 \n", total);
    printf("Percentage = %.2f\n", percent);


    if(percent >= 90)
    {
        printf("Grade A+ \n");
    }
    else if(percent >= 80)
    {
        printf("Grade A \n");
    }
    else if(percent >= 70)
    {
        printf("Grade B \n");
    }
    else if(percent >= 60)
    {
        printf("Grade C \n");
    }
    else if(percent >= 50)
    {
        printf("Grade D \n");
    }
    else if(percent >= 40)
    {
        printf("Grade E \n");
    }
    else
    {
        printf("Grade F \n");
    }
    printf("\n");

    return 0;
}
