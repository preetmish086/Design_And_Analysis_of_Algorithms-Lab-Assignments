#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* Merge two sorted arrays a[0..na-1] and b[0..nb-1] into a fresh array */
int* mergeTwo(int* a, int na, int* b, int nb)
{
    int* out = malloc((na + nb) * sizeof(int));
    int i = 0, j = 0, k = 0;
    while (i < na && j < nb)
        out[k++] = (a[i] <= b[j]) ? a[i++] : b[j++];
    while (i < na) out[k++] = a[i++];
    while (j < nb) out[k++] = b[j++];
    return out;
}

/* ---------------- Method 1: sequential merging ---------------- */
/* arrays[i] each has length n. Returns a freshly malloc'd sorted array
 * of length k*n. */
int* mergeSequential(int** arrays, int k, int n)
{
    int* result = malloc(n * sizeof(int));
    memcpy(result, arrays[0], n * sizeof(int));
    int resultLen = n;

    for (int i = 1; i < k; i++) {
        int* merged = mergeTwo(result, resultLen, arrays[i], n);
        free(result);
        result = merged;
        resultLen += n;
    }
    return result;
}

/* ---------------- Method 2: pairwise (divide & conquer) merging ---------------- */
/* Merges arrays[lo..hi] (each of length n) into one sorted array. */
int* mergePairwise(int** arrays, int lo, int hi, int n, int* outLen)
{
    if (lo == hi) {
        int* copy = malloc(n * sizeof(int));
        memcpy(copy, arrays[lo], n * sizeof(int));
        *outLen = n;
        return copy;
    }
    int mid = (lo + hi) / 2;
    int leftLen, rightLen;
    int* left  = mergePairwise(arrays, lo, mid, n, &leftLen);
    int* right = mergePairwise(arrays, mid + 1, hi, n, &rightLen);
    int* merged = mergeTwo(left, leftLen, right, rightLen);
    *outLen = leftLen + rightLen;
    free(left); free(right);
    return merged;
}

/* ---------------- helpers ---------------- */

int isSorted(int* arr, int n)
{
    for (int i = 1; i < n; i++) if (arr[i - 1] > arr[i]) return 0;
    return 1;
}

/* build k sorted arrays, each of length n, with random values */
int** buildSortedArrays(int k, int n)
{
    int** arrays = malloc(k * sizeof(int*));
    for (int i = 0; i < k; i++) {
        arrays[i] = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) arrays[i][j] = rand() % 1000000;
        /* simple insertion sort is fine, n is small per array */
        for (int a = 1; a < n; a++) {
            int key = arrays[i][a], b = a - 1;
            while (b >= 0 && arrays[i][b] > key) { arrays[i][b+1] = arrays[i][b]; b--; }
            arrays[i][b + 1] = key;
        }
    }
    return arrays;
}

void freeArrays(int** arrays, int k)
{
    for (int i = 0; i < k; i++) free(arrays[i]);
    free(arrays);
}

int main()
{
    srand(time(NULL));

#ifdef _WIN32
    system("if not exist Q3 mkdir Q3");
    system("if not exist Q3\\csv mkdir Q3\\csv");
    system("if not exist Q3\\gnuplot mkdir Q3\\gnuplot");
    system("if not exist Q3\\plots mkdir Q3\\plots");
#else
    system("mkdir -p Q3/csv");
    system("mkdir -p Q3/gnuplot");
    system("mkdir -p Q3/plots");
#endif

    /*
        Size of each individual sorted array.
    */
    int n = 200;

    int kValues[] = {
        2, 4, 8, 16, 32,
        64, 128, 256, 512
    };

    int numK =
        sizeof(kValues) / sizeof(kValues[0]);


    /*
        CSV file
    */

    FILE* fp =
        fopen("Q3/csv/kway_data.csv", "w");

    if (fp == NULL)
    {
        printf("ERROR: Could not create CSV file.\n");
        return 1;
    }

    fprintf(fp,
        "k,method1_sequential_ms,method2_pairwise_ms\n");


    for (int idx = 0; idx < numK; idx++)
    {
        int k = kValues[idx];

        int** arrays =
            buildSortedArrays(k, n);

        if (arrays == NULL)
        {
            printf("Memory allocation failed for k=%d\n",
                   k);
            continue;
        }


        /*
            Method 1:
            Sequential merging
        */

        clock_t t0 = clock();

        int* r1 =
            mergeSequential(arrays, k, n);

        clock_t t1 = clock();

        double time1 =
            (double)(t1 - t0) *
            1000.0 / CLOCKS_PER_SEC;


        /*
            Method 2:
            Pairwise merging
        */

        int outLen;

        clock_t t2 = clock();

        int* r2 =
            mergePairwise(
                arrays,
                0,
                k - 1,
                n,
                &outLen
            );

        clock_t t3 = clock();

        double time2 =
            (double)(t3 - t2) *
            1000.0 / CLOCKS_PER_SEC;


        /*
            Validate results
        */

        if (!isSorted(r1, k * n) ||
            !isSorted(r2, outLen) ||
            outLen != k * n)
        {
            printf(
                "ERROR: Merge incorrect for k=%d!\n",
                k
            );
        }


        fprintf(fp,
                "%d,%.4f,%.4f\n",
                k,
                time1,
                time2);


        printf(
            "k=%4d (n=%d, total=%7d)   "
            "Method 1 = %8.3f ms   "
            "Method 2 = %8.3f ms\n",
            k,
            n,
            k * n,
            time1,
            time2
        );


        free(r1);
        free(r2);

        freeArrays(arrays, k);
    }

    fclose(fp);


    /*
        GNUPlot script
    */

    FILE* gp =
        fopen("Q3/gnuplot/kway_plot.gnu",
              "w");

    if (gp == NULL)
    {
        printf("ERROR: Could not create GNUPlot file.\n");
        return 1;
    }


    fprintf(gp,
        "set terminal pngcairo size 1200,700 enhanced font 'Arial,12'\n");

    fprintf(gp,
        "set output 'Q3/plots/kway_growth.png'\n");

    fprintf(gp,
        "set title 'Merging k Sorted Arrays "
        "(each of size n=%d)'\n",
        n);

    fprintf(gp,
        "set xlabel 'k (number of arrays)'\n");

    fprintf(gp,
        "set ylabel 'Time (milliseconds)'\n");

    fprintf(gp,
        "set grid\n");

    fprintf(gp,
        "set key top left\n");

    fprintf(gp,
        "set datafile separator ','\n");


    fprintf(gp,
        "plot 'Q3/csv/kway_data.csv' "
        "using 1:2 with linespoints lw 2 pt 7 "
        "title 'Method 1: Sequential O(nk^2)', "
        "'Q3/csv/kway_data.csv' "
        "using 1:3 with linespoints lw 2 pt 5 "
        "title 'Method 2: Pairwise O(nk log k)'\n"
    );

    fclose(gp);


    /*
        Run GNUPlot
    */

    int result =
        system("gnuplot \"Q3/gnuplot/kway_plot.gnu\"");

    if (result != 0)
    {
        printf("\nERROR: GNUPlot could not generate the graph.\n");
        printf("Check that GNUPlot is installed and available in PATH.\n");
    }
    else
    {
        printf("\nQ3 plot generated successfully!\n");
        printf("CSV  : Q3/csv/kway_data.csv\n");
        printf("Plot : Q3/plots/kway_growth.png\n");
    }


    return 0;
}