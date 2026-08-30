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
            i++;

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

int main()
{
    int A[100];
    int n, k;

    printf("Enter the value of n: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }

    printf("Enter the value of k: ");
    scanf("%d", &k);

    if (k < 1 || k > n)
    {
        printf("Invalid value of k.\n");
        return 0;
    }

    int result = QuickSelect(A, 0, n - 1, k - 1);

    printf("The %dth smallest element is: %d\n", k, result);

    return 0;
}