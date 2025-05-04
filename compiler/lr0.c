#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUCTIONS 50
#define MAX_SYMBOLS 50
#define MAX_ITEMS 200
#define MAX_STATES 100
#define MAX_LINE 100

typedef struct{
    int prod_index;
    int dot_pos;
} Item;

typedef struct{
    Item items[MAX_ITEMS];
    int item_count;
} State;

char productions[MAX_PRODUCTIONS][MAX_LINE];
int production_count = 0;

char symbols[MAX_SYMBOLS];
int symbol_count = 0;

char terminals[MAX_SYMBOLS];
int terminal_count = 0;

char nonterminals[MAX_SYMBOLS];
int nonterminal_count = 0;

State states[MAX_STATES];
int state_count = 0;

char ACTION[MAX_STATES][MAX_SYMBOLS][20];
int GOTO[MAX_STATES][MAX_SYMBOLS];

FILE *output;

void add_symbol(char c){
    for (int i = 0; i < symbol_count; i++){
        if (symbols[i] == c) return;
    }
            
    symbols[symbol_count++] = c;
    if (isupper(c)){
        nonterminals[nonterminal_count++] = c;
    }
    else{
        terminals[terminal_count++] = c;
    }
}

void read_grammar(){
    FILE *input = fopen("test2.txt", "r");
    if (!input){
        printf("Cannot open input file\n");
        exit(1);
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), input)){
        if (line[0] == '\n' || line[0] == '\0') break;
        line[strcspn(line, "\n")] = '\0';
        strcpy(productions[production_count++], line);

        for (int i = 0; i < strlen(line); i++){
            if (line[i] != '=' && line[i] != '-' && line[i] != '>' && line[i] != '\0'){
                add_symbol(line[i]);
            }
                
        }
    }
    fclose(input);
}

void compute_closure(State *s){
    int changed = 1;
    while (changed){
        changed = 0;
        for (int i = 0; i < s->item_count; i++){
            Item it = s->items[i];
            char *prod = productions[it.prod_index];
            char B = prod[3 + it.dot_pos];

            if (!isupper(B)) continue;                

            for (int j = 0; j < production_count; j++){
                if (productions[j][0] == B){
                    int exists = 0;
                    for (int k = 0; k < s->item_count; k++){
                        if (s->items[k].prod_index == j && s->items[k].dot_pos == 0){
                            exists = 1;
                            break;
                        }
                    }
                    if (!exists){
                        s->items[s->item_count].prod_index = j;
                        s->items[s->item_count].dot_pos = 0;
                        s->item_count++;
                        changed = 1;
                    }
                }
            }
        }
    } 
}

State goto_state(State *state, char X){
    State new_state = {.item_count = 0};
    for (int i = 0; i < state->item_count; i++){
        Item it = state->items[i];
        char *prod = productions[it.prod_index];
        if (prod[3 + it.dot_pos] == X){
            new_state.items[new_state.item_count].prod_index = it.prod_index;
            new_state.items[new_state.item_count].dot_pos = it.dot_pos + 1;
            new_state.item_count++;
        }
    }
    compute_closure(&new_state);
    return new_state;
}

int state_exists(State *s){
    for (int i = 0; i < state_count; i++){

        if (states[i].item_count != s->item_count) continue;

        int match = 1;
        for (int j = 0; j < s->item_count; j++){
            if (states[i].items[j].prod_index != s->items[j].prod_index ||
                states[i].items[j].dot_pos != s->items[j].dot_pos){
                match = 0;
                break;
            }
        }
        if (match) return i;
    }
    return -1;
}

int add_state(State s){
    int index = state_exists(&s);
    if (index != -1) return index;
    states[state_count] = s;
    return state_count++;
}

void build_states(){
    // Augment grammar: S'->S (if not already)
    char new_start[MAX_LINE];
    sprintf(new_start, "Z->%c", productions[0][0]); // Z->S
    for (int i = production_count; i > 0; i--){
        strcpy(productions[i], productions[i - 1]);
    }
    strcpy(productions[0], new_start);
    production_count++;

    // Add end marker
    // add_symbol('$');
    // terminals[terminal_count++] = '$';
    add_symbol('$');
    int exists = 0;
    for (int i = 0; i < terminal_count; i++){
        if (terminals[i] == '$'){
            exists = 1;
            break;
        }
    }
    if (!exists) terminals[terminal_count++] = '$';        

    // Initial state
    State start = {.item_count = 1};
    start.items[0].prod_index = 0;
    start.items[0].dot_pos = 0;
    compute_closure(&start);
    add_state(start);

    for (int i = 0; i < state_count; i++){
        for (int j = 0; j < symbol_count; j++){
            char X = symbols[j];
            State to = goto_state(&states[i], X);

            if (to.item_count == 0) continue;
            int to_index = add_state(to);
            if (isupper(X)){
                GOTO[i][X] = to_index;
            }
            else{
                sprintf(ACTION[i][X], "s%d", to_index);
            }
        }
    }

    // Add reduce / accept actions
    for (int i = 0; i < state_count; i++){
        for (int j = 0; j < states[i].item_count; j++){
            Item it = states[i].items[j];
            char *prod = productions[it.prod_index];
            int len = strlen(prod + 3);

            if (it.dot_pos == len){
                if (it.prod_index == 0){
                    strcpy(ACTION[i]['$'], "acc");
                }
                else{
                    for (int t = 0; t < terminal_count; t++){
                        char a = terminals[t];
                        sprintf(ACTION[i][a], "r%d", it.prod_index);
                    }
                }
            }
        }
    }
}

void write_table(){
    fprintf(output, "\nLR(0) Parsing Table\n\n");
    fprintf(output, "%-7s", "State");

    for (int i = 0; i < terminal_count; i++){
        fprintf(output, "%-7c", terminals[i]);
    }

    for (int i = 0; i < nonterminal_count; i++){
        fprintf(output, "%-7c", nonterminals[i]);
    }

    fprintf(output, "\n");

    for (int i = 0; i < state_count; i++){
        fprintf(output, "%-7d", i);
        for (int j = 0; j < terminal_count; j++){
            char a = terminals[j];
            fprintf(output, "%-7s", ACTION[i][a][0] ? ACTION[i][a] : "");
        }
        for (int j = 0; j < nonterminal_count; j++){
            char A = nonterminals[j];
            if (GOTO[i][A]){
                fprintf(output, "%-7d", GOTO[i][A]);
            }
            else{
                fprintf(output, "%-7s", "");
            }
        }
        fprintf(output, "\n");
    }
}

int main(){
    output = fopen("output.txt", "w");
    if (!output){
        printf("Could not open output.txt\n");
        return 1;
    }

    read_grammar();
    build_states();
    write_table();

    fclose(output);
    printf("Parsing table written to output file\n");
    return 0;
}
