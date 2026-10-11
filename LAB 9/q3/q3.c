#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int distance;
    int fuel;
} Station;

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

/* ---------- Max Heap ---------- */

int heap[1000];
int heapSize = 0;

void heapInsert(int x) {
    int i = heapSize++;
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

    heap[0] = heap[--heapSize];

    int i = 0;

    while (1) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int largest = i;

        if (l < heapSize && heap[l] > heap[largest])
            largest = l;

        if (r < heapSize && heap[r] > heap[largest])
            largest = r;

        if (largest == i)
            break;

        swap(&heap[i], &heap[largest]);
        i = largest;
    }

    return result;
}

/* ---------- Sorting ---------- */

int compare(const void *a, const void *b) {
    Station *x = (Station *)a;
    Station *y = (Station *)b;

    return x->distance - y->distance;
}

int main() {
    int n, D, F;

    printf("Enter target distance: ");
    scanf("%d", &D);

    printf("Enter initial fuel: ");
    scanf("%d", &F);

    printf("Enter number of stations: ");
    scanf("%d", &n);

    Station s[n];

    for (int i = 0; i < n; i++) {
        printf("Station %d (distance fuel): ", i + 1);
        scanf("%d %d", &s[i].distance, &s[i].fuel);
    }

    qsort(s, n, sizeof(Station), compare);

    int fuel = F;
    int previous = 0;
    int stops = 0;

    for (int i = 0; i <= n; i++) {

        int currentDistance =
            (i == n) ? D : s[i].distance;

        int required = currentDistance - previous;

        while (fuel < required) {

            if (heapSize == 0) {
                printf("Impossible to reach target.\n");
                return 0;
            }

            fuel += extractMax();
            stops++;
        }

        fuel -= required;
        previous = currentDistance;

        if (i < n)
            heapInsert(s[i].fuel);
    }

    printf("Minimum refuelling stops = %d\n", stops);

    return 0;
}