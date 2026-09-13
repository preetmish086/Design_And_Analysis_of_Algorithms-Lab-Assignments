#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF LLONG_MAX

long long min(long long a, long long b)
{
    return (a < b) ? a : b;
}

// Prints the optimal parenthesization
void printOptimalParenthesis(int **split, int i, int j)
{
    if (i == j)
    {
        printf("A%d", i);
        return;
    }

    printf("(");

    int k = split[i][j];

    printOptimalParenthesis(split, i, k);
    printOptimalParenthesis(split, k + 1, j);

    printf(")");
}

int main()
{
    int n;

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid number of matrices.\n");
        return 1;
    }

    // p has n+1 dimensions
    long long *p =
        (long long *)malloc((n + 1) * sizeof(long long));

    // DP table
    long long **m =
        (long long **)malloc((n + 1) * sizeof(long long *));

    // Split table
    int **split =
        (int **)malloc((n + 1) * sizeof(int *));

    for (int i = 0; i <= n; i++)
    {
        m[i] =
            (long long *)malloc((n + 1) * sizeof(long long));

        split[i] =
            (int *)malloc((n + 1) * sizeof(int));
    }

    printf("\nEnter dimensions:\n");
    printf("For matrices A1...A%d, enter %d dimensions:\n",
           n, n + 1);

    for (int i = 0; i <= n; i++)
    {
        scanf("%lld", &p[i]);
    }

    // Cost of multiplying one matrix = 0
    for (int i = 1; i <= n; i++)
    {
        m[i][i] = 0;
    }

    // Chain length
    for (int length = 2; length <= n; length++)
    {
        for (int i = 1; i <= n - length + 1; i++)
        {
            int j = i + length - 1;

            m[i][j] = INF;

            // Try every possible split
            for (int k = i; k < j; k++)
            {
                long long cost =
                    m[i][k]
                    + m[k + 1][j]
                    + p[i - 1] * p[k] * p[j];

                if (cost < m[i][j])
                {
                    m[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }

    printf("\nMinimum number of scalar multiplications = %lld\n",
           m[1][n]);

    printf("Optimal ordering = ");
    printOptimalParenthesis(split, 1, n);
    printf("\n");

    // Free memory
    for (int i = 0; i <= n; i++)
    {
        free(m[i]);
        free(split[i]);
    }

    free(m);
    free(split);
    free(p);

    return 0;
}