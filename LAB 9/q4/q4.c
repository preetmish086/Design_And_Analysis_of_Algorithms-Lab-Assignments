#include <stdio.h>

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

        if (heap[p] <= heap[i])
            break;

        swap(&heap[p], &heap[i]);
        i = p;
    }
}

int extractMin() {
    int result = heap[0];

    heap[0] = heap[--size];

    int i = 0;

    while (1) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int smallest = i;

        if (l < size && heap[l] < heap[smallest])
            smallest = l;

        if (r < size && heap[r] < heap[smallest])
            smallest = r;

        if (smallest == i)
            break;

        swap(&heap[i], &heap[smallest]);
        i = smallest;
    }

    return result;
}

int main() {
    int n;

    printf("Enter number of sticks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        insert(x);
    }

    int totalCost = 0;

    while (size > 1) {
        int a = extractMin();
        int b = extractMin();

        int cost = a + b;

        totalCost += cost;

        insert(cost);

        printf("Connected %d and %d -> cost %d\n",
               a, b, cost);
    }

    printf("Minimum total cost = %d\n", totalCost);

    return 0;
}