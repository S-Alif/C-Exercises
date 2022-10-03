/*This is a program to convert fahrenheit temperature to celsius*/
#include <stdio.h>

int main()
{
    /*int c;*/
    float c, f;

    printf("This is a program to convert fahrenheit temperature to celsius \n");
    printf("\n");
    printf("Enter fahrenheit temperature = ");
    scanf("%f", &f);

    /*fahrenheit to celsius*/
    c = ((f-32)/9)*5;

    printf("celsius temperature = %f\n", c);

    return 0;
}
