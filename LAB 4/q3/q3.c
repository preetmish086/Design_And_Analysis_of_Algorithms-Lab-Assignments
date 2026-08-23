#include <stdio.h>
#define MAX 100

int found = 0;
int n, k, T;

int S[MAX];
int selected[MAX];

/* Merge two sorted parts */
void merge(int arr[], int low, int mid, int high)
{
    int temp[MAX];
    int i = low;
    int j = mid + 1;
    int p = low;

    while (i <= mid && j <= high)
    {
        if (arr[i] <= arr[j])
        {
            temp[p++] = arr[i++];
        }
        else
        {
            temp[p++] = arr[j++];
        }
    }

    while (i <= mid)
    {
        temp[p++] = arr[i++];
    }

    while (j <= high)
    {
        temp[p++] = arr[j++];
    }

    for (i = low; i <= high; i++)
    {
        arr[i] = temp[i];
    }
}

/* Merge sort */
void mergeSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;

        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);

        merge(arr, low, mid, high);
    }
}

/* Binary search */
int binarySearch(int arr[], int n, int key)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (arr[mid] == key)
        {
            return mid;
        }
        else if (arr[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1;
}

/*
   Select k-1 elements.
   When k-1 elements have been selected,
   search for the required final element.
*/
void findCombination(int start, int count, int sum)
{
    if (found)
    {
        return;
    }

    /* k-1 elements selected */
    if (count == k - 1)
    {
        int required = T - sum;
        int pos = binarySearch(S, n, required);

        if (pos != -1)
        {
            /*
               Make sure the required element is not
               one of the already selected elements.
            */
            int used = 0;

            for (int i = 0; i < count; i++)
            {
                if (selected[i] == pos)
                {
                    used = 1;
                    break;
                }
            }

            if (!used)
            {
                printf("\n%d numbers found: ", k);

                for (int i = 0; i < count; i++)
                {
                    printf("%d ", S[selected[i]]);
                }

                printf("%d", required);
                printf("\nSum = %d\n", T);

                found = 1;
            }
        }

        return;
    }

    /* Select the next element */
    for (int i = start; i < n; i++)
    {
        selected[count] = i;

        findCombination(i + 1,
                        count + 1,
                        sum + S[i]);

        if (found)
        {
            return;
        }
    }
}

int main()
{
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements of S:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &S[i]);
    }

    printf("Enter value of k: ");
    scanf("%d", &k);

    printf("Enter target T: ");
    scanf("%d", &T);

    if (k > n || k < 1)
    {
        printf("\nInvalid value of k.\n");
        return 0;
    }

    /* Sort S */
    mergeSort(S, 0, n - 1);

    printf("\nSorted S: ");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", S[i]);
    }

    findCombination(0, 0, 0);

    if (!found)
    {
        printf("\nNo %d elements add up to %d.\n", k, T);
    }

    return 0;
}