// 0/1 knapsack

#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

void printTable(int table[][100], int n, int W) {
    printf("0/1 Knapsack Table:\n");
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            printf("%d\t", table[i][w]);
        }
        printf("\n");
    }
}

int knapSack(int W, int wt[], int val[], int n) {
    int table[n + 1][100];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                table[i][w] = 0;
            else if (wt[i - 1] <= w)
                table[i][w] = max(val[i - 1] + table[i - 1][w - wt[i - 1]], table[i - 1][w]);
            else
                table[i][w] = table[i - 1][w];
        }
    }

    printTable(table, n, W);

    return table[n][W];
}

int main() {
    int n, W;

    printf("Enter the number of items: ");
    scanf("%d", &n);

    int val[n], wt[n];

    printf("Enter the values of items:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &val[i]);
    }

    printf("Enter the weights of items:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &wt[i]);
    }

    printf("Enter the knapsack capacity: ");
    scanf("%d", &W);

    printf("Maximum value: %d\n", knapSack(W, wt, val, n));

    return 0;
}

