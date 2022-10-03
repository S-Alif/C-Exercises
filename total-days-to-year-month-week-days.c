/*enter days and covert it to years,
months, weeks and days*/

#include<stdio.h>
#include<math.h>

int main(){
    int days;

    printf("enter days = ");
    scanf("%d", &days);

    int years = days / 365; //ignore leap year
    int months = (days % 365) / 30;
    int weeks = (days - ((years * 365)+(months * 30))) / 7;
        days = days - ((years * 365) + (months * 30) + (weeks * 7));

    printf("\nYears = %d", years);
    printf("\nMonths = %d", months);
    printf("\nWeeks = %d", weeks);
    printf("\nDays = %d \n", days);

    return 0;
}
