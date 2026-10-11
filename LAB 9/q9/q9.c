
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

long long w[MAX];
long long prefix[MAX + 1];
long long dp[MAX][MAX];
int split[MAX][MAX];

void printTree(int i, int j, int depth)
{
    if (i == j) {
        printf("Leaf %d (weight %lld), depth %d\n",
               i + 1, w[i], depth);
        return;
    }

    int k = split[i][j];

    printf("Internal node [%d..%d], depth %d\n",
           i + 1, j + 1, depth);

    printTree(i, k, depth + 1);
    printTree(k + 1, j, depth + 1);
}

int main(void)
{
    int n;

    printf("Enter number of leaves (1-%d): ", MAX);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of leaves.\n");
        return 1;
    }

    printf("Enter the weights in their fixed order:\n");
    for (int i = 0; i < n; i++) {
        if (scanf("%lld", &w[i]) != 1 || w[i] < 0) {
            printf("Weights must be non-negative integers.\n");
            return 1;
        }

        prefix[i + 1] = prefix[i] + w[i];
    }

    /* A single leaf has depth 0, so its cost is 0. */
    for (int i = 0; i < n; i++) {
        dp[i][i] = 0;
        split[i][i] = -1;
    }

    /* Build solutions for increasingly large intervals. */
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len <= n; i++) {
            int j = i + len - 1;
            long long sum = prefix[j + 1] - prefix[i];

            dp[i][j] = LLONG_MAX;

            for (int k = i; k < j; k++) {
                long long candidate =
                    dp[i][k] + dp[k + 1][j] + sum;

                if (candidate < dp[i][j]) {
                    dp[i][j] = candidate;
                    split[i][j] = k;
                }
            }
        }
    }

    printf("\nMinimum weighted path cost = %lld\n",
           dp[0][n - 1]);

    printf("\nTree structure:\n");
    printTree(0, n - 1, 0);

    return 0;
}
