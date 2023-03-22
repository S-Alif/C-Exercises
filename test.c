#include<stdio.h>
#include<stdlib.h>

// structure to store student data
typedef struct student{
    int usn;
    char name[20];
    char branch[10];
    int sem;
    int phone;

    struct student *next;
}student;

// other global variables
int max, top = 0, n;

student *start;

int menu()
{
    int choice;
    printf("\t\t\t\n==========MENU==========");
    printf("\n1. Create list.");
    printf("\n2. Insert data.");
    printf("\n3. Delete data.");
    printf("\n4. Display data.");
    printf("\n5. Stack demonstration.");
    printf("\n6. Queue demonstretion.");
    printf("\n7. Exit.");

    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    return choice;
    printf("\n");
}

//Stack menu
int stack_menu()
{
    int choice;

    printf("\t\t\t\n========Stack Demonstration========");
    printf("\n1. Push data.");
    printf("\n2. Pop data.");
    printf("\n3. Display stack.");
    printf("\n4. Exit from stack");

    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    return choice;
}

//Queue menu
int queue_menu()
{
    int choice;

    printf("\t\t\t\n========Queue Demonstration========");
    printf("\n1. Insert data.");
    printf("\n2. Delete data.");
    printf("\n3. Display queue.");
    printf("\n4. Exit from queue");

    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    return choice;
}

/*enter other data*/
student* enter_data(student *address){
    printf("\nEnter USN : ");
    scanf("%d", &address->usn);
    printf("Enter Name : ");
    scanf("%s", address->name);
    printf("Enter Branch : ");
    scanf("%s", address->branch);
    printf("Enter Semester : ");
    scanf("%d", &address->sem);
    printf("Enter Phone : ");
    scanf("%d", &address->phone);
}

/* create list  */
void create_list(){
    printf("\n\nEnter the size of the list : ");
    scanf("%d", &n);

    printf("\nA list of size - %d has been created\n\n", n);
}

/* insert data */
void insert(){
    student *head, *temp;

    head = malloc(sizeof(student));
    start = head;
    temp = head;

    // enter 1st data
    printf("\nEnter USN : ");
    scanf("%d", &temp->usn);
    printf("Enter Name : ");
    scanf("%s", temp->name);
    printf("Enter Branch : ");
    scanf("%s", temp->branch);
    printf("Enter Semester : ");
    scanf("%d", &temp->sem);
    printf("Enter Phone : ");
    scanf("%d", &temp->phone);


    // entering data for other nodes
    for(int i = 1; i < n; i++){
        head = malloc(sizeof(student));
        temp->next = head;
        enter_data(head);
        temp = temp->next;
    }

    printf("\nData has been entered\n\n");
}

/* display data */
void display_data(){
    student *temp;

    if(start == NULL){
        printf("\nThere is no data in the list\n");
    }else{
        temp = start;
        while(temp != NULL)
        {
        printf("\nUSN : %d", temp->usn);
        printf("\nName: %s", temp->name);
        printf("\nBranch: %s", temp->branch);
        printf("\nSemester: %d", temp->sem);
        printf("\nPhone: %d", temp->phone);
        temp = temp->next;
        }
    }
    printf("\n\n");
}

/* delete data */
void delete_data(){
    student *temp, *position;
    int i, pos;

    if(start == NULL){
        printf("\nThere is no data in the list\n");
    }else{
        printf("\n\nEnter position : ");
        scanf("%d", &pos);

        position = malloc(sizeof(student));
        temp = start;

        if(pos == 1){
            start = start->next;
            temp->next = NULL;
            free(temp);
        }else{
            while(pos != 1){
                position = temp->next;
                temp->next = temp->next->next;
                pos--;
            }
        }    

        position = temp->next;
        free(temp->next);
        temp->next = NULL;

        printf("\nData has been deleted\n\n");
    }
}

/* stack deletion */
void stack_delete(){
    student*head, *temp;

    temp = start;
    head = temp->next;
    start = head;

    free(temp);

    printf("\nData has been deleted\n\n");
}

/* stack insertion */
void stack_insert(){
    student *head, *temp;

    head = malloc(sizeof(student));
    temp = start;
    start = head;

    enter_data(head);
    head->next = temp;

    printf("\nData has been entered\n\n");
}


// stack demonstration
void stack_demo()
{
    int choice;

    do
    {
        choice = stack_menu();

        switch(choice){
            case 1: stack_insert();
                    break;
            case 2: stack_delete();
                    break;
            case 3: display_data();
                    break;
            case 4: choice = 4;
                    break;
            default: printf("INVALID OPTION\n\n");
                    break;
        }
    }while(choice != 4);

    printf("\n\n");      
}


/* queue insert */
void queue_insert(){
    student *rear, *temp;

    rear = malloc(sizeof(student));
    temp = start;
    enter_data(rear);

    while(temp->next != NULL){
        temp = temp->next;
    }

    temp->next= rear;
    printf("\nData has been entered\n\n");
}

/* queue delete */
void queue_delete(){
    student *front, *temp;

    front = start;
    temp = start;

    start = temp->next;

    free(front);
    printf("\nData has been deleted\n\n");
}

/* queue demonstration */
void queue_demo()
{
    int choice;

    do
    {
        choice = queue_menu();

        switch(choice){
            case 1: queue_insert();
                    break;
            case 2: queue_delete();
                    break;
            case 3: display_data();
                    break;
            case 4: choice = 4;
                    break;
            default: printf("INVALID OPTION\n\n");
                     break;
    } 
   } while (choice != 4);
    printf("\n\n");
}

int main(){
    int choice;

    do
    {
        choice = menu();

        switch(choice){
            case 1: create_list();
                    break;
            case 2: insert();
                    break;
            case 3: delete_data();
                    break;
            case 4: display_data();
                    break;
            case 5: stack_demo();
                    break;
            case 6: queue_demo();
                    break;
            case 7: choice = 7;
                    break;
            default: printf("INVALID OPTION\n\n");
                     break;
        }
    } while (choice != 7);

    return 0;
}