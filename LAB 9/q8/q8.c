#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Meeting;

int compareStart(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int main() {
    int n;

    printf("Enter number of meetings: ");
    scanf("%d", &n);

    int start[n], end[n];

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &start[i], &end[i]);
    }

    qsort(start, n, sizeof(int), compareStart);
    qsort(end, n, sizeof(int), compareStart);

    int i = 0;
    int j = 0;

    int rooms = 0;
    int answer = 0;

    while (i < n) {

        if (start[i] < end[j]) {
            rooms++;

            if (rooms > answer)
                answer = rooms;

            i++;
        }
        else {
            rooms--;
            j++;
        }
    }

    printf("Minimum rooms required = %d\n", answer);

    return 0;
}