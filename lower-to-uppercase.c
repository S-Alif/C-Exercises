#include<stdio.h>
#include<ctype.h>

int main()
{
    int j = 0;
    char str[j];
    char ch;

    printf("write something = ");
    scanf("%s", &str);

    for(j = 0; ch = str[j]; j++){
        putchar(toupper(ch));
    }

    /*ch = putchar(toupper(str[j]));
    printf("%s", ch);*/ //only showed 1 character


    /*while (str[j]) {
        ch = str[j];
        putchar(toupper(ch));
        j++;
    }*/

    return 0;
}
