/*find if the number is prime using function*/

#include<stdio.h>

// declaring the function
int prime(int n);

int main(){
    int n, prime_number = 1;

    printf("enter a number = ");
    scanf("%d", &n);

    prime_number = prime(n); /*calling the function*/

    if(prime_number == 0){
        printf("%d is not a prime number", n);
    }
    else{
        printf("%d is a prime number", n);
    }

    return 0;
}

// the function to check the prime number
int prime(int n){
    int i;

    for(i = 2; i < n; i++){
        if(n%i == 0){
            return 0;
            break;
        }
    }
}