/*
------------------------------------------------------------
DAA Lab Assignment
Question 1

Program:
Arrange the given functions in increasing order of
their asymptotic growth.

Method Used:
1. Evaluate all functions for different values of n.
2. Sort them using Merge Sort (Experimental Order).
3. Display the Correct Theoretical Order.
4. Compare both and print observations.

Compile:
gcc Q1_GrowthOrder.c -lm

------------------------------------------------------------
*/

#include <stdio.h>
#include <math.h>
#include <string.h>

#define NUM_FUNCTIONS 12
#define TESTS 7

/*------------------------------------------------------------*/
/* Structure                                                   */
/*------------------------------------------------------------*/

typedef struct
{
    char name[50];
    double value;
} Function;

/*------------------------------------------------------------*/
/* Test values of n                                            */
/*------------------------------------------------------------*/

double testN[TESTS] =
{
    1e2,
    1e3,
    1e4,
    1e5,
    1e6,
    1e7,
    1e8
};

/*------------------------------------------------------------*/
/* Merge Sort                                                  */
/*------------------------------------------------------------*/

void merge(Function arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Function L[n1];
    Function R[n2];

    int i, j, k;

    for(i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for(j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while(i < n1 && j < n2)
    {
        if(L[i].value <= R[j].value)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while(i < n1)
        arr[k++] = L[i++];

    while(j < n2)
        arr[k++] = R[j++];
}

void mergeSort(Function arr[], int left, int right)
{
    if(left < right)
    {
        int mid = (left + right) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

/*------------------------------------------------------------*/
/* Store all function values                                   */
/*------------------------------------------------------------*/

void loadFunctions(Function f[], double n)
{
    strcpy(f[0].name, "1/n");
    f[0].value = 1.0 / n;

    strcpy(f[1].name, "log2(n)");
    f[1].value = log2(n);

    strcpy(f[2].name, "12 sqrt(n)");
    f[2].value = 12 * sqrt(n);

    strcpy(f[3].name, "50 n^0.5");
    f[3].value = 50 * sqrt(n);

    strcpy(f[4].name, "n^0.51");
    f[4].value = pow(n, 0.51);

    strcpy(f[5].name, "n log2(n)");
    f[5].value = n * log2(n);

    strcpy(f[6].name, "n^log2(n)");
    f[6].value = pow(n, log2(n));

    strcpy(f[7].name, "2^32 n");
    f[7].value = pow(2,32) * n;

    strcpy(f[8].name, "100n^2 + 6n");
    f[8].value = 100 * n * n + 6 * n;

    strcpy(f[9].name, "n^2 - 324");
    f[9].value = n * n - 324;

    strcpy(f[10].name, "2n^3");
    f[10].value = 2 * n * n * n;

    strcpy(f[11].name, "3^n");
    if (n <= 600)
        f[11].value = pow(3, n);
    else
        f[11].value = INFINITY;
}

/*------------------------------------------------------------*/
/* Print Experimental Order                                    */
/*------------------------------------------------------------*/

void printExperimental(Function f[], double n)
{
    mergeSort(f, 0, NUM_FUNCTIONS - 1);

    printf("\n========================================================\n");
    printf("Experimental Ordering (n = %.0e)\n", n);
    printf("========================================================\n");

    printf("%-5s %-20s %-20s\n",
           "Rank",
           "Function",
           "Value");

    printf("--------------------------------------------------------\n");

    for(int i = 0; i < NUM_FUNCTIONS; i++)
    {
        if(isinf(f[i].value))
            printf("%-5d %-20s INF\n",
                    i + 1,
                    f[i].name);
        else
            printf("%-5d %-20s %.5e\n",
                    i + 1,
                    f[i].name,
                    f[i].value);
    }
}

/*------------------------------------------------------------*/
/* Print Correct Theoretical Order                            */
/*------------------------------------------------------------*/

void printTheoreticalOrder()
{
    printf("\n\n========================================================\n");
    printf("Correct Theoretical Asymptotic Order (n -> infinity)\n");
    printf("========================================================\n\n");

    printf("1.  1/n\n");
    printf("2.  log2(n)\n");
    printf("3.  12 sqrt(n)\n");
    printf("4.  50 n^0.5\n");
    printf("5.  n^0.51\n");
    printf("6.  2^32 n\n");
    printf("7.  n log2(n)\n");
    printf("8.  n^2 - 324\n");
    printf("9.  100n^2 + 6n\n");
    printf("10. 2n^3\n");
    printf("11. n^log2(n)\n");
    printf("12. 3^n\n");
}

/*------------------------------------------------------------*/
/* Observation                                                */
/*------------------------------------------------------------*/

void printObservation()
{
    printf("\n========================================================\n");
    printf("Observation\n");
    printf("========================================================\n\n");

    printf("1. The experimental ordering is obtained by evaluating\n");
    printf("   each function for finite values of n and sorting\n");
    printf("   them using Merge Sort.\n\n");

    printf("2. The theoretical ordering is based on asymptotic\n");
    printf("   growth (n -> infinity), where constant factors and\n");
    printf("   lower-order terms are ignored.\n\n");

    printf("3. Some functions may appear in a different order in\n");
    printf("   the experimental output because constants dominate\n");
    printf("   for practical values of n.\n\n");

    printf("   Examples:\n");
    printf("   . 50*sqrt(n) may appear larger than n^0.51\n");
    printf("     for all tested values of n.\n");
    printf("   . 2^32*n appears much larger than nlog2(n)\n");
    printf("     although nlog2(n) eventually grows faster.\n\n");

    printf("4. Therefore, the correct asymptotic order is the\n");
    printf("   theoretical order printed above.\n");
}

/*------------------------------------------------------------*/
/* Complexity                                                 */
/*------------------------------------------------------------*/

void printComplexity()
{
    printf("\n========================================================\n");
    printf("Complexity Analysis\n");
    printf("========================================================\n\n");

    printf("Merge Sort Time Complexity : O(m log m)\n");
    printf("where m = number of functions (%d).\n\n", NUM_FUNCTIONS);

    printf("Function Evaluation : O(m)\n");
    printf("Performed for %d different values of n.\n\n", TESTS);

    printf("Overall Time Complexity : O(TESTS × m log m)\n");
    printf("Overall Space Complexity: O(m)\n");
}

/*------------------------------------------------------------*/
/* Main                                                       */
/*------------------------------------------------------------*/

int main()
{
    Function f[NUM_FUNCTIONS];

    printf("========================================================\n");
    printf("      DAA LAB - ORDER OF GROWTH OF FUNCTIONS\n");
    printf("========================================================\n");

    for(int i = 0; i < TESTS; i++)
    {
        loadFunctions(f, testN[i]);
        printExperimental(f, testN[i]);
    }

    printTheoreticalOrder();

    printObservation();

    printComplexity();

    printf("\n========================================================\n");
    printf("Program Completed Successfully.\n");
    printf("========================================================\n");

    return 0;
}