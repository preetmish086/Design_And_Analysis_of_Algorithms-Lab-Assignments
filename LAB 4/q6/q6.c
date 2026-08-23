#include <stdio.h>

#define MAX 100

typedef struct {
    int point;
    int type;
} Event;

/*
    type = 1  -> start of interval
    type = -1 -> end of interval
*/

void merge(Event arr[], int low, int mid, int high)
{
    Event temp[2 * MAX];

    int i = low;
    int j = mid + 1;
    int k = low;

    while (i <= mid && j <= high)
    {
        /*
            If points are equal, start event
            should come before end event.
        */
        if (arr[i].point < arr[j].point ||
            (arr[i].point == arr[j].point &&
             arr[i].type > arr[j].type))
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

void mergeSort(Event arr[], int low, int high)
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
    int n;
    Event events[2 * MAX];

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    printf("Enter intervals (left right):\n");

    for (int i = 0; i < n; i++)
    {
        int left, right;

        scanf("%d %d", &left, &right);

        events[2 * i].point = left;
        events[2 * i].type = 1;

        events[2 * i + 1].point = right;
        events[2 * i + 1].type = -1;
    }

    /* Sort all events */
    mergeSort(events, 0, 2 * n - 1);

    int current = 0;
    int maximum = 0;
    int maxPoint = 0;

    /* Sweep through events */
    for (int i = 0; i < 2 * n; i++)
    {
        if (events[i].type == 1)
        {
            current++;

            if (current > maximum)
            {
                maximum = current;
                maxPoint = events[i].point;
            }
        }
        else
        {
            current--;
        }
    }

    printf("\nPoint with maximum overlap: %d\n", maxPoint);
    printf("Maximum number of intervals: %d\n", maximum);

    return 0;
}