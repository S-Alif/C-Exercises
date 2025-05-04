#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TERMINALS 100
#define MAX_NON_TERMINALS 100

typedef struct {
    char terminal;
    char nonTerminal;
    char *production;
} TableEntry;

typedef struct {
    TableEntry entries[MAX_NON_TERMINALS][MAX_TERMINALS];
    char terminals[MAX_TERMINALS];
    char nonTerminals[MAX_NON_TERMINALS];
    int terminalCount;
    int nonTerminalCount;
} ParsingTable;

ParsingTable table;
void generateParsingTable();
void collectTerminalsAndNonTerminals();

// functions
void parsingProductionRules(char *line);
void computeFirst(char symbol);
void addToFirst(char nonTerm, char term);
void computeFollow();
void addToFollow(char nonTerm, char term);

// check for terminal
int isTerminal(char ch){
    return !(ch >= 'A' && ch <= 'Z');
}

// production rules
typedef struct{
    char lhs;
    char rhs [20][20];
    int altCount;

} productionRule;

// first sets
typedef struct{
    char nonTerm;
    char set[20];
    int count;
} firstsAndFollows;


// number of productions
int count = 0;
// global production rule array
productionRule productions[100];

// for FIRSTS
firstsAndFollows firstSet[100];
int firstCount = 0;

// for FOLLOWS
firstsAndFollows followSet[100];
int followCount = 0;

int getFollowIndex(char nonTerm) {
    for(int i = 0; i < followCount; i++) {
        if(followSet[i].nonTerm == nonTerm) return i;
    }
    return -1;
}

int getNonTerminalIndex(char nonTerm) {
    for (int i = 0; i < table.nonTerminalCount; i++) {
        if (table.nonTerminals[i] == nonTerm) return i;
    }
    return -1;
}

int getTerminalIndex(char term) {
    for (int i = 0; i < table.terminalCount; i++) {
        if (table.terminals[i] == term) return i;
    }
    return -1;
}

int getFirstIndex(char nonTerm) {
    for (int i = 0; i < firstCount; i++) {
        if (firstSet[i].nonTerm == nonTerm) return i;
    }
    return -1;
}



// main function
int main () {
    FILE *input, *output;
    char line[100];

    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    while(fgets(line, sizeof(line), input)){
        if(line[0] == '\n') {
            count = count + 1;
            continue;
        }
        parsingProductionRules(line);
    }

    for (int i = 0; i < count; i++) {
        computeFirst(productions[i].lhs);
    }

    fprintf(output, "FIRST sets:\n");
    for(int i = 0; i < firstCount; i++){
        fprintf(output, "FIRST(%c) = { ", firstSet[i].nonTerm);
        for(int j = 0; j < firstSet[i].count; j++){
            fprintf(output, "%c", firstSet[i].set[j]);
            if(j != firstSet[i].count - 1) fprintf(output, ", ");
        }
        fprintf(output, " }\n");
    }


    for (int i = 0; i < count; i++) {
        int exists = 0;
        for (int j = 0; j < followCount; j++) {
            if (followSet[j].nonTerm == productions[i].lhs) {
                exists = 1;
                break;
            }
        }
        if (!exists) {
            followSet[followCount].nonTerm = productions[i].lhs;
            followSet[followCount].count = 0;
            followCount++;
        }
    }

    computeFollow();

    fprintf(output, "\nFOLLOW sets:\n");
    for(int i = 0; i < followCount; i++){
        fprintf(output, "FOLLOW(%c) = { ", followSet[i].nonTerm);
        for(int j = 0; j < followSet[i].count; j++){
            fprintf(output, "%c", followSet[i].set[j]);
            if(j != followSet[i].count - 1) fprintf(output, ", ");
        }
        fprintf(output, " }\n");
    }

    collectTerminalsAndNonTerminals();
    generateParsingTable();
    
    // Print LL(1) Parsing Table to output file
    fprintf(output, "\nLL(1) Parsing Table:\n");
    fprintf(output, "%-10s", "");
    for(int i = 0; i < table.terminalCount; i++) {
        if(table.terminals[i] != 'e') {
            fprintf(output, "%-10c", table.terminals[i]);
        }
    }
    fprintf(output, "\n");
    fprintf(output, "%-10s", "----------");
    for(int i = 0; i < table.terminalCount; i++) {
        if(table.terminals[i] != 'e') {
            fprintf(output, "----------");
        }
    }
    fprintf(output, "\n");
    
    for(int i = 0; i < table.nonTerminalCount; i++) {
        fprintf(output, "%-10c", table.nonTerminals[i]);
        for(int j = 0; j < table.terminalCount; j++) {
            if(table.terminals[j] != 'e') {
                if(table.entries[i][j].production)
                    fprintf(output, "%-10s", table.entries[i][j].production);
                else
                    fprintf(output, "%-10s", "");
            }
        }
        fprintf(output, "\n");
    }

    // Also print to console for verification
    printf("\nLL(1) Parsing Table has been written to output.txt\n");


    fclose(input);
    fclose(output);
}

