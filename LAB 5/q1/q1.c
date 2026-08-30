#include <stdio.h>

int Partition(int A[], int low, int high);

int QuickSelect(int A[], int low, int high, int k)
{
    if (low == high)
        return A[low];

    int pivotindex = Partition(A, low, high);

    if (k == pivotindex)
        return A[k];

    else if (k < pivotindex)
        return QuickSelect(A, low, pivotindex - 1, k);

    else
        return QuickSelect(A, pivotindex + 1, high, k);
}

int Partition(int A[], int low, int high)
{
    int pivot = A[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (A[j] <= pivot)
        {
            i = i + 1;

            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }

    int temp = A[i + 1];
    A[i + 1] = A[high];
    A[high] = temp;

    return i + 1;
}

float FIND_MEDIAN(int A[], int N)
{
    if (N % 2 != 0)
    {
        int k = N / 2;

        return QuickSelect(A, 0, N - 1, k);
    }
    else
    {
        int k1 = N / 2 - 1;
        int k2 = N / 2;

        int x = QuickSelect(A, 0, N - 1, k1);
        int y = QuickSelect(A, 0, N - 1, k2);

        return (x + y) / 2.0;
    }
}

int main()
{
    int arr[100];
    int n;

    printf("Enter the value of n: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    float median = FIND_MEDIAN(arr, n);

    printf("The median is: %.2f\n", median);

    return 0;
}