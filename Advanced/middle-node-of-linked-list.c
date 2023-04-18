// write a program to find the middle node of a linked list

#include<stdio.h>
#include<stdlib.h>

typedef struct list{
    int data;
    struct list *next_data;
}list;

list *start;

// reverse the list


int main(){
    int n, data;
    list *head, *temp;

    head = malloc(sizeof(list));
    start = head;
    temp = head;

    printf("Enter list size : ");
    scanf("%d", &n);

    printf("Enter data : ");
    scanf("%d", &head->data);
    for (int i = 1; i < n; i++){
        scanf("%d", &data);
        head = malloc(sizeof(list));
        temp->next_data = head;
        head->data = data;
        temp = temp->next_data;
    }

    // call the function
    return 0;
}