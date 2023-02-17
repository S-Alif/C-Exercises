#include <stdio.h>

#define MAX 5

int top = -1, pushed = 1, popped = 1;
int stack[MAX];


// declaring prototype
int menu();
void push_element();
void pop_element();
void check_palindrome();
void display_stack();
void status();
int exit_program();

int main(){

    int action = 1;

    do{
        int option = menu();

        switch(option){
            case 1:
                push_element();
                break;
            case 2:
                pop_element();
                break;
            case 3:
                check_palindrome();
                break;
            case 4:
                status();
                break;
            case 5:
                action = exit_program();
                break;
            default:
                printf("INVALID OPTION\n");
                break;
        }
    }while(action == 1);

    return 0;
}

/* menu */
int menu(){
    int choice;

    printf("Choose an option to perform action on stack : \n\n");
    printf("1. Push an element\n2. Pop an element\n3. Check for palindrome\n4. Check status\n5. Exit the program\n\nYour choice : ");
    scanf("%d", &choice);

    return choice;
}

/* push elements */
void push_element(){
    if(top != MAX - 1){
        top++;
        printf("\nElement to push : ");
        scanf("%d", &stack[top]);

        pushed = 1;
        popped = 1;
    }else{
        printf("\nStack is overflowed\n");
        pushed = 0;
    }

    if(pushed == 1){
        display_stack();
    }
    printf("\n");
}

/* pop elements */
void pop_element(){
    if(top != -1){
        printf("\nPopped element = %d\n\n", stack[top]);
        top--;
        popped = 1;
        pushed = 1;
    }else{
        printf("\nStack is underflowed\n");
        popped = 0;
    }

    if(popped == 1){
        display_stack();
    }
    printf("\n");
}

/* check for palindrome */
void check_palindrome(){
    int rev[MAX], flag = 0;

    for(int i = 0; i <= top; i++){
        rev[i] = stack[i];
    }

    int j = top;

    for(int i = 0; i <= top; i++){
        if(rev[i] != stack[j]){
            flag = 1;
            break;
        }
        j--;
    }
    
    if(flag != 0){
        printf("\n\nStack is not a palindrome\n");
        display_stack();
    }else{
        printf("\n\nStack is a palindrome\n");
        display_stack();
    }
}

/* display stack elements */
void display_stack(){
    int i = top;
    printf("\nStack elements are : \n");
    while(i != -1){
        printf("| %d |\n", stack[i--]);
    }
    printf("\n");
}

/* status */
void status(){
    if(top != MAX - 1 && top != -1){
        printf("Stack size = %d\n", MAX);
        printf("Current amount of data in stack = %d\n", top + 1);
        printf("Amount of data can be entered = %d\n", (MAX - (top + 1)));
    }
    if(top == MAX - 1){
        printf("Stack size = %d\n", MAX);
        printf("Current amount of data in stack = %d\n\n", top + 1);
        printf("Trying to enter more data will cause an OVERFLOW situation\n\n");
    }
    if(top == -1){
        printf("Stack size = %d\n", MAX);
        printf("Current amount of data in stack = %d\n\n", top + 1);
        printf("Trying to pop more data will cause an UNDERFLOW situation\n\n");
    }

}

/* exit the program */
int exit_program(){
    printf("\nProgram End\n");
    return 0;
}