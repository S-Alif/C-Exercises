/* NOTE : not fully completed but works for some cases */

#include<stdio.h>

// declare everything globally
char STR[20], PTR[20], REP[20];
int i = 0, flag = 0, j, k = 0;

// function to change all occurances in the main string
void change_string(){

    while (STR[i] != '\0'){
        j = i;
        k = 0;

        while(PTR[k] != '\0'){
            if(PTR[k] == STR[i+k]){
                k++;
                if(PTR[k] == '\0'){
                    for(int l = 0; REP[l] != '\0'; l++){
                        STR[i] = REP[l];
                        i++;
                    }
                    flag = 1;
                    i=j;
                }
            }
            else{
                i = j;
                k = 0;
                break;
            }
        }
        i++;
    }
}

int main(){ 

    printf("Enter the main string : ");
    gets(STR);
    printf("Enter the pattern to find in the main string : ");
    gets(PTR);
    printf("Enter the replace pattern : ");
    gets(REP);

    // call the function
    change_string();
    
    // verify the result
    if (flag == 0){
        printf("\npattern don't match");
    }else{
        printf("\n%s", STR);
    }
   
    return 0;
}