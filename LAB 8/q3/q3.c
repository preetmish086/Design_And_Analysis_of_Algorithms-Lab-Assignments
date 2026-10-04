#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

void printLCS(char X[], char Y[]) {
    int m = strlen(X);
    int n = strlen(Y);

    int **dp = malloc((m + 1) * sizeof(int *));

    for (int i = 0; i <= m; i++)
        dp[i] = calloc(n + 1, sizeof(int));

    /* Build DP table */
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {

            if (X[i - 1] == Y[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;

            else
                dp[i][j] = max(dp[i - 1][j],
                               dp[i][j - 1]);
        }
    }

    int length = dp[m][n];

    char *lcs = malloc((length + 1) * sizeof(char));
    lcs[length] = '\0';

    int i = m;
    int j = n;
    int index = length - 1;

    /* Traceback */
    while (i > 0 && j > 0) {

        if (X[i - 1] == Y[j - 1]) {
            lcs[index--] = X[i - 1];
            i--;
            j--;
        }
        else if (dp[i - 1][j] >= dp[i][j - 1]) {
            i--;
        }
        else {
            j--;
        }
    }

    printf("LCS length = %d\n", length);
    printf("LCS = %s\n", lcs);

    free(lcs);

    for (int k = 0; k <= m; k++)
        free(dp[k]);

    free(dp);
}

int main() {
    char X[1000], Y[1000];

    printf("Enter first string: ");
    scanf("%999s", X);

    printf("Enter second string: ");
    scanf("%999s", Y);

    printLCS(X, Y);

    return 0;
}