#include <stdio.h>

#define MAX 1000

long long reversalCost = 0;
long long reversalCount = 0;

/* Reverse p[l...r] */
void reverseRange(int p[], int l, int r)
{
    int i, j, temp;

    if (l >= r)
        return;

    reversalCost += (r - l + 1);
    reversalCount++;

    i = l;
    j = r;

    while (i < j)
    {
        temp = p[i];
        p[i] = p[j];
        p[j] = temp;

        i++;
        j--;
    }
}

/*
   Rotate:
       [l...mid] [mid+1...r]
   into:
       [mid+1...r] [l...mid]

   using three reversals.
*/
void rotateRange(int p[], int l, int mid, int r)
{
    if (l > mid || mid >= r)
        return;

    reverseRange(p, l, mid);
    reverseRange(p, mid + 1, r);
    reverseRange(p, l, r);
}

/*
   Stable partition:
       values <= valueMid | values > valueMid

   Returns the last position containing
   a value <= valueMid.
*/
int stablePartition(int p[], int left, int right, int valueMid)
{
    int mid;
    int boundaryLeft, boundaryRight;
    int highLeft, lowRight;

    if (left == right)
    {
        if (p[left] <= valueMid)
            return left;
        else
            return left - 1;
    }

    mid = (left + right) / 2;

    /* Partition both halves */
    boundaryLeft =
        stablePartition(p, left, mid, valueMid);

    boundaryRight =
        stablePartition(p, mid + 1, right, valueMid);

    /*
       Left half:
           [lowLeft][highLeft]

       Right half:
           [lowRight][highRight]

       Middle currently looks like:
           [highLeft][lowRight]

       Rotate it to:
           [lowRight][highLeft]
    */

    highLeft = mid - boundaryLeft;
    lowRight = boundaryRight - mid;

    if (highLeft > 0 && lowRight > 0)
    {
        /*
           Correct blocks:
           [boundaryLeft+1 ... mid]
           [mid+1 ... boundaryRight]
        */
        rotateRange(
            p,
            boundaryLeft + 1,
            mid,
            boundaryRight
        );
    }

    return boundaryLeft + lowRight;
}

/*
   Sort permutation using divide-and-conquer
   and reversal operations.

   Values in p[left...right] are assumed to be
   the consecutive integers valueLow...valueHigh.
*/
void sortByReversals(int p[], int left, int right,
                     int valueLow, int valueHigh)
{
    int valueMid;
    int boundary;

    if (left >= right || valueLow >= valueHigh)
        return;

    valueMid = (valueLow + valueHigh) / 2;

    /*
       Partition into:
           <= valueMid | > valueMid
    */
    boundary =
        stablePartition(p, left, right, valueMid);

    /* Recursively sort the two value ranges */
    if (boundary >= left)
    {
        sortByReversals(
            p,
            left,
            boundary,
            valueLow,
            valueMid
        );
    }

    if (boundary + 1 <= right)
    {
        sortByReversals(
            p,
            boundary + 1,
            right,
            valueMid + 1,
            valueHigh
        );
    }
}

/* Check whether permutation is sorted */
int isSorted(int p[], int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        if (p[i] != i + 1)
            return 0;
    }

    return 1;
}

int main()
{
    int p[MAX];
    int n, i;

    printf("Enter n: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid value of n.\n");
        return 1;
    }

    printf("Enter permutation of 1 to %d:\n", n);

    for (i = 0; i < n; i++)
        scanf("%d", &p[i]);

    printf("\nOriginal permutation:\n");

    for (i = 0; i < n; i++)
        printf("%d ", p[i]);

    printf("\n");

    sortByReversals(p, 0, n - 1, 1, n);

    printf("\nSorted permutation:\n");

    for (i = 0; i < n; i++)
        printf("%d ", p[i]);

    printf("\n");

    if (isSorted(p, n))
        printf("\nSorting successful.\n");
    else
        printf("\nSorting failed.\n");

    printf("Number of reversals = %lld\n", reversalCount);
    printf("Total reversal cost = %lld\n", reversalCost);

    return 0;
}