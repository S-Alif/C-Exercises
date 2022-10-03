// swap values of variables using function

#include<stdio.h>

int swap(int x, int y){
    int z;
    
    z = x;
    x = y;
    y = z;

    printf("after, a | b =  %d | %d\n", x, y);
}

int main(){
    int a, b, c;

    printf("enter numbers= ");
    scanf("%d%d", &a, &b);

    printf("before, a | b =  %d | %d\n", a, b);

    swap(a, b);

    return 0;
}