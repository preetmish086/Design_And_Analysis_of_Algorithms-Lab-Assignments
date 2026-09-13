#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int eggDrop(int E, int F)
{
    int **dp = (int **)malloc((E + 1) * sizeof(int *));

    for (int i = 0; i <= E; i++)
        dp[i] = (int *)malloc((F + 1) * sizeof(int));

    /* Base cases */
    for (int e = 0; e <= E; e++)
        dp[e][0] = 0;

    for (int f = 1; f <= F; f++)
        dp[1][f] = f;

    /* DP */
    for (int e = 2; e <= E; e++)
    {
        for (int f = 1; f <= F; f++)
        {
            dp[e][f] = 999999;

            /* Try dropping from every floor k */
            for (int k = 1; k <= f; k++)
            {
                int breaks = dp[e - 1][k - 1];
                int survives = dp[e][f - k];

                int worst = 1 + max(breaks, survives);

                if (worst < dp[e][f])
                    dp[e][f] = worst;
            }
        }
    }

    int answer = dp[E][F];

    for (int e = 0; e <= E; e++)
        free(dp[e]);

    free(dp);

    return answer;
}

int main()
{
    int E, F;

    printf("Enter number of eggs: ");
    scanf("%d", &E);

    printf("Enter number of floors: ");
    scanf("%d", &F);

    if (E <= 0 || F < 0)
    {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Minimum number of droppings = %d\n",
           eggDrop(E, F));

    return 0;
}