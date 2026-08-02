/*
------------------------------------------------------------
DAA Lab - Question 3

Performance Analysis of Bubble Sort

Case 1 : Already Sorted Array
Case 2 : Random Array
Case 3 : Reverse Sorted Array

Algorithms Compared:
1. Bubble Sort with Early Termination
2. Normal Bubble Sort

The program counts comparisons and generates a CSV
for plotting in Excel.

Compile:
gcc Q3_BubbleSort.c -o Q3_BubbleSort
------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 1000

/*------------------------------------------------------------*/
/* Utility Functions                                           */
/*------------------------------------------------------------*/

void generateRandomArray(int arr[], int n)
{
    for(int i=0;i<n;i++)
        arr[i]=rand()%10000;
}

void generateSortedArray(int arr[], int n)
{
    for(int i=0;i<n;i++)
        arr[i]=i;
}

void generateReverseArray(int arr[], int n)
{
    for(int i=0;i<n;i++)
        arr[i]=n-i;
}

void copyArray(int source[], int destination[], int n)
{
    for(int i=0;i<n;i++)
        destination[i]=source[i];
}

/*------------------------------------------------------------*/
/* Bubble Sort with Early Termination                          */
/*------------------------------------------------------------*/

long long bubbleSortEarly(int arr[], int n)
{
    long long comparisons=0;

    for(int i=0;i<n-1;i++)
    {
        int swapped=0;

        for(int j=0;j<n-i-1;j++)
        {
            comparisons++;

            if(arr[j]>arr[j+1])
            {
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;

                swapped=1;
            }
        }

        if(swapped==0)
            break;
    }

    return comparisons;
}

/*------------------------------------------------------------*/
/* Normal Bubble Sort                                          */
/*------------------------------------------------------------*/

long long bubbleSortNormal(int arr[], int n)
{
    long long comparisons=0;

    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            comparisons++;

            if(arr[j]>arr[j+1])
            {
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }

    return comparisons;
}

/*------------------------------------------------------------*/
/* Run Experiment                                               */
/*------------------------------------------------------------*/

void performExperiment(
        FILE *fp,
        char type[],
        int original[],
        int n)
{
    int arr1[MAX_SIZE];
    int arr2[MAX_SIZE];

    copyArray(original,arr1,n);
    copyArray(original,arr2,n);

    long long early=bubbleSortEarly(arr1,n);
    long long normal=bubbleSortNormal(arr2,n);

    printf("%-10s %-8d %-18lld %-18lld\n",
           type,
           n,
           early,
           normal);

    fprintf(fp,
            "%s,%d,%lld,%lld\n",
            type,
            n,
            early,
            normal);
}

/*------------------------------------------------------------*/
/* Main                                                        */
/*------------------------------------------------------------*/

int main()
{
    srand((unsigned)time(NULL));

    FILE *fp=fopen("bubble_sort_analysis.csv","w");

    if(fp==NULL)
    {
        printf("Unable to create CSV file.\n");
        return 1;
    }

    fprintf(fp,
            "InputType,ArraySize,EarlyTermination,NormalBubble\n");

    int arr[MAX_SIZE];

    printf("\n=====================================================================\n");
    printf("              Bubble Sort Performance Analysis\n");
    printf("=====================================================================\n\n");

    printf("%-10s %-8s %-18s %-18s\n",
           "Input",
           "Size",
           "Early Bubble",
           "Normal Bubble");

    printf("---------------------------------------------------------------------\n");

    for(int n=100;n<=1000;n+=100)
    {
        generateSortedArray(arr,n);
        performExperiment(fp,"Sorted",arr,n);

        generateRandomArray(arr,n);
        performExperiment(fp,"Random",arr,n);

        generateReverseArray(arr,n);
        performExperiment(fp,"Reverse",arr,n);

        printf("---------------------------------------------------------------------\n");
    }

    fclose(fp);

    printf("\nCSV file generated successfully : bubble_sort_analysis.csv\n");

    printf("\nPlot Suggestions:\n");
    printf("X-axis : Array Size\n");
    printf("Y-axis : Number of Comparisons\n");
    printf("Create three graphs (Sorted, Random, Reverse)\n");

    return 0;
}