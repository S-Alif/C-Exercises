/* linear search algorithm */

#include<stdio.h>

// linear_search function
int linear_search(int data[], int n, int item){
    int k = 0, loc = 0;

    while(loc == 0 && k < n){
        if(item == data[k]){
            loc = k;
        }
        k++;
    }

    return loc;
}

// main function
int main(){
    int loc, n, item;

    printf("Enter array size : ");
    scanf("%d", &n);

    int data[n];

    // enter array elements
    printf("\nEnter array elements : \n");
    for(int i = 0; i < n; i++){
        scanf("%d", &data[i]);
    }
    
    // item to be seached
    printf("\nEnter item to be searched : ");
    scanf("%d", &item);

    // call the function
    loc = linear_search(data, n, item);

    // check and print suitable message
    if(loc == 0){
        printf("\n%d is not in the array", item);
    }else{
        printf("\nItem %d is located in position %d", item, loc+1);
    }

    return 0;
}