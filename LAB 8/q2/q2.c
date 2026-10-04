#include <stdio.h>
#include <stdlib.h>

long long countWays(int coins[], int n, int V) {
    long long *dp = calloc(V + 1, sizeof(long long));

    dp[0] = 1;

    for (int i = 0; i < n; i++) {
        int coin = coins[i];

        for (int amount = coin; amount <= V; amount++) {
            dp[amount] += dp[amount - coin];
        }
    }

    long long answer = dp[V];

    free(dp);
    return answer;
}

int main() {
    int n, V;

    printf("Enter number of coins: ");
    scanf("%d", &n);

    int *coins = malloc(n * sizeof(int));

    printf("Enter denominations:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &coins[i]);

    printf("Enter target amount: ");
    scanf("%d", &V);

    printf("Total combinations = %lld\n",
           countWays(coins, n, V));

    free(coins);

    return 0;
}