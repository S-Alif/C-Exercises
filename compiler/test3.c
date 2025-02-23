#include <stdio.h>

int main (){
    char ch;
    FILE *file1, *file2;
    file1 = fopen("test.txt", "r");
    file2 = fopen("test2.txt", "w");

    while((ch = getc(file1)) != EOF){
        if(ch == ' ' || ch == ',' || ch == ';'){
            putc('\n', file2);
        }
        else{
            putc(ch, file2);
        }
    }

    fclose(file1);
    fclose(file2);

    return 0;
}
