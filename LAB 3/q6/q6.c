#include <stdio.h>
#include <stdlib.h>

typedef long long ll;


/*
    Selection Sort

    At the beginning of each iteration i:

        A[0 ... i-1]

    contains the i smallest elements of the array
    in sorted order.

    The algorithm finds the minimum element in:

        A[i ... n-1]

    and places it at A[i].

    This maintains the loop invariant and eventually
    sorts the entire array.
*/


void selection_sort(int A[], int n, ll *comparisons, ll *swaps)
{
    *comparisons = 0;
    *swaps = 0;

    /*
        Only the first n-1 positions need to be processed.

        Once positions 0 through n-2 are correctly placed,
        the last element automatically occupies its correct position.
    */
    for (int i = 0; i < n - 1; i++)
    {
        int min_index = i;

        /*
            Find the minimum element in A[i ... n-1].
        */
        for (int j = i + 1; j < n; j++)
        {
            (*comparisons)++;

            if (A[j] < A[min_index])
            {
                min_index = j;
            }
        }

        /*
            Exchange A[i] with the minimum element.

            The swap is unnecessary if A[i] is already
            the minimum element.
        */
        if (min_index != i)
        {
            int temp = A[i];
            A[i] = A[min_index];
            A[min_index] = temp;

            (*swaps)++;
        }
    }
}


/*
    Display the array.
*/
void print_array(const int A[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }

    printf("\n");
}


int main(void)
{
    int n;

    printf("============================================\n");
    printf("              SELECTION SORT\n");
    printf("============================================\n");

    printf("\nEnter number of elements: ");

    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Number of elements must be positive.\n");
        return 1;
    }


    /*
        Dynamically allocate the array.
    */
    int *A = malloc((size_t)n * sizeof(int));

    if (A == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }


    /*
        Input array.
    */
    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }


    printf("\nOriginal array:\n");
    print_array(A, n);


    /*
        Perform selection sort.
    */
    ll comparisons;
    ll swaps;

    selection_sort(A, n, &comparisons, &swaps);


    /*
        Display sorted array.
    */
    printf("\nSorted array:\n");
    print_array(A, n);


    /*
        Display comparison analysis.
    */
    printf("\n============================================\n");
    printf("            PERFORMANCE ANALYSIS\n");
    printf("============================================\n");

    printf("\nElement comparisons : %lld\n", comparisons);
    printf("Swaps               : %lld\n", swaps);


    /*
        The number of comparisons is independent
        of the initial ordering of the array.

            (n-1) + (n-2) + ... + 1

        = n(n-1)/2
    */

    ll theoretical_comparisons =
        (ll)n * (n - 1) / 2;

    printf("Theoretical comparisons : %lld\n",
           theoretical_comparisons);


    /*
        Complexity.
    */
    printf("\n============================================\n");
    printf("                COMPLEXITY\n");
    printf("============================================\n");

    printf("Best-case time  : Theta(n^2)\n");
    printf("Worst-case time : Theta(n^2)\n");
    printf("Auxiliary space : Theta(1)\n");


    /*
        Free dynamically allocated memory.
    */
    free(A);

    return 0;
}