void collectTerminalsAndNonTerminals() {
    table.terminalCount = 0;
    table.nonTerminalCount = 0;

    // Collect terminals and non-terminals
    for(int i = 0; i < count; i++) {
        // Add LHS to non-terminals
        int found = 0;
        for(int j = 0; j < table.nonTerminalCount; j++) {
            if(table.nonTerminals[j] == productions[i].lhs) {
                found = 1;
                break;
            }
        }
        if(!found) table.nonTerminals[table.nonTerminalCount++] = productions[i].lhs;

        // Process RHS
        for(int j = 0; j < productions[i].altCount; j++) {
            char *rhs = productions[i].rhs[j];
            for(int k = 0; k < strlen(rhs); k++) {
                // Skip epsilon when collecting terminals
                if(isTerminal(rhs[k]) && rhs[k] != 'e') {
                    found = 0;
                    for(int l = 0; l < table.terminalCount; l++) {
                        if(table.terminals[l] == rhs[k]) {
                            found = 1;
                            break;
                        }
                    }
                    if(!found) table.terminals[table.terminalCount++] = rhs[k];
                }
            }
        }
    }
    // Add $ as terminal
    table.terminals[table.terminalCount++] = '$';
}

void generateParsingTable() {
    for (int i = 0; i < count; i++) {
        char nonTerm = productions[i].lhs;
        int row = getNonTerminalIndex(nonTerm);

        for (int j = 0; j < productions[i].altCount; j++) {
            char *prod = productions[i].rhs[j];

            // Step 1: Compute FIRST(prod)
            int hasEpsilon = 0;
            for (int k = 0; k < strlen(prod); k++) {
                char symbol = prod[k];
                
                if (isTerminal(symbol)) {
                    int col = getTerminalIndex(symbol);
                    table.entries[row][col].production = prod;
                    break;
                } else {
                    int firstIdx = getFirstIndex(symbol);
                    for (int f = 0; f < firstSet[firstIdx].count; f++) {
                        char sym = firstSet[firstIdx].set[f];
                        if (sym == 'e') {
                            hasEpsilon = 1;
                        } else {
                            int col = getTerminalIndex(sym);
                            table.entries[row][col].production = prod;
                        }
                    }

                    // If this symbol does not derive epsilon, stop
                    int foundEpsilon = 0;
                    for (int f = 0; f < firstSet[firstIdx].count; f++) {
                        if (firstSet[firstIdx].set[f] == 'e') {
                            foundEpsilon = 1;
                            break;
                        }
                    }
                    if (!foundEpsilon) break;
                }

                // If all symbols so far have epsilon, continue to next
                if (k == strlen(prod) - 1 && hasEpsilon) {
                    // Add to FOLLOW(nonTerm)
                    int followIdx = getFollowIndex(nonTerm);
                    for (int f = 0; f < followSet[followIdx].count; f++) {
                        int col = getTerminalIndex(followSet[followIdx].set[f]);
                        table.entries[row][col].production = prod;
                    }
                }
            }

            // Special case: if the production is just epsilon (i.e., 'e')
            if (prod[0] == 'e' && prod[1] == '\0') {
                int followIdx = getFollowIndex(nonTerm);
                for (int f = 0; f < followSet[followIdx].count; f++) {
                    int col = getTerminalIndex(followSet[followIdx].set[f]);
                    table.entries[row][col].production = prod;
                }
            }
        }
    }
}

// adding to the first set
void addToFirst(char nonTerm, char term){
    int found = 0;

    // searching for existing first sets for non terminals
    for(int i = 0; i < firstCount; i++){
        if(firstSet[i].nonTerm == nonTerm){
            found = 1;

            // checking for duplicates
            for(int j = 0; j < firstSet[i].count; j++){
                if(firstSet[i].set[j] == term) return;
            }

            // add new terminal to first set
            firstSet[i].set[firstSet[i].count++] = term;
            return;
        }
    }

    if(!found) {
        firstSet[firstCount].nonTerm = nonTerm;
        firstSet[firstCount].set[0] = term;
        firstSet[firstCount].count = 1;
        firstCount++;
    }
}
// find firsts
void computeFirst(char symbol){
    if(isTerminal(symbol)){
        addToFirst(symbol, symbol);
        return;
    }

    for(int i = 0; i < count; i++){
        if(productions[i].lhs == symbol){
            for(int j = 0; j < productions[i].altCount; j++){
                char *rhs = productions[i].rhs[j];

                // Handle epsilon directly
                if(rhs[0] == 'e'){
                    addToFirst(symbol, 'e');
                    continue;
                }

                // Scan symbols in RHS left to right
                int k;
                for(k = 0; k < strlen(rhs); k++){
                    char curr = rhs[k];

                    if(isTerminal(curr)){
                        addToFirst(symbol, curr);
                        break;
                    } else {
                        computeFirst(curr);

                        // Copy FIRST(curr) into FIRST(symbol), excluding epsilon
                        int hasEpsilon = 0;
                        for(int f = 0; f < firstCount; f++){
                            if(firstSet[f].nonTerm == curr){
                                for(int m = 0; m < firstSet[f].count; m++){
                                    char term = firstSet[f].set[m];
                                    if(term == 'e') hasEpsilon = 1;
                                    else addToFirst(symbol, term);
                                }
                                break;
                            }
                        }

                        if(!hasEpsilon){
                            break; // stop if epsilon not present
                        }
                    }
                }

                // if we reached the end of rhs, and all had epsilon
                if(k == strlen(rhs)){
                    addToFirst(symbol, 'e');
                }
            }
        }
    }
}

