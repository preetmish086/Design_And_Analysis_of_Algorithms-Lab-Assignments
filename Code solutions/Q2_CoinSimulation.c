/*
------------------------------------------------------------
DAA Lab 01 - Question 2

Fair vs Biased Coin Simulation

Objective:
1. Simulate tossing a fair coin.
2. Simulate tossing a biased coin.
3. Estimate probability of getting HEAD.
4. Compare both experiments.
5. Generate CSV file for plotting.

Compile:
gcc q2.c -o q2

------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BIASED_PROBABILITY 0.70

/* Toss a fair coin */
int fairCoin()
{
    return rand() % 2;
}

/* Toss a biased coin */
int biasedCoin()
{
    double r = (double)rand() / RAND_MAX;

    if (r < BIASED_PROBABILITY)
        return 1;       // HEAD
    else
        return 0;       // TAIL
}

int main()
{
    int experiments[] = {10, 100, 1000, 10000, 100000};
    int totalExperiments = sizeof(experiments) / sizeof(experiments[0]);

    int i, j;

    srand((unsigned)time(NULL));

    FILE *fp = fopen("coin_simulation.csv", "w");

    if (fp == NULL)
    {
        printf("Unable to create CSV file.\n");
        return 1;
    }

    fprintf(fp, "Tosses,Fair_Probability,Biased_Probability\n");

    printf("\n=============================================================\n");
    printf("      FAIR COIN vs BIASED COIN SIMULATION\n");
    printf("=============================================================\n\n");

    printf("%-12s %-18s %-18s\n",
           "Tosses",
           "Fair P(HEAD)",
           "Biased P(HEAD)");

    printf("-------------------------------------------------------------\n");

    for (i = 0; i < totalExperiments; i++)
    {
        int tosses = experiments[i];

        int fairHeads = 0;
        int biasedHeads = 0;

        for (j = 0; j < tosses; j++)
        {
            if (fairCoin())
                fairHeads++;

            if (biasedCoin())
                biasedHeads++;
        }

        double fairProbability =
            (double)fairHeads / tosses;

        double biasedProbability =
            (double)biasedHeads / tosses;

        printf("%-12d %-18.6f %-18.6f\n",
               tosses,
               fairProbability,
               biasedProbability);

        fprintf(fp,
                "%d,%.6f,%.6f\n",
                tosses,
                fairProbability,
                biasedProbability);
    }

    fclose(fp);

    printf("\n-------------------------------------------------------------\n");
    printf("The fair coin probability approaches 0.5.\n");
    printf("The biased coin probability approaches %.2f.\n",
           BIASED_PROBABILITY);
    printf("-------------------------------------------------------------\n");

    printf("\nCSV file generated successfully: coin_simulation.csv\n");
    printf("Plot the CSV in Excel using:\n");
    printf("X-axis : Number of Tosses\n");
    printf("Y-axis : Estimated Probability of HEAD\n");

    return 0;
}