#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_PRODUCTIONS 100
#define MAX_SYMBOLS 100

typedef struct {
    char nonTerminal;
    char productions[MAX_PRODUCTIONS][MAX_SYMBOLS];
    int prodCount;
} Rule;

Rule grammar[MAX_PRODUCTIONS];
int ruleCount = 0;

char firstSets[26][MAX_SYMBOLS];
char followSets[26][MAX_SYMBOLS];
bool computedFirst[26] = {false};
bool computedFollow[26] = {false};
char startSymbol;

void addToSet(char set[], char value) {
    if (strchr(set, value) == NULL) {
        int len = strlen(set);
        set[len] = value;
        set[len + 1] = '\0';
    }
}

void computeFirst(char nonTerminal) {
    if (computedFirst[nonTerminal - 'A']) return;
    computedFirst[nonTerminal - 'A'] = true;

    for (int i = 0; i < ruleCount; i++) {
        if (grammar[i].nonTerminal == nonTerminal) {
            for (int j = 0; j < grammar[i].prodCount; j++) {
                char *production = grammar[i].productions[j];
                if (!isupper(production[0]) || production[0] == 'e') {
                    addToSet(firstSets[nonTerminal - 'A'], production[0]);
                } else {
                    int k = 0;
                    while (production[k] != '\0') {
                        if (isupper(production[k])) {
                            computeFirst(production[k]);
                            char *firstOfNext = firstSets[production[k] - 'A'];
                            bool hasEpsilon = false;
                            for (int l = 0; l < strlen(firstOfNext); l++) {
                                if (firstOfNext[l] != 'e') {
                                    addToSet(firstSets[nonTerminal - 'A'], firstOfNext[l]);
                                } else {
                                    hasEpsilon = true;
                                }
                            }
                            if (!hasEpsilon) break;
                        } else {
                            addToSet(firstSets[nonTerminal - 'A'], production[k]);
                            break;
                        }
                        k++;
                    }
                }
            }
        }
    }
}

void computeFollow(char nonTerminal) {
    if (computedFollow[nonTerminal - 'A']) return;
    computedFollow[nonTerminal - 'A'] = true;
    
    if (nonTerminal == startSymbol) {
        addToSet(followSets[nonTerminal - 'A'], '$');
    }
    
    for (int i = 0; i < ruleCount; i++) {
        for (int j = 0; j < grammar[i].prodCount; j++) {
            char *production = grammar[i].productions[j];
            int len = strlen(production);
            for (int k = 0; k < len; k++) {
                if (production[k] == nonTerminal) {
                    int nextIndex = k + 1;
                    while (nextIndex < len) {
                        if (!isupper(production[nextIndex])) {
                            addToSet(followSets[nonTerminal - 'A'], production[nextIndex]);
                            break;
                        }
                        char *firstNext = firstSets[production[nextIndex] - 'A'];
                        bool hasEpsilon = false;
                        for (int l = 0; l < strlen(firstNext); l++) {
                            if (firstNext[l] != 'e') {
                                addToSet(followSets[nonTerminal - 'A'], firstNext[l]);
                            } else {
                                hasEpsilon = true;
                            }
                        }
                        if (!hasEpsilon) break;
                        nextIndex++;
                    }
                    if (nextIndex == len || strchr(firstSets[production[nextIndex - 1] - 'A'], 'e')) {
                        computeFollow(grammar[i].nonTerminal);
                        char *followOfHead = followSets[grammar[i].nonTerminal - 'A'];
                        for (int l = 0; l < strlen(followOfHead); l++) {
                            if (followOfHead[l] != '$') {
                                addToSet(followSets[nonTerminal - 'A'], followOfHead[l]);
                            }
                        }
                    }
                }
            }
        }
    }
}

void readInput() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        printf("Error opening input file!\n");
        exit(1);
    }
    
    char line[MAX_SYMBOLS];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        grammar[ruleCount].nonTerminal = line[0];
        if (ruleCount == 0) startSymbol = line[0];
        
        char *token = strtok(line + 2, "|");
        while (token) {
            strcpy(grammar[ruleCount].productions[grammar[ruleCount].prodCount++], token);
            token = strtok(NULL, "|");
        }
        ruleCount++;
    }
    fclose(file);
}

void writeOutput() {
    FILE *file = fopen("output.txt", "w");
    if (!file) {
        printf("Error opening output file!\n");
        exit(1);
    }
    
    fprintf(file, "FIRST:\n");
	for (int i = 0; i < ruleCount; i++){
		fprintf(file, "%c = { ", grammar[i].nonTerminal);
		for (int j = 0; j < strlen(firstSets[grammar[i].nonTerminal - 'A']); j++){
			fprintf(file, "%c ", firstSets[grammar[i].nonTerminal - 'A'][j]);
		}
		fprintf(file, "}\n");
	}

	fprintf(file, "\nFOLLOW:\n");
    for (int i = 0; i < ruleCount; i++) {
		fprintf(file, "%c = { ", grammar[i].nonTerminal);
        for (int j = 0; j < strlen(followSets[grammar[i].nonTerminal - 'A']); j++){
			fprintf(file, "%c ", followSets[grammar[i].nonTerminal - 'A'][j]);
		}
		fprintf(file, "}\n");
    }
    fclose(file);
}

int main() {
    readInput();
    
    for (int i = 0; i < ruleCount; i++) {
        computeFirst(grammar[i].nonTerminal);
    }
    for (int i = 0; i < ruleCount; i++) {
        computeFollow(grammar[i].nonTerminal);
    }
    
    writeOutput();
    printf("FIRST and FOLLOW sets computed and written to output.txt\n");
    return 0;
}
