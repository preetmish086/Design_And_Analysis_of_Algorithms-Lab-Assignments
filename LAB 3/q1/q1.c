#include <stdio.h>

#define MAX 1000

/*----------------------------------------------------------
    Binary Search

    RAM Model:
    +, -, *, /, =, comparisons, memory accesses,
    function call and return are counted as 1 timestep.
----------------------------------------------------------*/
int binarySearch(int arr[], int n, int x, long long *steps)
{
    long long count = 0;

    /* Function call */
    count++;

    int low = 0;
    count++;                    // low=0

    int high = n - 1;
    count++;                    // high=n-1

    while (low <= high)
    {
        count++; // while condition check

        int mid = (low + high) / 2;
        count++;                // mid=(low+high)/2

        count++;                // comparison: arr[mid] == x
        if (arr[mid] == x)
        {
            count++;            // return
            *steps = count;
            return mid;
        }

        count++;                // comparison: arr[mid] < x
        if (arr[mid] < x)
        {
            low = mid + 1;
            count++;            // low=mid+1
        }

        else
        {
            high = mid - 1;
            count++;            // high=mid-1
        }
    }

    count++;                    // return
    *steps = count;

    return -1;
}


/*----------------------------------------------------------
    Ternary Search

    The array is divided into three parts using mid1 and mid2.
----------------------------------------------------------*/
int ternarySearch(int arr[], int n, int x, long long *steps)
{
    long long count = 0;

    /* Function call */
    count++;

    int low = 0;
    count++;                    // low=0
    
    int high = n - 1;
    count++;                    // high=n-1

    while (low <= high)
    {
        count++; //while condition check

        int mid1 = low + (high - low) / 3;
        count++;                // mid1 = low + (high - low) / 3

        int mid2 = high - (high - low) / 3;
        count++;                // mid2 = high - (high - low) / 3

        count++;                // comparison
        if (x == arr[mid1])
        {
            count++;            // return
            *steps = count;
            return mid1;
        }

        count++;                // comparison
        if (x == arr[mid2])
        {
            count++;            // return
            *steps = count;
            return mid2;
        }

        count++;                // comparison
        if (x < arr[mid1])
        {
            high = mid1 - 1;
            count++;            // high=mid1-1
        }
        else
        {
            count++;            // comparison
            if (x > arr[mid2])
            {
                low = mid2 + 1;
                count++;        // low=mid2+1
            }
            else
            {
                low = mid1 + 1;
                count++;        // mid1+1

                high = mid2 - 1;
                count++;        // high=mid2-1
            }
        }
    }

    count++;                    // return
    *steps = count;

    return -1;
}


// Display result for one user-provided input

void individualComparison()
{
    int n;
    int arr[MAX];
    int target;

    long long binarySteps;
    long long ternarySteps;

    printf("\n============================================\n");
    printf("       INDIVIDUAL SEARCH COMPARISON\n");
    printf("============================================\n");

    printf("Enter n (n <= %d): ", MAX);
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid value of n.\n");
        return;
    }

    printf("Enter %d sorted elements:\n", n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Enter the element to be searched: ");
    scanf("%d", &target);

    int binaryPosition =
        binarySearch(arr, n, target, &binarySteps);

    int ternaryPosition =
        ternarySearch(arr, n, target, &ternarySteps);

    printf("\n--------------------------------------------\n");
    printf("Binary Search\n");
    printf("--------------------------------------------\n");

    if (binaryPosition != -1)
    {
        printf("Element found at position: %d\n",
               binaryPosition);
    }
    else
    {
        printf("Element not found.\n");
    }

    printf("Total basic timesteps: %lld\n", binarySteps);

    printf("\n--------------------------------------------\n");
    printf("Ternary Search\n");
    printf("--------------------------------------------\n");

    if (ternaryPosition != -1)
    {
        printf("Element found at position: %d\n",
               ternaryPosition);
    }
    else
    {
        printf("Element not found.\n");
    }

    printf("Total basic timesteps: %lld\n", ternarySteps);

    printf("\n--------------------------------------------\n");
    printf("Comparison for this input\n");
    printf("--------------------------------------------\n");

    if (binarySteps < ternarySteps)
    {
        printf("Binary Search is better for this input.\n");
    }
    else if (ternarySteps < binarySteps)
    {
        printf("Ternary Search is better for this input.\n");
    }
    else
    {
        printf("Both searches require the same number of timesteps.\n");
    }
}


/*  Overall comparison

    We generate sorted arrays of different sizes.

    For each n, every element is searched once.
    Therefore, the comparison considers all target
    positions rather than depending on a single target.  */

void overallComparison()
{
    int arr[MAX];

    long long totalBinary = 0;
    long long totalTernary = 0;

    printf("\n============================================\n");
    printf("          OVERALL COMPARISON\n");
    printf("============================================\n");

    printf("\n%-10s %-20s %-20s\n", "n", "Binary Steps", "Ternary Steps");

    printf("--------------------------------------------------\n");

    /*
        Test increasing array sizes.

        Every element is searched, so the experiment
        considers different target positions.
    */
    for (int n = 10; n <= 1000; n *= 10)
    {
        long long binaryForN = 0;
        long long ternaryForN = 0;

        /* Generate a sorted array */
        for (int i = 0; i < n; i++)
        {
            arr[i] = i + 1;
        }

        /*
            Search every element in the array.
            This removes dependence on one particular
            target position.
        */
        for (int target = 1; target <= n; target++)
        {
            long long binarySteps;
            long long ternarySteps;

            binarySearch(arr, n, target, &binarySteps);
            ternarySearch(arr, n, target, &ternarySteps);

            binaryForN += binarySteps;
            ternaryForN += ternarySteps;
        }

        totalBinary += binaryForN;
        totalTernary += ternaryForN;

        printf("%-10d %-20lld %-20lld\n",
               n, binaryForN, ternaryForN);
    }

    printf("\n============================================\n");
    printf("FINAL RESULT\n");
    printf("============================================\n");

    printf("Total Binary Search timesteps : %lld\n",
           totalBinary);

    printf("Total Ternary Search timesteps: %lld\n",
           totalTernary);

    printf("\n");

    if (totalBinary < totalTernary)
    {
        printf("Conclusion: Binary Search requires fewer\n");
        printf("basic timesteps overall under the chosen\n");
        printf("RAM-model counting scheme.\n");
    }
    else if (totalTernary < totalBinary)
    {
        printf("Conclusion: Ternary Search requires fewer\n");
        printf("basic timesteps overall under the chosen\n");
        printf("RAM-model counting scheme.\n");
    }
    else
    {
        printf("Conclusion: Both require the same total\n");
        printf("number of basic timesteps.\n");
    }
}


/*----------------------------------------------------------
    Main
----------------------------------------------------------*/
int main()
{
    int choice;

    printf("============================================\n");
    printf("       BINARY vs TERNARY SEARCH\n");
    printf("============================================\n");

    printf("\n1. Individual comparison\n");
    printf("2. Overall comparison\n");
    printf("3. Run both\n");

    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            individualComparison();
            break;

        case 2:
            overallComparison();
            break;

        case 3:
            individualComparison();
            overallComparison();
            break;

        default:
            printf("Invalid choice.\n");
    }

    return 0;
}