/*
------------------------------------------------------------
DAA Lab - Question 6

Duplicate Detection using Two Methods

Method 1 : Brute Force (O(n^2))
Method 2 : Merge Sort + Adjacent Comparison (O(n log n))

The program counts the number of comparisons
performed by each method.

CSV Generated:
duplicate_analysis.csv

Compile:
gcc Q6_DuplicateDetection.c -o Q6_DuplicateDetection
------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10000

long long bruteComparisons = 0;
long long mergeComparisons = 0;

/*------------------------------------------------------------*/
/* Generate Unique Array                                      */
/*------------------------------------------------------------*/

void generateUniqueArray(int arr[], int n)
{
    for(int i=0;i<n;i++)
        arr[i]=i+1;

    /* Shuffle the array */
    for(int i=n-1;i>0;i--)
    {
        int j=rand()%(i+1);

        int temp=arr[i];
        arr[i]=arr[j];
        arr[j]=temp;
    }
}

/*------------------------------------------------------------*/
/* Copy Array                                                 */
/*------------------------------------------------------------*/

void copyArray(int src[],int dest[],int n)
{
    for(int i=0;i<n;i++)
        dest[i]=src[i];
}

/*------------------------------------------------------------*/
/* Brute Force Duplicate Detection                            */
/*------------------------------------------------------------*/

int bruteForceDuplicate(int arr[],int n)
{
    bruteComparisons=0;

    for(int i=0;i<n-1;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            bruteComparisons++;

            if(arr[i]==arr[j])
                return 1;
        }
    }

    return 0;
}

/*------------------------------------------------------------*/
/* Merge Function                                             */
/*------------------------------------------------------------*/

void merge(int arr[],int left,int mid,int right)
{
    int n1=mid-left+1;
    int n2=right-mid;

    int L[n1];
    int R[n2];

    for(int i=0;i<n1;i++)
        L[i]=arr[left+i];

    for(int j=0;j<n2;j++)
        R[j]=arr[mid+1+j];

    int i=0,j=0,k=left;

    while(i<n1 && j<n2)
    {
        mergeComparisons++;

        if(L[i]<=R[j])
            arr[k++]=L[i++];
        else
            arr[k++]=R[j++];
    }

    while(i<n1)
        arr[k++]=L[i++];

    while(j<n2)
        arr[k++]=R[j++];
}

/*------------------------------------------------------------*/
/* Merge Sort                                                 */
/*------------------------------------------------------------*/

void mergeSort(int arr[],int left,int right)
{
    if(left<right)
    {
        int mid=(left+right)/2;

        mergeSort(arr,left,mid);
        mergeSort(arr,mid+1,right);

        merge(arr,left,mid,right);
    }
}

/*------------------------------------------------------------*/
/* Merge Sort Duplicate Detection                             */
/*------------------------------------------------------------*/

int mergeDuplicate(int arr[],int n)
{
    mergeComparisons=0;

    mergeSort(arr,0,n-1);

    for(int i=0;i<n-1;i++)
    {
        mergeComparisons++;

        if(arr[i]==arr[i+1])
            return 1;
    }

    return 0;
}

/*------------------------------------------------------------*/
/* Main                                                       */
/*------------------------------------------------------------*/

int main()
{
    srand(100);

    int original[MAX_SIZE];
    int arr1[MAX_SIZE];
    int arr2[MAX_SIZE];

    FILE *fp=fopen("duplicate_analysis.csv","w");

    if(fp==NULL)
    {
        printf("Unable to create CSV file.\n");
        return 1;
    }

    fprintf(fp,"ArraySize,BruteComparisons,MergeComparisons\n");

    printf("\n==============================================================\n");
    printf("      Duplicate Detection Performance Analysis\n");
    printf("==============================================================\n\n");

    printf("%-10s %-22s %-22s\n",
           "Size",
           "Brute Comparisons",
           "Merge Comparisons");

    printf("--------------------------------------------------------------\n");

    for(int n=1000;n<=10000;n+=1000)
    {
        generateUniqueArray(original,n);

        copyArray(original,arr1,n);
        copyArray(original,arr2,n);

        bruteForceDuplicate(arr1,n);
        mergeDuplicate(arr2,n);

        printf("%-10d %-22lld %-22lld\n",
               n,
               bruteComparisons,
               mergeComparisons);

        fprintf(fp,
                "%d,%lld,%lld\n",
                n,
                bruteComparisons,
                mergeComparisons);
    }

    fclose(fp);

    printf("\n--------------------------------------------------------------\n");
    printf("CSV File Generated : duplicate_analysis.csv\n");
    printf("X-axis : Array Size\n");
    printf("Y-axis : Number of Comparisons\n");
    printf("--------------------------------------------------------------\n");

    printf("\nConclusion:\n");
    printf("1. Brute Force performs O(n^2) comparisons.\n");
    printf("2. Merge Sort + Scan performs O(n log n) comparisons.\n");
    printf("3. For sufficiently large n, Merge Sort is much more efficient.\n");

    return 0;
}