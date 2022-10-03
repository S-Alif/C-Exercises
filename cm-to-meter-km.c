/*enter length in centimeter and convert
to kilometer and meter*/

#include<stdio.h>
#include<math.h>

int main(){
    int cm;

    printf("enter length in centimeter = ");
    scanf("%d", &cm);

    float m = cm / 100;
    float km = m / 1000;

    printf("\nLength in meter = %.2f", m);
    printf("\nLength in kilometer = %.4f \n", km);

    return 0;
}

