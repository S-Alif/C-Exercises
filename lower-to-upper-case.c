// turn lowercase string to uppercase in c

#include<stdio.h>
#include<string.h>

char uppercase(char b[100]);

int main(){
    char a[100];

    printf("enter a lowercase string : ");
    gets(a);

    uppercase(a);

    return 0;
}

char uppercase(char b[100]){
    int i = 0;
    char c[i];

    printf("\nuppercase string : ");
    for(i = 0; b[i] != '\0'; i++){
        if(b[i] >= 'a' && b[i] <= 'z'){
            c[i] = b[i] - 32;
        }
        printf("%c", c[i]);
    }
}