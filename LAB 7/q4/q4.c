#include <stdio.h>

unsigned long long securitySwitches(int n)
{
    unsigned long long prev2 = 1;  // M(1)
    unsigned long long prev1 = 2;  // M(2)
    unsigned long long current;

    if (n == 1)
        return 1;

    if (n == 2)
        return 2;

    for (int i = 3; i <= n; i++)
    {
        if (i % 2 == 1)
            current = 2 * prev1 + 1;
        else
            current = 2 * prev1;

        prev2 = prev1;
        prev1 = current;
    }

    return prev1;
}

int main()
{
    int n;

    printf("Enter number of switches: ");
    scanf("%d", &n);

    if (n <= 0 || n >= 63)
    {
        printf("Invalid input. Enter n between 1 and 62.\n");
        return 1;
    }

    printf("Minimum number of moves = %llu\n",
           securitySwitches(n));

    return 0;
}