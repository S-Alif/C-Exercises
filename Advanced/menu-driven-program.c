#include<stdio.h>
#include<stdlib.h>

int n=0;
int *array;

// declaring functions
int menu();
void create_array();
void display_array();
void insert_into_array();
void delete_from_array();
int exit_program();

int main(){
    int action = 1;

    do{
        int option = menu();

        switch (option){
            case 1:
                create_array();
                break;
            case 2:
                display_array();
                break;
            case 3:
                insert_into_array();
                break;
            case 4:
                delete_from_array();
                break;
            case 5:
                action = exit_program();
                break;
            default:
                printf("\nInvalid Option\n");
                break;
        }
    }
    while(action == 1);

    return 0;
}

// menu function
int menu(){
    int choice;
    
    printf("Choose an option to perform the following actions : \n");
    printf("\n\t1. Create an array on N elements");
    printf("\n\t2. Display the array elements");
    printf("\n\t3. Insert an element at a position");
    printf("\n\t4. Delete an element at a position");
    printf("\n\t5. Exit\n");

    printf("\nYour choice : ");
    scanf("%d", &choice);

    return choice;
}

// create array function
void create_array(){
    int i;
    printf("\n\nEnter array size : ");
    scanf("%d", &n);

    array = malloc(sizeof(int) * n);

    printf("\nEnter array values : ");
    for(i = 0; i < n; i++){
        // printf("\nEnter value - %d : ", i+1);
        scanf("%d", &array[i]);
    }

    printf("\nArray values added\n\n");
}

// display array elements
void display_array(){
    if(n == 0){
        printf("\ncreate an array first\n");
    }else{
        printf("\nArray values are : \n");

        for(int i = 0; i < n; i++){
            printf("%d\t", array[i]);
        }
        printf("\n\n");
    }
}

// insert into array
void insert_into_array(){

    if(n == 0){
        printf("\ncreate an array first\n");
    }else{
        n++;
        int pos, elem, i;
        printf("\nEnter the position : ");
        scanf("%d", &pos);

        printf("Enter the value : ");
        scanf("%d", &elem);

        for(i = n-1; i >= pos; i--){
            array[i] = array[i - 1];
        }

        array[pos - 1] = elem;

        printf("\nArray values are : \n");
        for(i = 0; i < n; i++){
            printf("%d\t", array[i]);
        }
        printf("\n\n");
    }
}

// delete from array
void delete_from_array(){
    if(n == 0){
        printf("\ncreate an array first\n");
    }else{
        int pos, i;
        printf("\nEnter the position to delete : ");
        scanf("%d", &pos);

        if(pos > n){
            printf("\nenter a valid position from 1 to %d", n);
        }else{
            for(i = pos-1; i < n-1; i++){
                array[i] = array[i + 1];
            }
            n--;
        }

        printf("\nArray values are : \n");
        for(i = 0; i < n; i++){
            printf("%d\t", array[i]);
        }
        printf("\n\n");
    }
}

// exit the program
int exit_program(){
    printf("\nProgram End\n");
    return 0;
}