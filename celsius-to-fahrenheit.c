/*This is a program a program that converts Centigrade to Fahrenheit*/
#include <stdio.h>

int main()
{
    /*int c;*/
    float c, f;

    printf("This is a program to convert celsius temperature to fahrenheit \n");
    printf("\n");
    printf("Enter celsius temperature = ");
    scanf("%f", &c);

    /*celsius to fahrenheit*/
    f = ((c*9)/5)+32;

    printf("fahrenheit temperature = %.2f\n", f);

    return 0;
}
