#include <stdio.h>
#include <limits.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int N;

    printf("Enter N: ");
    scanf("%d", &N);

    int arr[N];

    printf("Enter dimensions: ");
    for (int i = 0; i < N; i++)
        scanf("%d", &arr[i]);

    int dp[N][N];

    for (int i = 1; i < N; i++)
        dp[i][i] = 0;

    for (int length = 2; length < N; length++) {
        for (int i = 1; i < N - length + 1; i++) {
            int j = i + length - 1;
            dp[i][j] = INT_MAX;

            for (int k = i; k < j; k++) {
                int cost = dp[i][k]
                         + dp[k + 1][j]
                         + arr[i - 1] * arr[k] * arr[j];

                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    printf("Minimum number of scalar multiplications = %d\n",
           dp[1][N - 1]);

    return 0;
}