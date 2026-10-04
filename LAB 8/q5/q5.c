#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int MSIS(int A[], int n) {
    int *dp = malloc(n * sizeof(int));

    int answer = A[0];

    for (int i = 0; i < n; i++)
        dp[i] = A[i];

    for (int i = 1; i < n; i++) {

        for (int j = 0; j < i; j++) {

            if (A[j] < A[i]) {
                dp[i] = max(dp[i],
                            dp[j] + A[i]);
            }
        }

        answer = max(answer, dp[i]);
    }

    free(dp);

    return answer;
}

int main() {
    int n;

    printf("Enter n: ");
    scanf("%d", &n);

    int *A = malloc(n * sizeof(int));

    printf("Enter positive integers:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    printf("Maximum sum = %d\n", MSIS(A, n));

    free(A);

    return 0;
}