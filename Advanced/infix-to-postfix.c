#include <stdio.h>

#define MAX 20

char stack[20];
int top = -1;

//declaring prototype
int empty();
int full();
char peek();
char pop();
void push(char oper);
int check_operand(char ch);
int precedence(char ch);
int postfix(char *input);


int main(){
    char input[MAX];

    printf("Enter an infix expression : ");
    gets(input);

    postfix(input);
    return 0;
}

int empty(){
    return top == -1;
}
int full(){
    return top == MAX - 1;
}
char peek(){
    return stack[top];
}
char pop(){
    if (empty()){
        return -1;
    }
        
    char ch = stack[top];
    top--;
    return (ch);
}

void push(char oper){
    if (full()){
        printf("Stack Full!!!!");
    }

    else{
        top++;
        stack[top] = oper;
    }
}

int check_operand(char ch){
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int precedence(char ch){
    switch (ch)
    {
    case '+':
    case '-':
        return 1;
        break;
    case '*':
    case '/':
        return 2;
        break;
    case '^':
        return 3;
        break;
    default:
        return -1;
        break;
    }
    
}

int postfix(char *input){
    int i, j;
    for (i = 0, j = -1; input[i]; ++i){
        if (check_operand(input[i])){
            input[++j] = input[i];
        }            
        else if (input[i] == '('){
            push(input[i]);
        }            
        else if (input[i] == ')'){
            while (!empty() && peek() != '('){
                input[++j] = pop();
            }                
            if (!empty() && peek() != '('){
                return -1;
            }else{
                pop();
            }
                
        }else{
            while (!empty() && precedence(input[i]) <= precedence(peek())){
                input[++j] = pop();
            }                
            push(input[i]);
        }
    }
    while (!empty()){
        input[++j] = pop();
    }
    input[++j] = '\0';
    printf("%s", input);
}