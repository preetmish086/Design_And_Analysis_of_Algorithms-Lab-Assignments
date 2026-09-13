#include <stdio.h>
int main(){
    int n;
    printf("Enter the height of the triangle: ");
    scanf("%d", &n);
    int N=n*(n+1)/2;
    int moves=N/3;
    printf("The minimum number of moves required to invert the triangle of height %d is %d", n, moves);
    return 0;
}