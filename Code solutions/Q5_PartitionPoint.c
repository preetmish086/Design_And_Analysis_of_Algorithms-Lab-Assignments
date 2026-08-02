/*
------------------------------------------------------------
DAA Lab - Question 5

Find the Partition Point

Problem:
An array consists of a sequence of 0's followed by a
sequence of 1's.

Find the first occurrence of 1 (partition point)
using Binary Search.

Time Complexity : O(log n)

Compile:
gcc Q5_PartitionPoint.c -o Q5_PartitionPoint
------------------------------------------------------------
*/

#include <stdio.h>

/*------------------------------------------------------------*/
/* Binary Search to Find Partition Point                      */
/*------------------------------------------------------------*/

int findPartitionPoint(int arr[], int n)
{
    int low = 0;
    int high = n - 1;
    int answer = -1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == 1)
        {
            answer = mid;
            high = mid - 1;      // Search left half
        }
        else
        {
            low = mid + 1;       // Search right half
        }
    }

    return answer;
}

/*------------------------------------------------------------*/
/* Main                                                       */
/*------------------------------------------------------------*/

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter the array (0's followed by 1's):\n");

    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int partition = findPartitionPoint(arr, n);

    printf("\n---------------------------------------\n");

    if(partition == -1)
    {
        printf("No partition point found.\n");
        printf("The array contains only 0's.\n");
    }
    else if(partition == 0)
    {
        printf("The array contains only 1's.\n");
        printf("Partition Point = 0\n");
    }
    else
    {
        printf("Partition Point Index = %d\n", partition);
        printf("First occurrence of 1 found at index %d\n", partition);
    }

    printf("---------------------------------------\n");

    return 0;
}