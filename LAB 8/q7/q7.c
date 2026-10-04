#include <stdio.h>
#include <stdlib.h>

void rodCutting(int price[], int n) {
    int *dp = malloc((n + 1) * sizeof(int));
    int *choice = malloc((n + 1) * sizeof(int));

    dp[0] = 0;

    for (int i = 1; i <= n; i++) {

        dp[i] = -1000000000;
        choice[i] = 0;

        for (int j = 1; j <= i; j++) {

            int candidate = price[j] + dp[i - j];

            if (candidate > dp[i]) {
                dp[i] = candidate;
                choice[i] = j;
            }
        }
    }

    printf("Maximum revenue = %d\n", dp[n]);

    printf("Optimal pieces: ");

    int remaining = n;

    while (remaining > 0) {
        printf("%d ", choice[remaining]);
        remaining -= choice[remaining];
    }

    printf("\n");

    free(dp);
    free(choice);
}

int main() {
    int n;

    printf("Enter rod length: ");
    scanf("%d", &n);

    int *price = malloc((n + 1) * sizeof(int));

    price[0] = 0;

    printf("Enter prices p[1] ... p[%d]:\n", n);

    for (int i = 1; i <= n; i++)
        scanf("%d", &price[i]);

    rodCutting(price, n);

    free(price);

    return 0;
}