#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void Heapify(int A[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && A[left] > A[largest])
        largest = left;

    if (right < n && A[right] > A[largest])
        largest = right;

    if (largest != i)
    {
        swap(&A[i], &A[largest]);

        Heapify(A, n, largest);
    }
}

void HeapSort(int A[], int n)
{
    /* Build Max Heap */
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        Heapify(A, n, i);
    }

    /* Extract elements one by one */
    for (int i = n - 1; i > 0; i--)
    {
        swap(&A[0], &A[i]);

        Heapify(A, i, 0);
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

    inputFile = fopen("heapsort_input.txt", "w");

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
    inputFile = fopen("heapsort_input.txt", "r");

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

    /* Apply Heap Sort */
    HeapSort(A, n);

    /* Store sorted elements in output file */
    outputFile = fopen("heapsort_output.txt", "w");

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

    printf("\n\nOriginal elements are stored in heapsort_input.txt");
    printf("\nSorted elements are stored in heapsort_output.txt\n");

    return 0;
}