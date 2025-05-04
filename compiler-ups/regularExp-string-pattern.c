#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

// Match a character against a set like [a-z]
bool match_set(const char *pattern, char c, int *advance) {
    bool matched = false;
    if (*pattern == '[') {
        pattern++;
        while (*pattern && *pattern != ']') {
            if (*(pattern + 1) == '-' && isalpha(*(pattern + 2))) {
                char start = *pattern;
                char end = *(pattern + 2);
                if (c >= start && c <= end) matched = true;
                pattern += 3;
            } else {
                if (*pattern == c) matched = true;
                pattern++;
            }
        }
        while (*pattern && *pattern != ']') pattern++;
        if (*pattern == ']') pattern++;
        *advance = pattern - (pattern - *advance);
    }
    return matched;
}

// Recursive match function
bool match_here(const char *text, const char *pattern);

bool match_star(char c, const char *pattern, const char *text) {
    do {
        if (match_here(text, pattern)) return true;
    } while (*text != '\0' && (*text++ == c || c == '.'));
    return false;
}

bool match_plus(char c, const char *pattern, const char *text) {
    if (*text != '\0' && (*text == c || c == '.')) {
        text++;
        return match_star(c, pattern, text);
    }
    return false;
}

bool match_question(char c, const char *pattern, const char *text) {
    if (*text != '\0' && (*text == c || c == '.')) {
        if (match_here(text + 1, pattern)) return true;
    }
    return match_here(text, pattern);
}

bool match_here(const char *text, const char *pattern) {
    if (*pattern == '\0') return *text == '\0';

    if (pattern[0] == '[') {
        int advance = 0;
        if (match_set(pattern, *text, &advance)) {
            pattern += advance;
            if (pattern[0] == '*') return match_star(*text, pattern + 1, text + 1);
            else if (pattern[0] == '+') return match_plus(*text, pattern + 1, text + 1);
            else if (pattern[0] == '?') return match_question(*text, pattern + 1, text + 1);
            else return match_here(text + 1, pattern);
        } 
        else {
            return false;
        }
    }

    if (pattern[1] == '*') return match_star(pattern[0], pattern + 2, text);
    if (pattern[1] == '+') return match_plus(pattern[0], pattern + 2, text);
    if (pattern[1] == '?') return match_question(pattern[0], pattern + 2, text);

    if (*text != '\0' && (pattern[0] == '.' || pattern[0] == *text)) {
        return match_here(text + 1, pattern + 1);
    }
    return false;
}

bool match(const char *text, const char *pattern) {
    return match_here(text, pattern);
}

int main() {
    FILE *infile = fopen("test2.txt", "r");
    FILE *outfile = fopen("output.txt", "w");

    if (!infile || !outfile) {
        printf("Error opening files.\n");
        return 1;
    }

    char text[100], pattern[100];

    // Read from input file
    if (fscanf(infile, "%s", text) != 1 || fscanf(infile, "%s", pattern) != 1) {
        fprintf(outfile, "Invalid input format.\n");
        fclose(infile);
        fclose(outfile);
        return 1;
    }

    fprintf(outfile, "Text: %s\n", text);
    fprintf(outfile, "Pattern: %s\n", pattern);

    if (match(text, pattern)) {
        fprintf(outfile, "Result: Pattern matches the text!\n");
    } else {
        fprintf(outfile, "Result: Pattern does NOT match the text.\n");
    }

    fclose(infile);
    fclose(outfile);
    return 0;
}