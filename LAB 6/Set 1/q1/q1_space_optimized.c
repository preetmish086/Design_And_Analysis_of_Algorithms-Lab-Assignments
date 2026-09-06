#include <stdio.h>

int main(){
    int n;
    long long prev1=1, prev2=0, curr;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    if(n<0)
    {
        printf("Invalid input");
        return 0;
    }
    if(n==0)
    {
        printf("Fibonacci number at position %d is: %lld", n, prev2);
    }
    else if(n==1)
    {
        printf("Fibonacci number at position %d is: %lld", n, prev1);
    }
    else
    {
        for(int i=2; i<=n; i++)
        {
            curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }
        printf("Fibonacci number at position %d is: %lld", n, curr);
    }
}