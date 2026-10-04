#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min3(int a, int b, int c) {
    int result = a;

    if (b < result)
        result = b;

    if (c < result)
        result = c;

    return result;
}

void editDistance(char A[], char B[]) {
    int m = strlen(A);
    int n = strlen(B);

    int **dp = malloc((m + 1) * sizeof(int *));

    for (int i = 0; i <= m; i++)
        dp[i] = malloc((n + 1) * sizeof(int));

    /* Base cases */
    for (int i = 0; i <= m; i++)
        dp[i][0] = i;

    for (int j = 0; j <= n; j++)
        dp[0][j] = j;

    /* Fill table */
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {

            if (A[i - 1] == B[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else {
                dp[i][j] = 1 + min3(
                    dp[i - 1][j],     // delete
                    dp[i][j - 1],     // insert
                    dp[i - 1][j - 1]  // substitute
                );
            }
        }
    }

    printf("Edit distance = %d\n\n", dp[m][n]);
    printf("Traceback:\n");

    int i = m;
    int j = n;

    while (i > 0 || j > 0) {

        if (i > 0 && j > 0 &&
            A[i - 1] == B[j - 1]) {

            printf("Keep '%c'\n", A[i - 1]);
            i--;
            j--;
        }

        else if (i > 0 &&
                 dp[i][j] == dp[i - 1][j] + 1) {

            printf("Delete '%c'\n", A[i - 1]);
            i--;
        }

        else if (j > 0 &&
                 dp[i][j] == dp[i][j - 1] + 1) {

            printf("Insert '%c'\n", B[j - 1]);
            j--;
        }

        else {
            printf("Substitute '%c' -> '%c'\n",
                   A[i - 1], B[j - 1]);

            i--;
            j--;
        }
    }

    for (int k = 0; k <= m; k++)
        free(dp[k]);

    free(dp);
}

int main() {
    char A[1000], B[1000];

    printf("Enter source string: ");
    scanf("%999s", A);

    printf("Enter target string: ");
    scanf("%999s", B);

    editDistance(A, B);

    return 0;
}