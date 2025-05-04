// LALR(1) Parser Table Generator with Merged State Support
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROD 20
#define MAX_ITEMS 100
#define MAX_SYMBOLS 40
#define MAX_STATES 100
#define MAX_LEN 20

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

Production productions[MAX_PROD + 1];
int num_productions;
char symbols[MAX_SYMBOLS];
int num_symbols;
ItemSet states[MAX_STATES];
int num_states;
int action[MAX_STATES][MAX_SYMBOLS];
int goTo[MAX_STATES][MAX_SYMBOLS];
int core_map[MAX_STATES]; // map LR(1) states to merged LALR states
char state_names[MAX_STATES][20]; // string names of merged states

int is_terminal(char c) {
    return !(c >= 'A' && c <= 'Z');
}

int symbol_index(char c) {
    for (int i = 0; i < num_symbols; i++)
        if (symbols[i] == c) return i;
    return -1;
}

void add_symbol(char c) {
    if (symbol_index(c) < 0 && num_symbols < MAX_SYMBOLS)
        symbols[num_symbols++] = c;
}

int item_equal(Item a, Item b) {
    return a.prod_id == b.prod_id && a.dot_pos == b.dot_pos && a.lookahead == b.lookahead;
}

int core_equal(Item a, Item b) {
    return a.prod_id == b.prod_id && a.dot_pos == b.dot_pos;
}

int itemset_core_equal(ItemSet *a, ItemSet *b) {
    if (a->count != b->count) return 0;
    for (int i = 0; i < a->count; i++) {
        int found = 0;
        for (int j = 0; j < b->count; j++) {
            if (core_equal(a->items[i], b->items[j])) { found = 1; break; }
        }
        if (!found) return 0;
    }
    return 1;
}

void compute_first(char *beta, char lookahead, char *out) {
    int len = strlen(beta);
    if (len == 0 || is_terminal(beta[0])) {
        out[0] = (len > 0 ? beta[0] : lookahead);
        out[1] = '\0';
        return;
    }

    int count = 0;
    for (int i = 1; i < num_productions; i++) {
        if (productions[i].lhs == beta[0]) {
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
                    beta[blen + 1] = '\0';
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
        if (I->count == states[i].count) {
            int match = 1;
            for (int j = 0; j < I->count; j++) {
                int found = 0;
                for (int k = 0; k < states[i].count; k++) {
                    if (item_equal(I->items[j], states[i].items[k])) {
                        found = 1; break;
                    }
                }
                if (!found) { match = 0; break; }
            }
            if (match) return i;
        }
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

// --- LALR MERGE ---

int merged_state_count = 0;

void merge_states() {
    for (int i = 0; i < num_states; i++) core_map[i] = -1;

    for (int i = 0; i < num_states; i++) {
        if (core_map[i] != -1) continue;
        char name[20] = "";
        core_map[i] = merged_state_count;
        char tmp[10];
        sprintf(tmp, "%d", i);
        strcat(name, tmp);

        for (int j = i + 1; j < num_states; j++) {
            if (core_map[j] == -1 && itemset_core_equal(&states[i], &states[j])) {
                core_map[j] = merged_state_count;
                sprintf(tmp, "%d", j);
                strcat(name, tmp);
            }
        }
        strcpy(state_names[merged_state_count], name);
        merged_state_count++;
    }
}

void print_table(FILE *outfile) {
    fprintf(outfile, "%-10s", "STATE");
    for (int j = 0; j < num_symbols; j++) {
        fprintf(outfile, "%c\t", symbols[j]);
    }
    fprintf(outfile, "\n");

    for (int m = 0; m < merged_state_count; m++) {
        fprintf(outfile, "%-10s", state_names[m]);
        int base_lr1_state = -1;
        for (int i = 0; i < num_states; i++) {
            if (core_map[i] == m) {
                base_lr1_state = i;
                break;
            }
        }

        if (base_lr1_state != -1) {
            for (int j = 0; j < num_symbols; j++) {
                if (is_terminal(symbols[j])) {
                    int v = action[base_lr1_state][j];
                    if (v > 0) fprintf(outfile, "s%d\t", core_map[v - 1]);
                    else if (v < 0) fprintf(outfile, v == -999 ? "acc\t" : "r%d\t", -v);
                    else fprintf(outfile, "\t");
                } else {
                    int v = goTo[base_lr1_state][j];
                    if (v != 0) fprintf(outfile, "%d\t", core_map[v]);
                    else fprintf(outfile, "\t");
                }
            }
        } else {
            for (int j = 0; j < num_symbols; j++) {
                fprintf(outfile, "\t");
            }
        }
        fprintf(outfile, "\n");
    }
}
// --- MAIN ---
int main() {
    FILE *infile = fopen("test2.txt", "r");
    if (!infile) {
        perror("Error opening input file");
        return 1;
    }

    FILE *outfile = fopen("output.txt", "w");
    if (!outfile) {
        perror("Error opening output file");
        fclose(infile);
        return 1;
    }

    int n = 0;
    Production temp[MAX_PROD];
    char buf[50];

    while (fgets(buf, sizeof(buf), infile)) {
        buf[strcspn(buf, "\n")] = '\0';
        if (strlen(buf) > 0) {
            temp[n].lhs = buf[0];
            strcpy(temp[n].rhs, buf + 3);
            add_symbol(temp[n].lhs);
            for (int k = 0; k < (int)strlen(temp[n].rhs); k++)
                add_symbol(temp[n].rhs[k]);
            n++;
        }
    }

    fclose(infile);

    productions[0].lhs = 'Z';
    productions[0].rhs[0] = temp[0].lhs;
    productions[0].rhs[1] = '\0';
    add_symbol('$');

    int prod_idx = 1;
    for (int i = 0; i < n; i++) {
        char *rhs = temp[i].rhs;
        char *seg = strtok(rhs, "|");
        while (seg) {
            productions[prod_idx].lhs = temp[i].lhs;
            strcpy(productions[prod_idx].rhs, seg);
            for (int k = 0; k < (int)strlen(seg); k++)
                if (seg[k] != '|') add_symbol(seg[k]);
            prod_idx++;
            seg = strtok(NULL, "|");
        }
    }
    num_productions = prod_idx;

    construct_states();
    merge_states();
    print_table(outfile);

    fclose(outfile);
    return 0;
}