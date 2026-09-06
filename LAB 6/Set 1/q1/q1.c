#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;

    printf("Enter n: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Invalid input\n");
        return 0;
    }

    long long *dp = malloc((n + 1) * sizeof(long long));

    dp[0] = 0;

    if (n >= 1)
        dp[1] = 1;

    for (int i = 2; i <= n; i++)
        dp[i] = dp[i - 1] + dp[i - 2];

    printf("Fibonacci number = %lld\n", dp[n]);

    free(dp);

    return 0;
}