#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
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
            swap(&A[i], &A[j]);
        }
    }

    swap(&A[i + 1], &A[high]);

    return i + 1;
}

void QuickSort(int A[], int low, int high)
{
    if (low < high)
    {
        int pivotindex = Partition(A, low, high);

        QuickSort(A, low, pivotindex - 1);
        QuickSort(A, pivotindex + 1, high);
    }
}

int main()
{
    int A[1000];
    int n;

    FILE *inputFile;
    FILE *outputFile;

    printf("Enter the value of n: ");
    scanf("%d", &n);

    if (n < 1 || n > 1000)
    {
        printf("Invalid value of n.\n");
        return 0;
    }

    /* Generate random elements */
    srand(time(NULL));

    inputFile = fopen("quicksort_input.txt", "w");

    if (inputFile == NULL)
    {
        printf("Error opening input file.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        A[i] = rand() % 1000;
        fprintf(inputFile, "%d ", A[i]);
    }

    fclose(inputFile);

    /* Read elements from file */
    inputFile = fopen("quicksort_input.txt", "r");

    if (inputFile == NULL)
    {
        printf("Error opening input file.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        fscanf(inputFile, "%d", &A[i]);
    }

    fclose(inputFile);

    /* Apply Quick Sort */
    QuickSort(A, 0, n - 1);

    /* Store sorted elements in output file */
    outputFile = fopen("quicksort_output.txt", "w");

    if (outputFile == NULL)
    {
        printf("Error opening output file.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        fprintf(outputFile, "%d ", A[i]);
    }

    fclose(outputFile);

    /* Display sorted elements */
    printf("\nSorted elements:\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }

    printf("\n\nOriginal elements are stored in quicksort_input.txt");
    printf("\nSorted elements are stored in quicksort_output.txt\n");

    return 0;
}