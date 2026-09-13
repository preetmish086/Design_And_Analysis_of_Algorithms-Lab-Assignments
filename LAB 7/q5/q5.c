#include <stdio.h>

void hitMovingTarget(int n)
{
    if (n == 2)
    {
        printf("Shooting sequence: 1 1\n");
        printf("Number of shots = 2\n");
        return;
    }

    printf("Shooting sequence: ");

    // Forward sweep
    for (int i = 2; i <= n - 1; i++)
        printf("%d ", i);

    // Backward sweep
    for (int i = n - 1; i >= 2; i--)
        printf("%d ", i);

    printf("\n");
    printf("Number of shots = %d\n", 2 * (n - 2));
}

int main()
{
    int n;

    printf("Enter number of hiding spots: ");
    scanf("%d", &n);

    if (n <= 1)
    {
        printf("Invalid input. n must be greater than 1.\n");
        return 1;
    }

    hitMovingTarget(n);

    return 0;
}