// Write a function to reverse a string using stack

#include<stdio.h>
#include<string.h>

#define max 20

int top = -1;
char stack[max];

// function to reverse string
void rev_string(char string[]){
    for(int i = 0; i < strlen(string); i++){
        if(top != max-1){
            top++;
            stack[top] = string[i];
        }
    }

    printf("Reversed String : \b");
    while (top != -1){
        printf("%c", stack[top]);
        top--;
    }
}

int main(){
    char string[20];
    printf("Enter a string : ");
    fgets(string, 20, stdin);

    rev_string(string);
    return 0;
}