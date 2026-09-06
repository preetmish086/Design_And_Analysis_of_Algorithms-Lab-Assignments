#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void printArray(int a[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int findMax(int a[], int n) {
    int max = a[0];

    for (int i = 1; i < n; i++)
        if (a[i] > max)
            max = a[i];

    return max;
}

void findTwoLargest(int a[], int n, int *largest, int *second) {
    *largest = *second = -2147483648;

    for (int i = 0; i < n; i++) {
        if (a[i] > *largest) {
            *second = *largest;
            *largest = a[i];
        } else if (a[i] > *second && a[i] != *largest) {
            *second = a[i];
        }
    }
}

double findMean(int a[], int n) {
    double sum = 0;

    for (int i = 0; i < n; i++)
        sum += a[i];

    return sum / n;
}

int compare(const void *x, const void *y) {
    return (*(int *)x - *(int *)y);
}

double findMedian(int a[], int n) {
    qsort(a, n, sizeof(int), compare);

    if (n % 2)
        return a[n / 2];

    return (a[n / 2 - 1] + a[n / 2]) / 2.0;
}

double findStdDev(int a[], int n, double mean) {
    double sum = 0;

    for (int i = 0; i < n; i++)
        sum += (a[i] - mean) * (a[i] - mean);

    return sqrt(sum / n);
}

int findMode(int a[], int n) {
    int mode = a[0], maxCount = 0;

    for (int i = 0; i < n; i++) {
        int count = 0;

        for (int j = 0; j < n; j++)
            if (a[i] == a[j])
                count++;

        if (count > maxCount) {
            maxCount = count;
            mode = a[i];
        }
    }

    return mode;
}

int removeDuplicates(int a[], int n) {
    int newSize = 0;

    for (int i = 0; i < n; i++) {
        int duplicate = 0;

        for (int j = 0; j < newSize; j++) {
            if (a[i] == a[j]) {
                duplicate = 1;
                break;
            }
        }

        if (!duplicate)
            a[newSize++] = a[i];
    }

    return newSize;
}

void reverse(int a[], int n) {
    for (int i = 0, j = n - 1; i < j; i++, j--) {
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
}

void partition(int a[], int n, int pivot) {
    int pos = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] >= pivot) {
            int temp = a[i];
            a[i] = a[pos];
            a[pos] = temp;
            pos++;
        }
    }
}

int main() {
    int n, pivot;

    printf("Enter array size: ");
    scanf("%d", &n);

    int a[n], b[n];

    printf("Enter elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    int largest, second;
    double mean, median, sd;

    largest = findMax(a, n);
    findTwoLargest(a, n, &largest, &second);
    mean = findMean(a, n);
    median = findMedian(a, n);
    sd = findStdDev(a, n, mean);

    printf("\nMaximum = %d\n", largest);
    printf("First largest = %d\n", largest);
    printf("Second largest = %d\n", second);
    printf("Mean = %.2f\n", mean);
    printf("Median = %.2f\n", median);
    printf("Standard deviation = %.2f\n", sd);
    printf("Mode = %d\n", findMode(a, n));

    for (int i = 0; i < n; i++)
        b[i] = a[i];

    int newSize = removeDuplicates(b, n);
    printf("After removing duplicates: ");
    printArray(b, newSize);

    reverse(a, n);
    printf("Reversed array: ");
    printArray(a, n);

    printf("Enter pivot: ");
    scanf("%d", &pivot);

    partition(a, n, pivot);
    printf("After partitioning: ");
    printArray(a, n);

    return 0;
}