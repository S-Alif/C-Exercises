// #include <stdio.h>
// #include <string.h>
// #include <ctype.h>


// #define MAX_WORD_LENGTH 30

// int checkKeyword(char word[]) {
//     char keywords[][20] = {"if", "while", "for", "int", "char", "float", "double", "include"};

//     int i;
//     // Invalid identifier check
//     if (!isalpha(word[0])) {
//         return 11;
//     }

//     for (i = 0; i < 32; i++) {
//         if (strcmp(keywords[i], word) == 0) {
//             return 1;
//         }
//     }
//     return 0;
// }

// int main() {
//     FILE *file;
//     char fileContent, words[MAX_WORD_LENGTH], ops[] = "*-/+%=";
//     int i = 0, j = 0;

//     file = fopen("test.c", "r");

//     if (file == NULL) {
//         printf("Error: Could not open test.c\n");
//         return 1;
//     }

//     while ((fileContent = getc(file)) != EOF) {
//         printf("%c", fileContent);

//         if (isalnum(fileContent)) {
//             if (j < MAX_WORD_LENGTH - 1) {
//                 words[j++] = fileContent;
//             }
//         } else {
//             if ((fileContent == ' ' || fileContent == '\n' || fileContent == ';' ||
//                  fileContent == '(' || fileContent == ')' || fileContent == '{' ||
//                  fileContent == '}' || fileContent == ',') && j != 0) {
//                 words[j] = '\0';
//                 j = 0;

//                 int check = checkKeyword(words);

//                 if (check == 1) {
//                     printf("%s is a Keyword\n", words);
//                 } else if (check == 11) {
//                     printf("%s is an invalid identifier\n", words);
//                 } else {
//                     printf("%s is an identifier\n", words);
//                 }
//             }

//             // Checking for operators
//             for (i = 0; i < strlen(ops); i++) {
//                 if (fileContent == ops[i]) {
//                     printf("%c is an operator\n", fileContent);
//                     break;
//                 }
//             }
//         }
//     }

//     fclose(file);
//     return 0;
// }


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 100
#define MAX_STRING_LENGTH 200


bool isKeyword(const char *word) {
    const char *keywords[] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};
    const int numKeywords = sizeof(keywords) / sizeof(keywords[0]);

    int i;

    for (i = 0; i < numKeywords; i++) {
        if (strcmp(keywords[i], word) == 0) {
            return true;
        }
    }
    return false;
}


/*----------------------------------------------------------------
cannot detect muti-character operators
------------------------------------------------------------------*/

int main() {
    FILE *file;
    char fileContent, word[MAX_WORD_LENGTH], stringLiteral[MAX_STRING_LENGTH];
    int stringIndex = 0, wordIndex = 0, i;
    bool inString = false;
    char ops[] = "+-*%=<>!&|/";


    file = fopen("test.c", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    while ((fileContent = getc(file)) != EOF) {

        // finding string literals
        if (fileContent == '"') {
            if (inString) {
                stringLiteral[stringIndex] = '\0';
                stringIndex = 0;
                inString = false;
                printf("\"%s\" \t-\t is a string literal\n", stringLiteral);
            }
            else {
                inString = true;
            }
        }

        else if (inString) {
            if (stringIndex < MAX_STRING_LENGTH - 1) {
                stringLiteral[stringIndex++] = fileContent;
            }
            else {
                fprintf(stderr, "literals too long!\n");
            }
        }

        else if (isalnum(fileContent) || fileContent == '_') {
            if (wordIndex < MAX_WORD_LENGTH - 1) {
                word[wordIndex++] = fileContent;
            } else {
                fprintf(stderr, "Word too long!\n");
            }
        }

        // Check for punctuation
        else if (ispunct(fileContent)) {
            if (wordIndex > 0) {
                word[wordIndex] = '\0';
                wordIndex = 0;

                if (isKeyword(word)) {
                    printf("%s \t-\t is a keyword\n", word);
                }
                else if (isalpha(word[0]) || word[0] == '_') {
                    printf("%s \t-\t is an identifier\n", word);
                }
                else if (isdigit(word[0])) {
                    printf("%s \t-\t is number\n", word);
                }
                else {
                    printf("%s \t-\t is an invalid identifier\n", word);
                }
            }

            //Check for operators
            for (i = 0; i < strlen(ops); i++) {
                if (fileContent == ops[i]) {
                    printf("%c \t-\t is an operator\n", fileContent);
                    break;
                }
            }

            if(fileContent == '(' || fileContent == ')' || fileContent == '{' || fileContent == '}' || fileContent == ',' || fileContent == ';'){
                printf("%c \t-\t is a punctuation\n", fileContent);
            }
        }

        // Check for whitespace
        else if (isspace(fileContent)) {
            if (wordIndex > 0) {
                word[wordIndex] = '\0';
                wordIndex = 0;

                if (isKeyword(word)) {
                    printf("%s \t-\t is a keyword\n", word);
                }
                else if (isalpha(word[0]) || word[0] == '_') {
                    printf("%s \t-\t is an identifier\n", word);
                }
                else if (isdigit(word[0])) {
                    printf("%s \t-\t is number\n", word);
                }
                else {
                    printf("%s \t-\t is an invalid identifier\n", word);
                }
            }
        }
    }

    fclose(file);
    return 0;
}

/* ----------------------------------------------------------------
cannot properly identify string literals
----------------------------------------------------------------*/
/*
int main() {
    FILE *file;
    char fileContent;
    char word[MAX_WORD_LENGTH];
    int wordIndex = 0;
    char ops[] = "+-*%=<>!&|/"; // Include more operators
    int i;

    file = fopen("test.c", "r");
    if (file == NULL) {
        perror("Error opening file"); // Use perror for errors
        return 1;
    }

    while ((fileContent = getc(file)) != EOF) {
        printf("%c", fileContent); // Print file content

        if (isalnum(fileContent) || fileContent == '_') { // Allow underscores in identifiers
            if (wordIndex < MAX_WORD_LENGTH - 1) {
                word[wordIndex++] = fileContent;
            }
            else {
                fprintf(stderr, "Word too long!\n"); // Handle overflow
            }
        }

        else if (isspace(fileContent) || ispunct(fileContent)) { // Check for delimiters
            if (wordIndex > 0) {
                word[wordIndex] = '\0'; // Null-terminate the word
                wordIndex = 0;

                if (isKeyword(word)) {
                    printf(" -- is a keyword\n", word);
                }
                else if (isalpha(word[0]) || word[0] == '_') { // Check for valid identifier start
                    printf(" -- %s is an identifier\n", word);
                }
                else {
                    printf(" -- %s is an invalid identifier\n", word);
                }
            }

            // Check for operators (outside word building)
            for (i = 0; i < strlen(ops); i++) {
                if (fileContent == ops[i]) {
                    printf(" -- %c is an operator\n", fileContent);
                    break; // Important: Stop searching once operator is found
                }
            }
        }
    }

    fclose(file);
    return 0;
}
*/