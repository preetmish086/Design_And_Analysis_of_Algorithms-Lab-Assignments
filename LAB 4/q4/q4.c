#include <stdio.h>

#define MAX 100

typedef struct {
    int time;
    int type;
} Event;

/* type = 1 for entry, -1 for exit */

void merge(Event arr[], int low, int mid, int high)
{
    Event temp[2 * MAX];

    int i = low;
    int j = mid + 1;
    int k = low;

    while (i <= mid && j <= high)
    {
        if (arr[i].time < arr[j].time)
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

    printf("Enter number of people: ");
    scanf("%d", &n);

    printf("Enter entry and exit times:\n");

    for (int i = 0; i < n; i++)
    {
        printf("Person %d: ", i + 1);

        scanf("%d %d",
              &events[2 * i].time,
              &events[2 * i + 1].time);

        events[2 * i].type = 1;
        events[2 * i + 1].type = -1;
    }

    /* Sort events according to time */
    mergeSort(events, 0, 2 * n - 1);

    int current = 0;
    int maximum = 0;
    int maxTime = 0;

    /* Process sorted events */
    for (int i = 0; i < 2 * n; i++)
    {
        if (events[i].type == 1)
        {
            current++;
        }
        else
        {
            current--;
        }

        if (current > maximum)
        {
            maximum = current;
            maxTime = events[i].time;
        }
    }

    printf("\nMaximum number of people present: %d\n", maximum);
    printf("Time when maximum people were present: %d\n", maxTime);

    return 0;
}