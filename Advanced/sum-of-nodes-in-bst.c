// Write a program to calculate the sum of all nodes in a binary node

#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node *left, *right;
}node;

node *root = NULL;

// insert data
node* insert_data(node *address, int data){
    if(address == NULL){
        node *temp;
        temp = (node *)malloc(sizeof(node));
        temp->data = data;
        temp->left = temp->right = NULL;
        return temp;
    }
    if(data < address->data){
        address->left = insert_data(address->left, data);
    }
    if(data >= address->data){
        address->right = insert_data(address->right, data);
    }

    return address;
}

// sum of nodes
int sum_of_nodes(node *address){
    int sum = 0;
    if(address == NULL){
        return 0;
    }
    else{
        sum = address->data + sum_of_nodes(address->left) + sum_of_nodes(address->right);
    }
    return sum;
}


int main(){
    int data, n;

    printf("Enter tree size : ");
    scanf("%d", &n);
    printf("A tree of size - %d has been created\n\n", n);

    printf("Enter data : ");
    for(int i = 0; i < n; i++){
        scanf("%d", &data);
        root = insert_data(root, data);
    }

    // call the function for sum
    printf("\nSum of all nodes : %d", sum_of_nodes(root));

    return 0;
}