#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int LIS(int A[], int n) {
    int *dp = malloc(n * sizeof(int));

    int answer = 1;

    for (int i = 0; i < n; i++)
        dp[i] = 1;

    for (int i = 1; i < n; i++) {

        for (int j = 0; j < i; j++) {

            if (A[j] < A[i])
                dp[i] = max(dp[i], dp[j] + 1);
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

    printf("Enter array:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    printf("LIS length = %d\n", LIS(A, n));

    free(A);

    return 0;
}