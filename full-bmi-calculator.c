#include <stdio.h>
#include <math.h>

int main()
{
    float w, h, bmi;

    printf("This is a program to calculate your BMI and and tell you which category you are in.\n");
    printf("\n");

    printf("enter weight(kg) = ");
    scanf("%f", &w);

    printf("enter height(meter) = ");
    scanf("%f", &h);

    bmi = w/(h*h);

    printf("\n");
    printf("Your BMI is = %f \n", bmi);
    printf("\n");

    if(bmi < 15){
        printf("Your BMI category is: starvation\n");
    }
    else if(bmi >= 15.1 && bmi <= 17.5){
        printf("Your BMI category is: anorexic\n");
    }
    else if(bmi >= 17.6 && bmi <= 18.5){
        printf("Your BMI category is: underweight\n");
    }
    else if(bmi >= 18.6 && bmi <= 24.9){
        printf("Your BMI category is: ideal\n");
    }
    else if(bmi >= 25 && bmi <= 25.9){
        printf("Your BMI category is: overweight\n");
    }
    else if(bmi >= 26 && bmi <= 30.9){
        printf("Your BMI category is: obese\n");
    }
    else if(bmi >= 40){
        printf("Your BMI category is: morbidly obese\n");
    }
    else{
        printf("error input data\n");
    }

    return 0;
}
