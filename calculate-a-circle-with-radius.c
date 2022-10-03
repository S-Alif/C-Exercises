/* C program to calculate diameter, circumference and area of circle */

#include <stdio.h>
#include <math.h>

int main()
{
    float r, d, c, a;

    printf("A c-program to calculate everything of a circle from radius \n");
    printf("\n");

    printf("Enter radius of circle(meter): ");
    scanf("%f", &r);
    printf("\n");

    /*formulas*/
    d = 2 * r;
    c = 2 * 3.1416 * r;
    a = 3.1416 * (r * r);

    printf("diameter of circle = %.2f meteres \n", d);
    printf("circumference of circle = %.2f meters \n", c);
    printf("area of circle = %.2f sq. meteres ", a);

    printf("\n");

    return 0;
}
