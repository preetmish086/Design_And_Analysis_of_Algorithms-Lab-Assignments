#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_STRUCTURES 6
#define NUM_OPERATIONS 7

/*
    Q1: Dictionary Operations

    Data Structures:
    1. Unsorted Array
    2. Sorted Array
    3. Unsorted Singly Linked List
    4. Sorted Singly Linked List
    5. Unsorted Doubly Linked List
    6. Sorted Doubly Linked List

    Operations:
    1. Search
    2. Insert
    3. Delete
    4. Minimum
    5. Maximum
    6. Predecessor
    7. Successor

    Complexity codes:
    0 = O(1)
    1 = O(log n)
    2 = O(n)
*/

const char *structures[NUM_STRUCTURES] = {
    "Unsorted Array",
    "Sorted Array",
    "Unsorted SLL",
    "Sorted SLL",
    "Unsorted DLL",
    "Sorted DLL"
};

const char *operations[NUM_OPERATIONS] = {
    "Search",
    "Insert",
    "Delete",
    "Minimum",
    "Maximum",
    "Predecessor",
    "Successor"
};

/*
                    Search Insert Delete Minimum Maximum Pred Succ

Unsorted Array        n      1      1      n      n      n    n
Sorted Array          log    n      n      1      1      1    1
Unsorted SLL          n      1      n      n      n      n    n
Sorted SLL            n      n      n      1      n      n    1
Unsorted DLL          n      1      1      n      n      n    n
Sorted DLL            n      n      1      1      1      1    1
*/

int complexity[NUM_STRUCTURES][NUM_OPERATIONS] = {
    {2, 0, 0, 2, 2, 2, 2},
    {1, 2, 2, 0, 0, 0, 0},
    {2, 0, 2, 2, 2, 2, 2},
    {2, 2, 2, 0, 2, 2, 0},
    {2, 0, 0, 2, 2, 2, 2},
    {2, 2, 0, 0, 0, 0, 0}
};


/* Return theoretical growth value */
double growthValue(int type, int n)
{
    if (type == 0)
        return 1.0;                 /* O(1) */

    if (type == 1)
        return log2((double)n);     /* O(log n) */

    return (double)n;               /* O(n) */
}


/*
    Create required folders.

    Run this program from the "Lab 2" directory.

    It creates:

    Q1/
    Q1/csv/
    Q1/gnuplot/
    Q1/plots/
*/
void createFolders()
{
#ifdef _WIN32

    system("if not exist Q1 mkdir Q1");
    system("if not exist Q1\\csv mkdir Q1\\csv");
    system("if not exist Q1\\gnuplot mkdir Q1\\gnuplot");
    system("if not exist Q1\\plots mkdir Q1\\plots");

#else

    system("mkdir -p Q1/csv");
    system("mkdir -p Q1/gnuplot");
    system("mkdir -p Q1/plots");

#endif

    printf("Required Q1 folders created.\n\n");
}


/*
    Generate CSV files inside Q1/csv/
*/
void generateCSVFiles()
{
    int op, s, n;

    for (op = 0; op < NUM_OPERATIONS; op++)
    {
        char filename[200];

        sprintf(filename,
                "Q1/csv/q1_%s.csv",
                operations[op]);

        /* Replace spaces with underscores */
        for (int i = 0; filename[i] != '\0'; i++)
        {
            if (filename[i] == ' ')
                filename[i] = '_';
        }

        FILE *fp = fopen(filename, "w");

        if (fp == NULL)
        {
            printf("ERROR: Could not create %s\n", filename);
            continue;
        }

        fprintf(fp, "N");

        for (s = 0; s < NUM_STRUCTURES; s++)
        {
            fprintf(fp, ",\"%s\"", structures[s]);
        }

        fprintf(fp, "\n");

        /*
            Input sizes from 10 to 1000.
        */
        for (n = 10; n <= 1000; n += 10)
        {
            fprintf(fp, "%d", n);

            for (s = 0; s < NUM_STRUCTURES; s++)
            {
                double value =
                    growthValue(complexity[s][op], n);

                fprintf(fp, ",%.6f", value);
            }

            fprintf(fp, "\n");
        }

        fclose(fp);

        printf("Created: %s\n", filename);
    }
}


