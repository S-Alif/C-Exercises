#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

#define MAX 4

int stack[MAX],item;
int ch,top = -1,count = 0, status = 0;


void push(int stack[], int item){
    if(top == (MAX - 1))
    printf("Stack is Overflow");
    else{
        stack[++top] = item;
        status++;
    }
}

int pop(int stack[]){
    int ret;
    if(top == -1)
        printf("\n\n Stack is Underflow");
    else{
        ret = stack[top--];
        status--;
        printf("\nPopped element is %d",ret);
        
    }
    return ret;
}

void palindrome(int stack[]){
    int i, temp;
    temp = status;
    for(i=0; i < temp; i++){
        if(stack[i] == pop(stack))            
            count++;
        
                   
    }
    if(temp == count)
        printf("\nStack contents are Palindrome");
    else
        printf("\nStack contents are not Palindrome");
}

void display(int stack[]){
    int i;
    printf("\nThe stack contents are:");
    if(top == -1)
        printf("stack is empty");
    else{
        for(i=top; i>=0;i--)
            printf("\n......\n|%d|", stack[i]);
        printf("\n");
    }
}
    
void main(){
         do{
             printf("\n\n....MAIN MENU....\n");
             printf("\n1. PUSH (insert) in the stack");
             printf("\n2.POP(delete)from the stack");
             printf("\n3.PALINDROME check using stack");
             printf("\n4.Exit(End the execution)");

             printf("\n\nYour choice : ");

             scanf("\%d", &ch);
             
             
             switch(ch){
                 case 1:
                    printf("\nEnter a element to be pushed:");
                    scanf("%d", &item);
                    push(stack, item);
                    display(stack);
                    break;
                 case 2:
                    item = pop(stack);
                    display(stack);
                    break;
                 case 3:
                    palindrome(stack);
                    break;
                 case 4:
                    exit(0);
                    break;
                 default:
                    printf("\END OF EXECUTION");
                 
             }
             
         }while(ch != 4);

         getch();
}