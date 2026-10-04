#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

int minCoins(int coins[], int n, int V) {
    int *dp = (int *)malloc((V + 1) * sizeof(int));

    dp[0] = 0;

    for (int i = 1; i <= V; i++)
        dp[i] = INF;

    for (int amount = 1; amount <= V; amount++) {
        for (int i = 0; i < n; i++) {
            if (coins[i] <= amount &&
                dp[amount - coins[i]] != INF) {

                int candidate = dp[amount - coins[i]] + 1;

                if (candidate < dp[amount])
                    dp[amount] = candidate;
            }
        }
    }

    int answer = (dp[V] == INF) ? -1 : dp[V];

    free(dp);
    return answer;
}

int main() {
    int n, V;

    printf("Enter number of coin denominations: ");
    scanf("%d", &n);

    int *coins = malloc(n * sizeof(int));

    printf("Enter coin denominations:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &coins[i]);

    printf("Enter target amount: ");
    scanf("%d", &V);

    printf("Minimum coins = %d\n", minCoins(coins, n, V));

    free(coins);

    return 0;
}