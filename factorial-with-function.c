// print the factorial series of a number and it sum using function

#include<stdio.h>

int factorial();
int main(){
    int n;

    printf("enter number for factorial : ");
    scanf("%d", &n);

    printf("\nfactorial series : ");

    factorial(n);

    return 0;
}
// factorial function
int factorial(int x){
    int i, sum = 1;

    for(i = 1; i <= x; i++){
        printf("%d X ", i);
        sum = sum * i;
    }

    printf("\b\b= %d", sum);
}