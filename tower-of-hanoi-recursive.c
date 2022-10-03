// tower of hanoi using recursion

#include<stdio.h>

void transfer(int n, char from, char to, char temp){
    if(n > 0){
        transfer(n-1, from, temp, to);

        printf("move disk %d from %c to %c \n", n, from, to);

        transfer(n-1, temp, to, from);
    }
}
int main(){
    int n;

    printf("solving the tower of hanoi \n\n");

    printf("number of disks = ");
    scanf("%d", &n);

    printf("\n");
    transfer(n, 'L', 'R', 'C');

    return 0;
}