#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Calculate 2^n */
long long power2(int n)
{
    long long result = 1;

    for (int i = 0; i < n; i++)
        result *= 2;

    return result;
}

/* Standard 3-peg Tower of Hanoi */
void hanoi3(int n, char source, char destination, char auxiliary)
{
    if (n == 0)
        return;

    hanoi3(n - 1, source, auxiliary, destination);

    printf("Move disk %d: %c -> %c\n",
           n, source, destination);

    hanoi3(n - 1, auxiliary, destination, source);
}

/* 4-peg Reve's Puzzle */
void reve(int n,
          char source,
          char destination,
          char aux1,
          char aux2,
          long long R[],
          int split[])
{
    if (n == 0)
        return;

    if (n == 1)
    {
        printf("Move disk 1: %c -> %c\n",
               source, destination);
        return;
    }

    int k = split[n];

    /* Move k smallest disks using 4 pegs */
    reve(k, source, aux1,
         destination, aux2, R, split);

    /* Move remaining n-k disks using 3 pegs */
    hanoi3(n - k, source,
           destination, aux2);

    /* Move k disks onto destination */
    reve(k, aux1, destination,
         source, aux2, R, split);
}

int main()
{
    int n;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid number of disks.\n");
        return 1;
    }

    long long *R =
        (long long *)malloc((n + 1) * sizeof(long long));

    int *split =
        (int *)malloc((n + 1) * sizeof(int));

    R[0] = 0;

    if (n >= 1)
        R[1] = 1;

    /* DP */
    for (int i = 2; i <= n; i++)
    {
        R[i] = LLONG_MAX;

        for (int k = 1; k < i; k++)
        {
            long long moves =
                2 * R[k]
                + power2(i - k)
                - 1;

            if (moves < R[i])
            {
                R[i] = moves;
                split[i] = k;
            }
        }
    }

    printf("\nMinimum number of moves = %lld\n",
           R[n]);

    printf("Optimal split for n = %d is k = %d\n",
           n, split[n]);

    if (n <= 10)
    {
        printf("\nSequence of moves:\n");

        reve(n, 'A', 'D',
             'B', 'C',
             R, split);
    }
    else
    {
        printf("\nMove sequence not printed for large n.\n");
    }

    free(R);
    free(split);

    return 0;
}