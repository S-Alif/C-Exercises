#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROD 100
#define MAX_ITEMS 200
#define MAX_SYMBOLS 50
#define MAX_STATES 100
#define MAX_LEN 50

typedef struct {
    char lhs;
    char rhs[MAX_LEN];
} Production;

typedef struct {
    int prod_id;
    int dot_pos;
    char lookahead;
} Item;

typedef struct {
    Item items[MAX_ITEMS];
    int count;
} ItemSet;

Production productions[MAX_PROD];
int num_productions = 0;
char symbols[MAX_SYMBOLS];
int num_symbols = 0;
ItemSet states[MAX_STATES];
int num_states = 0;
int action[MAX_STATES][MAX_SYMBOLS];
int goTo[MAX_STATES][MAX_SYMBOLS];

FILE *outFile;

// ---------- Utility Functions ----------
int is_terminal(char c) {
    return !(c >= 'A' && c <= 'Z');
}

int symbol_index(char c) {
    for (int i = 0; i < num_symbols; i++)
        if (symbols[i] == c) return i;
    return -1;
}

void add_symbol(char c) {
    if (c == 'e') return; // epsilon is not a real symbol - remember it
    if (symbol_index(c) < 0 && num_symbols < MAX_SYMBOLS)
        symbols[num_symbols++] = c;
}

int item_equal(Item a, Item b) {
    return a.prod_id == b.prod_id && a.dot_pos == b.dot_pos && a.lookahead == b.lookahead;
}

int itemset_equal(ItemSet *a, ItemSet *b) {
    if (a->count != b->count) return 0;
    for (int i = 0; i < a->count; i++) {
        int found = 0;
        for (int j = 0; j < b->count; j++)
            if (item_equal(a->items[i], b->items[j])) { found = 1; break; }
        if (!found) return 0;
    }
    return 1;
}

// ---------- Grammar Handling ----------
void compute_first(char *beta, char lookahead, char *out) {
    int len = strlen(beta);
    if (len == 0 || is_terminal(beta[0])) {
        out[0] = (len > 0 ? beta[0] : lookahead);
        out[1] = '\0';
        return;
    }
    int count = 0;
    for (int i = 1; i < num_productions; i++) {
        if (productions[i].lhs == beta[0] && productions[i].rhs[0] != '\0') {
            char c = productions[i].rhs[0];
            if (is_terminal(c)) {
                out[count++] = c;
            }
        }
    }
    if (count == 0) out[count++] = lookahead;
    out[count] = '\0';
}

