#include<stdio.h>

// declare everything globally
char STR[50], PTR[20], REP[20], REPLACED[50];
int i = 0, j, k = 0, l, m = 0, flag = 0;

// function to change all occurances in the main string
void replace_string(){

    while (STR[i] != '\0'){
        j=i;
        k = 0;

        while(PTR[k] != '\0'){
            if(PTR[k] == STR[j]){
                k++;
                j++;
                if(PTR[k] == '\0'){
                    for(l = 0; REP[l] != '\0'; l++){
                        REPLACED[m] = REP[l];
                        m++;
                    }
                    flag = 1;
                    i=j;
                }
            }
            else{
                REPLACED[m] = STR[i];
                m++;
                i++;
                k = 0;
                break;
            }
        }
    }
    REPLACED[m] = '\0';
}

int main(){ 

    printf("\n\nEnter the main string : ");
    gets(STR);
    printf("Enter the pattern to find in the main string : ");
    gets(PTR);
    printf("Enter the replace pattern : ");
    gets(REP);

    // call the function
    replace_string();
    
    // verify the result
    if (flag == 0){
        printf("\npattern don't match");
    }else{
        printf("\nReplaced string : %s\n\n", REPLACED);
    }
    
    return 0;
}