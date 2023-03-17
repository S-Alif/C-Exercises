#include<stdio.h>
#include<stdlib.h>

// structure to store student data
typedef struct student_info{
    int usn;
    char name[20];
    char branch[10];
    int semester;
    int phone;

    struct student_info *next_data;
}student_info;

// other global variables
int n;

student_info *start;

/* menu */
int menu(){
    int choice;

    printf("Choose an option to perform action on list : \n\n");
    printf("1. Create list\n2. Insert data\n3. Delete data\n4. Display data\n5. Stack demonstration\n6. Queue demonstration\n7. Exit the program\n\nYour choice : ");
    scanf("%d", &choice);

    return choice;
    printf("\n\n");
}

/* stack menu */
int stack_menu(){
    int choice;

    printf("Make singly list work as stack : \n\n");
    printf("1. Push data\n2. Pop data\n3. Display data\n4. Exit from stack\n\nYour choice : ");
    scanf("%d", &choice);

    return choice;
}

/* queue menu */
int queue_menu(){
    int choice;

    printf("Make singly list work as queue : \n\n");
    printf("1. Insert data\n2. Delete data\n3. Display data\n4. Exit from queue\n\n");

    printf("Your choice : ");
    scanf("%d", &choice);

    return choice;
}

/*exit the program*/
int exit_program(){
    printf("program ended");
    return 0;
}

/*enter other data*/
student_info* enter_data(student_info *address){
    printf("\nEnter USN : ");
    scanf("%d", &address->usn);
    printf("Enter Name : ");
    scanf("%s", address->name);
    printf("Enter Branch : ");
    scanf("%s", address->branch);
    printf("Enter Semester : ");
    scanf("%d", &address->semester);
    printf("Enter Phone : ");
    scanf("%d", &address->phone);
    printf("\n-----------------------\n");
}

/* create list  */
void create_list(){
    printf("\nEnter the size of the list : ");
    scanf("%d", &n);

    printf("\nA list of size - %d has been created\n\n", n);
}

/* insert data */
void insert_data(){
    student_info *head, *temp;

    head = malloc(sizeof(student_info));
    start = head;
    temp = head;

    printf("\nEnter data of %d students\n", n);
    printf("------------------------------\n");

    // enter 1st data
    enter_data(head);

    // entering data for other nodes
    for(int i = 1; i < n; i++){
        head = malloc(sizeof(student_info));
        temp->next_data = head;
        enter_data(head);
        temp = temp->next_data;
    }

    printf("\nData has been entered\n\n");
}

/* display data */
void display_data(){
    student_info *temp;

    if(start == NULL){
        printf("\nThere is no data in the list\n");
    }else{
        temp = start;

        printf("\nUSN\t\tName\t\tBranch\t\tSemester\tPhone");
        printf("\n-------------------------------------------------------------------------------\n");
        while(temp != NULL){
            printf("\n%d\t\t%s\t\t%s\t\t%d\t\t%d\n",temp->usn, temp->name, temp->branch, temp->semester, temp->phone);
            temp = temp->next_data;
        }
    }
    printf("\n\n");
}

/* delete data */
void delete_data(){
    student_info *temp, *position;
    int i, pos;

    if(start == NULL){
        printf("\nThere is no data in the list\n");
    }else{
        printf("\n\nEnter position : ");
        scanf("%d", &pos);

        position = malloc(sizeof(student_info));
        temp = start;

        if(pos == 1){
            start = start->next_data;
            temp->next_data = NULL;
            free(temp);
        }else{
            while(pos != 1){
                position = temp->next_data;
                temp->next_data = temp->next_data->next_data;
                pos--;
            }
        }    

        position = temp->next_data;
        free(temp->next_data);
        temp->next_data = NULL;

        printf("\nData has been deleted\n\n");
    }
}

/* stack deletion */
void stack_delete(){
    student_info *head, *temp;

    temp = start;
    head = temp->next_data;
    start = head;

    free(temp);

    printf("\nData has been deleted\n\n");
}

/* stack insertion */
void stack_insert(){
    student_info *head, *temp;

    head = malloc(sizeof(student_info));
    temp = start;
    start = head;

    enter_data(head);
    head->next_data = temp;

    printf("\nData has been entered\n\n");
}


/* stack demonstration */
void stack_demo(){
    int action = 1, option;

    while(action == 1){

        option = stack_menu();

        switch(option){
            case 1: stack_insert();
                    break;
            case 2: stack_delete();
                    break;
            case 3: display_data();
                    break;
            case 4: action = exit_program();
                    break;
            default: printf("INVALID OPTION\n\n");
                     break;
        }
    }
}


/* queue insert */
void queue_insert(){
    student_info *rear, *temp;

    rear = malloc(sizeof(student_info));
    temp = start;
    enter_data(rear);

    while(temp->next_data != NULL){
        temp = temp->next_data;
    }

    temp->next_data = rear;
    printf("\nData has been entered\n\n");
}

/* queue delete */
void queue_delete(){
    student_info *front, *temp;

    front = start;
    temp = start;

    start = temp->next_data;

    free(front);
    printf("\nData has been deleted\n\n");
}

/* queue demonstration */
void queue_demo(){
    int action = 1, option;

    while(action == 1){

        option = queue_menu();

        switch(option){
            case 1: queue_insert();
                    break;
            case 2: stack_delete();
                    break;
            case 3: display_data();
                    break;
            case 4: action = exit_program();
                    break;
            default: printf("INVALID OPTION\n\n");
                     break;
        }
    }
}

int main(){
    int action = 1, option;

    while(action == 1){

        option = menu();

        switch(option){
            case 1: create_list();
                    break;
            case 2: insert_data();
                    break;
            case 3: delete_data();
                    break;
            case 4: display_data();
                    break;
            case 5: stack_demo();
                    break;
            case 6: queue_demo();
                    break;
            case 7: action = exit_program();
                    break;
            default: printf("INVALID OPTION\n\n");
                     break;
        }
    }

    return 0;
}