void closure(ItemSet *I) {
    int changed;
    do {
        changed = 0;
        for (int i = 0; i < I->count; i++) {
            Item itm = I->items[i];
            Production *p = &productions[itm.prod_id];
            if (itm.dot_pos < (int)strlen(p->rhs)) {
                char B = p->rhs[itm.dot_pos];
                if (!is_terminal(B)) {
                    char beta[MAX_LEN + 1] = "";
                    strcpy(beta, p->rhs + itm.dot_pos + 1);
                    int blen = strlen(beta);
                    beta[blen] = itm.lookahead;
                    beta[blen+1] = '\0';

                    char first_set[MAX_LEN];
                    compute_first(beta, itm.lookahead, first_set);
                    for (int j = 1; j < num_productions; j++) {
                        if (productions[j].lhs == B) {
                            for (int f = 0; first_set[f]; f++) {
                                Item new_it = { j, 0, first_set[f] };
                                int exists = 0;
                                for (int k = 0; k < I->count; k++) {
                                    if (item_equal(I->items[k], new_it)) { exists = 1; break; }
                                }
                                if (!exists) {
                                    I->items[I->count++] = new_it;
                                    changed = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    } while (changed);
}

void goto_function(ItemSet *dest, ItemSet *src, char X) {
    dest->count = 0;
    for (int i = 0; i < src->count; i++) {
        Item itm = src->items[i];
        Production *p = &productions[itm.prod_id];
        if (itm.dot_pos < (int)strlen(p->rhs) && p->rhs[itm.dot_pos] == X) {
            Item moved = { itm.prod_id, itm.dot_pos + 1, itm.lookahead };
            dest->items[dest->count++] = moved;
        }
    }
    closure(dest);
}

int add_state(ItemSet *I) {
    for (int i = 0; i < num_states; i++) {
        if (itemset_equal(&states[i], I)) return i;
    }
    states[num_states] = *I;
    return num_states++;
}

void construct_states() {
    ItemSet start = { .count = 1 };
    start.items[0] = (Item){ 0, 0, '$' };
    closure(&start);
    num_states = 0;
    add_state(&start);

    for (int i = 0; i < num_states; i++) {
        ItemSet dest;
        for (int j = 0; j < num_symbols; j++) {
            char X = symbols[j];
            goto_function(&dest, &states[i], X);
            if (dest.count > 0) {
                int idx = add_state(&dest);
                if (is_terminal(X)) action[i][j] = idx + 1;
                else goTo[i][j] = idx;
            }
        }
    }
    for (int i = 0; i < num_states; i++) {
        for (int k = 0; k < states[i].count; k++) {
            Item itm = states[i].items[k];
            Production *p = &productions[itm.prod_id];
            if (itm.dot_pos == (int)strlen(p->rhs)) {
                int a = symbol_index(itm.lookahead);
                if (itm.prod_id == 0 && itm.lookahead == '$') action[i][a] = -999;
                else action[i][a] = -itm.prod_id;
            }
        }
    }
}

void print_table() {
    fprintf(outFile, "      ACTIONS                 | GOTO      \n");
    fprintf(outFile, "      ------------------------|------------\n");
    fprintf(outFile, "State |");

    // Print terminal symbols under ACTION
    for (int j = 0; j < num_symbols; j++){
        if (is_terminal(symbols[j])){
            fprintf(outFile, "  %c  |", symbols[j]);
        }
    }
    // Separator for GOTO
    fprintf(outFile, " ");

    // Print non-terminal symbols under GOTO
    for (int j = 0; j < num_symbols; j++){
        if (!is_terminal(symbols[j])){
            fprintf(outFile, "  %c  |", symbols[j]);
        }
    }

    fprintf(outFile, "\n");

    // Print each row
    for (int i = 0; i < num_states; i++) {
        fprintf(outFile, "  %2d  |", i);

        // ACTION part
        for (int j = 0; j < num_symbols; j++) {
            if (is_terminal(symbols[j])) {
                int val = action[i][j];
                if (val > 0){
                    fprintf(outFile, " s%-2d |", val - 1);
                }                    
                else if (val < 0){
                    fprintf(outFile, val == -999 ? "acc  |" : " r%-2d |", -val);
                }                    
                else{
                    fprintf(outFile, "     |");
                }
            }
        }
        fprintf(outFile, " ");
        // GOTO part
        for (int j = 0; j < num_symbols; j++) {
            if (!is_terminal(symbols[j])) {
                int val = goTo[i][j];
                if (val){
                    fprintf(outFile, " %-3d |", val);
                }
                else{
                    fprintf(outFile, "     |");
                }
            }
        }
        fprintf(outFile, "\n");
    }
}


void read_grammar_from_file(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Cannot open input file.\n");
        exit(1);
    }

    char line[100];
    Production temp[MAX_PROD];
    int temp_count = 0;

    while (fgets(line, sizeof(line), fp)) {
        char lhs = line[0];
        char *rhs = strchr(line, '=');
        if (!rhs) continue;
        rhs++;
        char *token = strtok(rhs, "|\n");
        while (token) {
            temp[temp_count].lhs = lhs;
            if (strcmp(token, "e") == 0) temp[temp_count].rhs[0] = '\0';
            else strcpy(temp[temp_count].rhs, token);
            add_symbol(lhs);
            for (int i = 0; token[i]; i++) add_symbol(token[i]);
            temp_count++;
            token = strtok(NULL, "|\n");
        }
    }
    fclose(fp);

    // Augmented production: Z -> S
    productions[0].lhs = 'Z';
    productions[0].rhs[0] = temp[0].lhs;
    productions[0].rhs[1] = '\0';
    add_symbol('$');
    for (int i = 0; i < temp_count; i++) productions[i + 1] = temp[i];
    num_productions = temp_count + 1;
}

// ---------- Main ----------
int main() {
    read_grammar_from_file("input.txt");

    outFile = fopen("output.txt", "w");
    if (!outFile) {
        printf("Cannot open output file.\n");
        return 1;
    }

    construct_states();
    print_table();
    fclose(outFile);

    printf("CLR parser table has been written\n");
    return 0;
}
