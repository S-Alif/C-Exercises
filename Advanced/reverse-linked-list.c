// wirte a program to reverse a linked list

#include<stdio.h>
#include<stdlib.h>

typedef struct list{
    int data;
    struct list *next_data;
}list;

list *start;

// middle node of the list
void middle(list *address){
    if(address == NULL){
        printf("Error : Invalid Input !!!!\n");
    }
    
    list *check_one_node, *check_two_nodes;
    check_one_node = check_two_nodes = address;
 
    while(check_two_nodes != NULL && check_two_nodes->next_data != NULL) {
        check_two_nodes = check_two_nodes->next_data->next_data;
        check_one_node = check_one_node->next_data;
    }
     
    printf("\nMiddle Node : %d\n", check_one_node->data);
}

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
    middle(start);
    return 0;
}