#include <stdio.h>
#include <stdbool.h>
#define MAX 100

void merge(int arr[], int low, int mid, int high)
{
    int temp[MAX];
    int i=low, j=mid+1, k=low;
    while (i <= mid && j <= high)
    {
        if (arr[i] <= arr[j])
        {
            temp[k] = arr[i];
            i++;
        }
        else
        {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }
    while (i <= mid)
    {
        temp[k] = arr[i];
        i++;
        k++;
    }

    while (j <= high)
    {
        temp[k] = arr[j];
        j++;
        k++;
    }

    for (i = low; i <= high; i++)
    {
        arr[i] = temp[i];
    }
}

void mergesort(int arr[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;

        mergesort(arr, low, mid);
        mergesort(arr, mid + 1, high);

        merge(arr, low, mid, high);
    }
}

bool binarysearch(int arr[], int n, int target)
{
    int l=0, h=n-1, mid;
    while(l<=h)
    {
        mid=(l+h)/2;
        if(arr[mid]==target)
        return true;
        else if(arr[mid]<target)
        l=mid+1;
        else
        h=mid-1;
    }
    return false;
}

int main(){
    int s1[MAX], s2[MAX];
    int n, x;
    printf("Enter n: ");
    scanf("%d",&n);
    printf("Enter elements of 1st set:\n");
    for(int i=0; i<n; i++)
    scanf("%d",&s1[i]);
    printf("Enter elements of 2nd set:\n");
    for(int i=0; i<n; i++)
    scanf("%d",&s2[i]);
    printf("Enter the value of x: ");
    scanf("%d",&x);
    mergesort(s2,0,n-1);
    for(int i=0; i<n; i++)
    {
        if(binarysearch(s2, n, x-s1[i]))
        {
            printf("Pair found with sum %d\n",x);
            return 0;
        }
    }
    printf("No such pair found with sum %d\n",x);
    return 0;
}