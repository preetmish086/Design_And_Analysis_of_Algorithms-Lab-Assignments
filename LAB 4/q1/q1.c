#include <stdio.h>
#define MAX 100

typedef struct pair{
    int val;
    char clr;
}pair;

void sort(pair arr[], int n)
{
    pair r[n], b[n], y[n];
    int j=0, k=0, l=0;
    for(int i=0; i<n; i++)
    {
        if(arr[i].clr=='r')
        {
            r[j].val=arr[i].val;
            r[j++].clr=arr[i].clr;
        }
        else if(arr[i].clr=='b')
        {
            b[k].val=arr[i].val;
            b[k++].clr=arr[i].clr;
        }
        else
        {
            y[l].val=arr[i].val;
            y[l++].clr=arr[i].clr;
        }
    }
    printf("Items sorted by colour such that numbers of identical colours are sorted:\n");
    for(int i=0; i<j; i++)
    {printf("%d",r[i].val);
    printf("%c\n",r[i].clr);}
    for(int i=0; i<k; i++)
    {printf("%d",b[i].val);
    printf("%c\n",b[i].clr);}
    for(int i=0; i<l; i++)
    {printf("%d",y[i].val);
    printf("%c\n",y[i].clr);}
}

int main(){
    pair arr[MAX];
    int n;
    printf("Enter number of pairs:");
    scanf("%d", &n);
    printf("Enter value colour pairs (r,b or y): ");
    for(int i=0; i<n; i++)
    {
        scanf("%d %c", &arr[i].val, &arr[i].clr);
    }
    sort(arr,n);
    return 0;
}