// adding to the follow set
void addToFollow(char nonTerm, char term){
    int found = 0;

    for (int i = 0; i < followCount; i++){
        if(followSet[i].nonTerm == nonTerm){
            found = 1;

            for(int j = 0; j < followSet[i].count; j++){
                if(followSet[i].set[j] == term) return;
            }

            followSet[i].set[followSet[i].count++] = term;
            return;
        }
    }

    if(!found) {
        followSet[followCount].nonTerm = nonTerm;
        followSet[followCount].set[0] = term;
        followSet[followCount].count = 1;
        followCount++;
    }
}

// find follow
void computeFollow() {
    addToFollow(productions[0].lhs, '$');

    int changed = 1;

    while(changed){
        changed = 0;

        for(int i = 0; i < count; i++){
            char lhs = productions[i].lhs;

            for(int j = 0; j < productions[i].altCount; j++){
                char *rhs = productions[i].rhs[j];
                int len = strlen(rhs);

                for(int k = 0; k < len; k++){
                    char charFromRHS = rhs[k];
                    if(isTerminal(charFromRHS)) continue;

                    if(k+1 < len) {
                        char next = rhs[k+1];
                        int index = getFollowIndex(charFromRHS);

                        if(isTerminal(next)){
                            if(index != -1 && strchr(followSet[index].set, next) == NULL){
                                addToFollow(charFromRHS, next);
                                changed = 1;
                            }
                        }
                        else{

                            // adding FIRST(next), excludes epsilon (e)
                            for(int f = 0; f < firstCount; f++){
                                if(firstSet[f].nonTerm == next){

                                    for(int m = 0; m < firstSet[f].count; m++){
                                        if(firstSet[f].set[m] != 'e'){
                                            int idx = getFollowIndex(charFromRHS);
                                            int oldCount = (idx != -1) ? followSet[idx].count : 0;
                                            addToFollow(charFromRHS, firstSet[f].set[m]);

                                            if(oldCount != followSet[idx].count) changed = 1;
                                        }
                                    }

                                    int hasEpsilon = 0;

                                    for(int m = 0; m < firstSet[f].count; m++){
                                        if(firstSet[f].set[m] == 'e'){
                                            hasEpsilon = 1;
                                            break;
                                        }
                                    }

                                    if(hasEpsilon){
                                        for(int x = 0; x < followCount; x++){
                                            if(followSet[x].nonTerm == lhs){
                                                for(int y = 0; y < followSet[x].count; y++){
                                                    int idx = getFollowIndex(charFromRHS);
                                                    int oldCount = (idx != -1) ? followSet[idx].count : 0;
                                                    addToFollow(charFromRHS, followSet[x].set[y]);
                                                    if (oldCount != followSet[idx].count) changed = 1;
                                                }
                                                break;
                                            }
                                        }
                                    }

                                    break;

                                }
                            }
                        }
                    }
                    else{
                        for (int x = 0; x < followCount; x++) {
                            if (followSet[x].nonTerm == lhs) {
                                for (int y = 0; y < followSet[x].count; y++) {
                                    int idx = getFollowIndex(charFromRHS);
                                    int oldCount = (idx != -1) ? followSet[idx].count : 0;
                                    addToFollow(charFromRHS, followSet[x].set[y]);
                                    if (oldCount != followSet[idx].count) changed = 1;
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

// parse the prodcution rules
void parsingProductionRules(char *line){
    char lhs, *arrow, *token, *savePtr;

    arrow = strstr(line, "=");
    if(!arrow) return;

    lhs = line[0];
    char *rhs = arrow + 1;

    // removing leading space if there is any
    while (*rhs == ' ') rhs++;

    // removing new lines
    rhs[strcspn(rhs, "\n")] = '\0';

    productionRule *rule = &productions[count++];
    rule->lhs = lhs;
    rule->altCount = 0;

    // split the right side if "|" found
    token = strtok(rhs, "|");
    while(token) {
        // removing leading spaces
        while (*token == ' ') {
            token++;
        }

        strcpy(rule->rhs[rule->altCount++], token);
        token = strtok(NULL, "|");        
    }
}