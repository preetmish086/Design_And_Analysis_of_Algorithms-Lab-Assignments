/*
------------------------------------------------------------
DAA Lab - Question 4

Tower of Hanoi Simulation

Objectives:
1. Simulate Tower of Hanoi using recursion.
2. Display all moves.
3. Count total number of moves.
4. Generate CSV for plotting.

Compile:
gcc Q4_TowerOfHanoi.c -o Q4_TowerOfHanoi
------------------------------------------------------------
*/

#include <stdio.h>

long long moveCount;

/*------------------------------------------------------------*/
/* Recursive Tower of Hanoi                                   */
/*------------------------------------------------------------*/

void towerOfHanoi(int n, char source, char auxiliary, char destination)
{
    if (n == 1)
    {
        printf("Move Disk 1 : %c -> %c\n", source, destination);
        moveCount++;
        return;
    }

    towerOfHanoi(n - 1, source, destination, auxiliary);

    printf("Move Disk %d : %c -> %c\n", n, source, destination);
    moveCount++;

    towerOfHanoi(n - 1, auxiliary, source, destination);
}

/*------------------------------------------------------------*/
/* Main                                                       */
/*------------------------------------------------------------*/

int main()
{
    int n;

    FILE *fp = fopen("tower_of_hanoi.csv", "w");

    if (fp == NULL)
    {
        printf("Unable to create CSV file.\n");
        return 1;
    }

    fprintf(fp, "Disks,TotalMoves\n");

    printf("Enter number of disks for simulation: ");
    scanf("%d", &n);

    moveCount = 0;

    printf("\n====================================================\n");
    printf("          Tower of Hanoi Simulation\n");
    printf("====================================================\n\n");

    towerOfHanoi(n, 'A', 'B', 'C');

    printf("\n----------------------------------------------------\n");
    printf("Total Moves Required = %lld\n", moveCount);
    printf("----------------------------------------------------\n");

    /* Performance Analysis */

    printf("\nGenerating data for graph...\n\n");

    printf("%-10s %-15s\n", "Disks", "Moves");
    printf("-------------------------\n");

    for(int i=1;i<=15;i++)
    {
        long long moves=(1LL<<i)-1;

        printf("%-10d %-15lld\n", i, moves);

        fprintf(fp,"%d,%lld\n",i,moves);
    }

    fclose(fp);

    printf("\nCSV file generated: tower_of_hanoi.csv\n");
    printf("Plot in Excel:\n");
    printf("X-axis : Number of Disks\n");
    printf("Y-axis : Number of Moves\n");

    return 0;
}