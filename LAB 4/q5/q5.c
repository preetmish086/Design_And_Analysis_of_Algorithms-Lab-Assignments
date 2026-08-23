#include <stdio.h>

#define MAX 100

typedef struct {
    int start;
    int end;
} Interval;

void merge(Interval arr[], int low, int mid, int high)
{
    Interval temp[MAX];

    int i = low;
    int j = mid + 1;
    int k = low;

    while (i <= mid && j <= high)
    {
        if (arr[i].start <= arr[j].start)
        {
            temp[k++] = arr[i++];
        }
        else
        {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid)
    {
        temp[k++] = arr[i++];
    }

    while (j <= high)
    {
        temp[k++] = arr[j++];
    }

    for (i = low; i <= high; i++)
    {
        arr[i] = temp[i];
    }
}

void mergeSort(Interval arr[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;

        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);

        merge(arr, low, mid, high);
    }
}

int main()
{
    Interval arr[MAX];
    Interval result[MAX];

    int n;
    int resultCount = 0;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    printf("Enter intervals (start end):\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &arr[i].start, &arr[i].end);
    }

    /* Sort intervals by starting point */
    mergeSort(arr, 0, n - 1);

    /* Merge overlapping intervals */

    int currentStart = arr[0].start;
    int currentEnd = arr[0].end;

    for (int i = 1; i < n; i++)
    {
        if (arr[i].start <= currentEnd)
        {
            /* Intervals overlap */
            if (arr[i].end > currentEnd)
            {
                currentEnd = arr[i].end;
            }
        }
        else
        {
            /* No overlap */
            result[resultCount].start = currentStart;
            result[resultCount].end = currentEnd;
            resultCount++;

            currentStart = arr[i].start;
            currentEnd = arr[i].end;
        }
    }

    /* Store the last interval */
    result[resultCount].start = currentStart;
    result[resultCount].end = currentEnd;
    resultCount++;

    /* Print result */
    printf("\nMerged intervals:\n");

    for (int i = 0; i < resultCount; i++)
    {
        printf("(%d, %d)", result[i].start, result[i].end);

        if (i != resultCount - 1)
        {
            printf(", ");
        }
    }

    printf("\n");

    return 0;
}