/*
    Generate GNUPlot files and PNG plots.
*/
void generatePlots()
{
    int op;

    for (op = 0; op < NUM_OPERATIONS; op++)
    {
        char csvFile[200];
        char plotFile[200];
        char gpFile[200];

        sprintf(csvFile,
                "Q1/csv/q1_%s.csv",
                operations[op]);

        sprintf(plotFile,
                "Q1/plots/q1_%s.png",
                operations[op]);

        sprintf(gpFile,
                "Q1/gnuplot/q1_%s.gnuplot",
                operations[op]);

        /* Replace spaces with underscores */
        for (int i = 0; csvFile[i] != '\0'; i++)
            if (csvFile[i] == ' ')
                csvFile[i] = '_';

        for (int i = 0; plotFile[i] != '\0'; i++)
            if (plotFile[i] == ' ')
                plotFile[i] = '_';

        for (int i = 0; gpFile[i] != '\0'; i++)
            if (gpFile[i] == ' ')
                gpFile[i] = '_';


        FILE *gp = fopen(gpFile, "w");

        if (gp == NULL)
        {
            printf("ERROR: Could not create %s\n", gpFile);
            continue;
        }

        /*
            PNG output.
        */
        fprintf(gp,
                "set terminal pngcairo size 1200,700 enhanced font 'Arial,12'\n");

        fprintf(gp,
                "set output '%s'\n",
                plotFile);

        fprintf(gp,
                "set title 'Q1 - %s: Comparison of Data Structures'\n",
                operations[op]);

        fprintf(gp,
                "set xlabel 'Input Size (n)'\n");

        fprintf(gp,
                "set ylabel 'Order of Growth'\n");

        fprintf(gp, "set grid\n");

        /*
            Log scale allows O(1), O(log n)
            and O(n) to be seen clearly.
        */
        fprintf(gp, "set logscale y\n");

        fprintf(gp,
                "set key outside right\n");

        fprintf(gp,
                "set datafile separator ','\n");

        fprintf(gp,
                "set xtics 100\n");


        fprintf(gp,
            "plot '%s' using 1:2 with lines lw 2 title 'Unsorted Array', \\\n",
            csvFile);

        fprintf(gp,
            "     '%s' using 1:3 with lines lw 2 title 'Sorted Array', \\\n",
            csvFile);

        fprintf(gp,
            "     '%s' using 1:4 with lines lw 2 title 'Unsorted SLL', \\\n",
            csvFile);

        fprintf(gp,
            "     '%s' using 1:5 with lines lw 2 title 'Sorted SLL', \\\n",
            csvFile);

        fprintf(gp,
            "     '%s' using 1:6 with lines lw 2 title 'Unsorted DLL', \\\n",
            csvFile);

        fprintf(gp,
            "     '%s' using 1:7 with lines lw 2 title 'Sorted DLL'\n",
            csvFile);

        fclose(gp);

        /*
            Execute GNUPlot.
        */
        char command[400];

#ifdef _WIN32
        sprintf(command,
                "gnuplot \"%s\"",
                gpFile);
#else
        sprintf(command,
                "gnuplot \"%s\"",
                gpFile);
#endif

        printf("\nGenerating plot: %s\n", plotFile);

        int result = system(command);

        if (result != 0)
        {
            printf("ERROR: GNUPlot failed for %s\n",
                   operations[op]);

            printf("Make sure GNUPlot is installed and added to PATH.\n");
        }
        else
        {
            printf("Successfully generated: %s\n",
                   plotFile);
        }
    }
}


int main()
{
    printf("===============================================\n");
    printf(" Q1 - Dictionary Operations Plot Generator\n");
    printf("===============================================\n\n");

    createFolders();

    printf("Generating CSV files...\n\n");

    generateCSVFiles();

    printf("\nGenerating GNUPlot files and PNG plots...\n");

    generatePlots();

    printf("\n===============================================\n");
    printf("Q1 plotting completed.\n");
    printf("===============================================\n");

    return 0;
}