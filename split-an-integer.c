/*take an integer as input and split it into digits*/

#include<stdio.h>
void split_digit(int n);

int main(){
    int n;

    printf("Input : ");
    scanf("%d", &n);

    // passing value to function
    split_digit(n);

    return 0;
}

// highest_number function
// also rearrange in descending order
void split_digit(int n){
    int i, j, k, a = 0, sorted;
    int digits[100];

    while (n > 0){
        i = n % 10;
        n = n / 10;
        
        digits[a] = i;
        a++;
    }

    printf("split numbers : ");
    // printing the split numbers
    k = a - 1;
    for(j = 0; j < a; j++){
        printf("%d\t", digits[k]);
        k--;
    }
}