// find the kth smallest element in an array

#include<stdio.h>
#include<stdlib.h>

// small element finder
void small_elem(int array[], int n, int k){
    int sorted;

    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if(array[j] < array[i]){
                sorted = array[i];
                array[i] = array[j];
                array[j] = sorted;
            }
        }
    }

    printf("%dth smallest element is : %d", k, array[k-1]);
}

int main(){
    int n, k;

    printf("Enter array size : ");
    scanf("%d", &n);
    int array[n];

    printf("Enter array values : ");
    for(int i = 0; i < n; i++){
        scanf("%d", &array[i]);
    }

    printf("Smallest element to find : ");
    scanf("%d", &k);

    small_elem(array, n, k);

    return 0;
}