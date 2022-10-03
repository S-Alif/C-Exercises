// calculating the factorial of an integer using recursive function

#include<stdio.h>

int factorial(int x){
    if(x <= 1){
        return (1);
    }
    else{
        return(x * factorial(x-1));
    }
}
int main(){
    int n;

    printf("n = ");
    scanf("%d", &n);

    printf("n! = %d\n", factorial(n));

    return 0;
}