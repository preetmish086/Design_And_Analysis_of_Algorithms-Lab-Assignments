#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

int collatzNext(uint64_t n, uint64_t *next) {

    if (n == 0)
        return 0;

    if (n % 2 == 0) {
        *next = n / 2;
        return 1;
    }

    /* Check overflow for 3*n + 1 */
    if (n > (UINT64_MAX - 1) / 3)
        return 0;

    *next = 3 * n + 1;

    return 1;
}

uint64_t *generateTrajectory(uint64_t start,
                             size_t *length,
                             int *overflow) {

    size_t capacity = 16;
    size_t count = 0;

    uint64_t *trajectory =
        malloc(capacity * sizeof(uint64_t));

    if (trajectory == NULL)
        return NULL;

    uint64_t current = start;

    while (1) {

        if (count == capacity) {

            capacity *= 2;

            uint64_t *temp =
                realloc(trajectory,
                        capacity * sizeof(uint64_t));

            if (temp == NULL) {
                free(trajectory);
                return NULL;
            }

            trajectory = temp;
        }

        trajectory[count++] = current;

        if (current == 1)
            break;

        uint64_t next;

        if (!collatzNext(current, &next)) {
            *overflow = 1;
            break;
        }

        current = next;
    }

    *length = count;

    return trajectory;
}

void analyzeTrajectory(uint64_t start) {

    size_t length = 0;
    int overflow = 0;

    uint64_t *trajectory =
        generateTrajectory(start,
                           &length,
                           &overflow);

    if (trajectory == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("\nStarting value: %" PRIu64 "\n", start);

    printf("Trajectory:\n");

    for (size_t i = 0; i < length; i++) {
        printf("%" PRIu64, trajectory[i]);

        if (i + 1 < length)
            printf(" -> ");
    }

    printf("\n");

    if (overflow)
        printf("Overflow detected before trajectory reached 1.\n");
    else
        printf("Steps to reach 1: %zu\n", length - 1);

    free(trajectory);
}

int main() {

    uint64_t a, b;

    printf("Enter interval [a,b]: ");

    if (scanf("%" SCNu64 " %" SCNu64, &a, &b) != 2) {
        printf("Invalid input.\n");
        return 1;
    }

    if (a == 0 || a > b) {
        printf("Invalid interval.\n");
        return 1;
    }

    for (uint64_t n = a; n <= b; n++) {

        analyzeTrajectory(n);

        /* Avoid overflow when n == UINT64_MAX */
        if (n == UINT64_MAX)
            break;
    }

    return 0;
}