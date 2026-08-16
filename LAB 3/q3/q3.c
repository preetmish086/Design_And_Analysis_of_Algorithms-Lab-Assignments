#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int min;
    int max;
    long long comparisons;
} Result;


/*
    Divide and Conquer algorithm to find the
    minimum and maximum elements of an array.

    Base Case 1:
        One element -> it is both minimum and maximum.
        Comparisons = 0

    Base Case 2:
        Two elements -> compare them once.
        Smaller = minimum
        Larger  = maximum

    Recursive Case:
        Divide the array into two halves.
        Find min and max of both halves recursively.
        Combine the results using:
            1 comparison for minimum
            1 comparison for maximum

    The total number of comparisons is bounded by:

        ceil(3n/2) - 2
*/


Result find_min_max(const int a[], int low, int high)
{
    Result left_result;
    Result right_result;
    Result result;

    /*
        Base Case 1:
        Only one element.
    */
    if (low == high)
    {
        result.min = a[low];
        result.max = a[low];
        result.comparisons = 0;

        return result;
    }


    /*
        Base Case 2:
        Exactly two elements.
    */
    if (high == low + 1)
    {
        result.comparisons = 1;

        if (a[low] < a[high])
        {
            result.min = a[low];
            result.max = a[high];
        }
        else
        {
            result.min = a[high];
            result.max = a[low];
        }

        return result;
    }


    /*
        Divide the array into two halves.
    */
    int mid = low + (high - low) / 2;


    /*
        Conquer:
        Find minimum and maximum in both halves.
    */
    left_result = find_min_max(a, low, mid);
    right_result = find_min_max(a, mid + 1, high);


    /*
        Combine:
        Compare the two minimums.
        This requires 1 comparison.
    */
    result.comparisons =
        left_result.comparisons +
        right_result.comparisons;

    result.comparisons++;

    if (left_result.min < right_result.min)
    {
        result.min = left_result.min;
    }
    else
    {
        result.min = right_result.min;
    }


    /*
        Compare the two maximums.
        This requires 1 comparison.
    */
    result.comparisons++;

    if (left_result.max > right_result.max)
    {
        result.max = left_result.max;
    }
    else
    {
        result.max = right_result.max;
    }


    return result;
}


int main(void)
{
    int n;

    printf("============================================\n");
    printf("   MINIMUM AND MAXIMUM USING DIVIDE & CONQUER\n");
    printf("============================================\n");


    /*
        Input size.
    */
    printf("\nEnter number of elements: ");
    scanf("%d", &n);


    /*
        Validate n.
    */
    if (n <= 0)
    {
        printf("Number of elements must be positive.\n");
        return 1;
    }


    /*
        Dynamically allocate the array.
    */
    int *a = malloc((size_t)n * sizeof(int));

    if (a == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }


    /*
        Input array elements.
    */
    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }


    /*
        Apply the divide-and-conquer algorithm.
    */
    Result result = find_min_max(a, 0, n - 1);


    /*
        Calculate the theoretical comparison bound:

            ceil(3n/2) - 2

        Since n is an integer, this can be calculated as:

            (3n + 1) / 2 - 2
    */
    long long theoretical_bound =
        (3LL * n + 1) / 2 - 2;


    /*
        Display results.
    */
    printf("\n============================================\n");
    printf("                  RESULT\n");
    printf("============================================\n");

    printf("\nMinimum = %d\n", result.min);
    printf("Maximum = %d\n", result.max);


    /*
        Comparison analysis.
    */
    printf("\n--------------------------------------------\n");
    printf("COMPARISON ANALYSIS\n");
    printf("--------------------------------------------\n");

    printf("Actual comparisons      : %lld\n",
           result.comparisons);

    printf("Theoretical upper bound : ceil(3n/2) - 2 = %lld\n",
           theoretical_bound);


    /*
        Validate the comparison bound.
    */
    printf("\n--------------------------------------------\n");
    printf("VALIDATION\n");
    printf("--------------------------------------------\n");

    if (result.comparisons <= theoretical_bound)
    {
        printf("Validation: Comparison count satisfies\n");
        printf("the theoretical 3n/2 bound.\n");
    }
    else
    {
        printf("Validation: Comparison count exceeds\n");
        printf("the theoretical bound.\n");
    }


    /*
        Complexity analysis.
    */
    printf("\n============================================\n");
    printf("                COMPLEXITY\n");
    printf("============================================\n");

    printf("Time Complexity       : O(n)\n");
    printf("Auxiliary Space       : O(log n)\n");


    /*
        Deallocate dynamically allocated memory.
    */
    free(a);

    return 0;
}