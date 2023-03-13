/* Queue - linear data structure implementation */

#include<stdio.h>
#include<stdlib.h>

// declare global variables
int *array, max, front = -1, rear = -1;

// function for the menu
int menu(){
    int choice;

    printf("Perform following action on a queue : \n\n");
    printf("\t1. Create a Queue\n\t2. Insert elements to the queue\n\t3. Delete elements from the queue\n\t4. Display queue\n\t5. Exit\n\n");

    printf("Your choice : ");
    scanf("%d", &choice);

    return choice;
}

// creating a queue of desired size
void create_queue(){
    printf("\n\nEnter the size of the queue : ");
    scanf("%d", &max);

    array = malloc(max * sizeof(int));

    printf("A Queue of size - %d has been created\n\n", max);
}

// insert elements to the queue
void insert_elements(){
    printf("\n\nEnter element to be inserted : ");

    if(rear != max - 1){
        scanf("%d", &array[++rear]);

        if(front == -1){
            front = 0;
        }

        printf("Element has been inserted\n\n\n");
    }else{
        printf("\nQueue Overflown\n\n\n");
    }
}

// delete from the queue
void delete_elements(){
    if(front == -1){
        printf("\n\nQueue Underflown\n\n\n");
    }else{
        if(front == rear){
            front = -1;
            rear = -1;
        }else{
            printf("\n\nDeleted Element : %d\n\n", array[front++]);
        }
    }
}

// display the queue
void display_elements(){
    if(front == -1){
        printf("\nQueue currently has no elements\n\n\n");
    }else{
        printf("\nQueue elements are : \n");
        for(int i = front; i <= rear; i++){
            printf("%d\t", array[i]);
        }
    }
    printf("\n\n\n");
}

// exit the program
int exit_program(){
    printf("\nProgram Ended");
    return 0;
}


int main(){
    int action = 1, option;

    while (action == 1){
        option = menu();

        switch (option){
        case 1:
            create_queue();
            break;
        case 2:
            insert_elements();
            break;
        case 3:
            delete_elements();
            break;
        case 4:
            display_elements();
            break;
        case 5:
            action = exit_program();
            break;
        default:
            printf("\n\nINVALID OPERATION\n\n\n");
            break;
        }
    }

    return 0;
}