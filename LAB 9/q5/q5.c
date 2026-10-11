#include <stdio.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n;

    printf("Enter number of children: ");
    scanf("%d", &n);

    int rating[n];
    int left[n];
    int right[n];

    printf("Enter ratings:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d", &rating[i]);
        left[i] = 1;
        right[i] = 1;
    }

    /* Left to right */
    for (int i = 1; i < n; i++) {
        if (rating[i] > rating[i - 1])
            left[i] = left[i - 1] + 1;
    }

    /* Right to left */
    for (int i = n - 2; i >= 0; i--) {
        if (rating[i] > rating[i + 1])
            right[i] = right[i + 1] + 1;
    }

    int total = 0;

    for (int i = 0; i < n; i++) {
        total += max(left[i], right[i]);
    }

    printf("Minimum candies = %d\n", total);

    return 0;
}