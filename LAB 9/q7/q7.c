#include <stdio.h>
#include <limits.h>

#define MAX 1000

int heap[MAX];
int size = 0;

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void insert(int x) {
    int i = size++;
    heap[i] = x;

    while (i > 0) {
        int p = (i - 1) / 2;

        if (heap[p] >= heap[i])
            break;

        swap(&heap[p], &heap[i]);
        i = p;
    }
}

int extractMax() {
    int result = heap[0];

    heap[0] = heap[--size];

    int i = 0;

    while (1) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int largest = i;

        if (l < size && heap[l] > heap[largest])
            largest = l;

        if (r < size && heap[r] > heap[largest])
            largest = r;

        if (largest == i)
            break;

        swap(&heap[i], &heap[largest]);
        i = largest;
    }

    return result;
}

int main() {
    int n;

    printf("Enter n: ");
    scanf("%d", &n);

    int minValue = INT_MAX;

    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);

        if (x % 2 == 1)
            x *= 2;

        if (x < minValue)
            minValue = x;

        insert(x);
    }

    int answer = INT_MAX;

    while (1) {

        int maxValue = extractMax();

        if (maxValue - minValue < answer)
            answer = maxValue - minValue;

        /* Cannot reduce an odd maximum */
        if (maxValue % 2 == 1)
            break;

        maxValue /= 2;

        if (maxValue < minValue)
            minValue = maxValue;

        insert(maxValue);
    }

    printf("Minimum deviation = %d\n", answer);

    return 0;
}