#include<stdio.h>
#include<stdlib.h>

// structure for binary search tree
typedef struct tree{
    int data;
    struct tree *left_data, *right_data;
}tree;

// other variables
int n;
tree *root = NULL;


/* menu */
int menu(){
    int choice;

    printf("Perform action on a binary search tree : \n");
    printf("\t1. Create tree\n\t2. Search data\n\t3. Delete data from the tree\n\t4. In-order\n\t5. Pre-order\n\t6. Post-order\n\t7. Exit\n\nYour choice : ");
    scanf("%d", &choice);

    return choice;
    printf("\n\n");
}

// insert data
tree* insert_data(tree *address, int data){
    if(address == NULL){
        tree *temp;
        temp = (tree *)malloc(sizeof(tree));
        temp->data = data;
        temp->left_data = temp->right_data = NULL;
        return temp;
    }
    if(data < address->data){
        address->left_data = insert_data(address->left_data, data);
    }
    else if(data > address->data){
        address->right_data = insert_data(address->right_data, data);
    }

    return address;
}

// creating tree
tree* create_tree(){
    int data;

    printf("Enter tree size : ");
    scanf("%d", &n);
    printf("A tree of size - %d has been created\n\n", n);

    printf("Enter data : ");
    for(int i = 0; i < n; i++){
        scanf("%d", &data);
        root = insert_data(root, data);
    }
    printf("\n");
}

// get the smaller data
tree* lower_data(tree *address){
    if(address == NULL){
        return NULL;
    }else if(address->left_data){
        return lower_data(address->left_data);
    }else{
        return address;
    }
}

// searching data
tree* search_data(tree *address, int data){
    if(address == NULL){
        printf("\n%d not found", data);
    }
    else if(data < address->data){
        address->left_data = search_data(address->left_data, data);
    }
    else if(data > address->data){
        address->right_data = search_data(address->right_data, data);
    }
    else{
        printf("\n%d is found", address->data);
    }

    return address;
}

// delete data
tree* delete_data(tree *address, int data){
    tree *temp;

    if(address == NULL){
        printf("\n\nElemenet Not Found\n\n");
    }
    else if(data < address->data){
        address->left_data = delete_data(address->left_data, data);
    }
    else if(data > address->data){
        address->right_data = delete_data(address->right_data, data);
    }
    else{
        if(address->left_data && address->right_data){
            temp = lower_data(address->right_data);
            address->data = temp->data;
            address->right_data = delete_data(address->right_data, temp->data);
        }
        else{
            temp = address;
            if(address->left_data == NULL){
                address = address->right_data;
            }
            if(address->right_data == NULL){
                address = address->left_data;
            }
            free(temp);
        }
    }
    
    return address;
}

// in order
void in_order(tree *address){
    
    if(address != NULL){
        in_order(address->left_data);
        printf("%d\t", address->data);
        in_order(address->right_data);
    }
}

// pre order
void pre_order(tree *address){
    
    if(address != NULL){
        printf("%d\t", address->data);
        pre_order(address->left_data);
        pre_order(address->right_data);
    }
}

// post order
void post_order(tree *address){
    
    if(address != NULL){
        post_order(address->left_data);
        post_order(address->right_data);
        printf("%d\t", address->data);
    }
}

int exit_program(){
    printf("Program Ended");
    return 0;
}


int main(){
    int action = 1, data;

    while(action == 1){

        switch(menu()){
            case 1: create_tree();
                    break;
            case 2:
                printf("Enter element to search : ");
                scanf("%d", &data);
                search_data(root, data);
                printf("\n\n");
                break;
            case 3:
                printf("Enter element to delete : ");
                scanf("%d", &data);
                delete_data(root, data);
                printf("\n\n");
                break;
            case 4:
                printf("Displaying elements in \"IN ORDER\" : \n");
                in_order(root);
                printf("\n\n");
                break;
            case 5:
                printf("Displaying elements in \"PRE ORDER\" : \n");
                pre_order(root);
                printf("\n\n");
                break;
            case 6:
                printf("Displaying elements in \"POST ORDER\" : \n");
                post_order(root);
                printf("\n\n");
                break;
            case 7: action = exit_program();
                    break;
            default: printf("INVALID OPTION\n\n");
                     break;
        }
    }
}