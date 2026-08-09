#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* ---------------- Classic 2-way merge sort ---------------- */

void merge2(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1, n2 = r - m;
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));
    memcpy(L, arr + l,     n1 * sizeof(int));
    memcpy(R, arr + m + 1, n2 * sizeof(int));

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L); free(R);
}

void mergeSort2(int arr[], int l, int r)
{
    if (l >= r) return;                 /* base case: 0 or 1 element */
    int m = l + (r - l) / 2;
    mergeSort2(arr, l, m);
    mergeSort2(arr, m + 1, r);
    merge2(arr, l, m, r);
}

/* ---------------- Modified 3-way merge sort ---------------- */

/* Merge three already-sorted runs arr[l..m1], arr[m1+1..m2], arr[m2+1..r] */
void merge3(int arr[], int l, int m1, int m2, int r)
{
    int n1 = m1 - l + 1, n2 = m2 - m1, n3 = r - m2;
    int *A = malloc(n1 * sizeof(int));
    int *B = malloc(n2 * sizeof(int));
    int *C = malloc(n3 * sizeof(int));
    memcpy(A, arr + l,      n1 * sizeof(int));
    memcpy(B, arr + m1 + 1, n2 * sizeof(int));
    memcpy(C, arr + m2 + 1, n3 * sizeof(int));

    int i = 0, j = 0, k = 0, idx = l;
    while (i < n1 && j < n2 && k < n3) {
        if (A[i] <= B[j] && A[i] <= C[k])      arr[idx++] = A[i++];
        else if (B[j] <= A[i] && B[j] <= C[k]) arr[idx++] = B[j++];
        else                                    arr[idx++] = C[k++];
    }
    /* at most one array remains fully; drain remaining pairs, then singles */
    while (i < n1 && j < n2) arr[idx++] = (A[i] <= B[j]) ? A[i++] : B[j++];
    while (j < n2 && k < n3) arr[idx++] = (B[j] <= C[k]) ? B[j++] : C[k++];
    while (i < n1 && k < n3) arr[idx++] = (A[i] <= C[k]) ? A[i++] : C[k++];
    while (i < n1) arr[idx++] = A[i++];
    while (j < n2) arr[idx++] = B[j++];
    while (k < n3) arr[idx++] = C[k++];

    free(A); free(B); free(C);
}

void mergeSort3(int arr[], int l, int r)
{
    if (l >= r) return;                 /* base case: 0 or 1 element */
    int len = r - l + 1;
    if (len < 3) {                      /* too small to split 3 ways */
        mergeSort2(arr, l, r);          /* fall back to normal merge  */
        return;
    }
    int third = len / 3;
    int m1 = l + third - 1;
    int m2 = l + 2 * third - 1;
    mergeSort3(arr, l, m1);
    mergeSort3(arr, m1 + 1, m2);
    mergeSort3(arr, m2 + 1, r);
    merge3(arr, l, m1, m2, r);
}

/* ---------------- helpers ---------------- */

int isSorted(int arr[], int n)
{
    for (int i = 1; i < n; i++)
        if (arr[i - 1] > arr[i]) return 0;
    return 1;
}

void fillRandom(int arr[], int n)
{
    for (int i = 0; i < n; i++) arr[i] = rand() % 1000000;
}

int main()
{
    srand(time(NULL));

#ifdef _WIN32
    system("if not exist Q2 mkdir Q2");
    system("if not exist Q2\\csv mkdir Q2\\csv");
    system("if not exist Q2\\gnuplot mkdir Q2\\gnuplot");
    system("if not exist Q2\\plots mkdir Q2\\plots");
#else
    system("mkdir -p Q2/csv");
    system("mkdir -p Q2/gnuplot");
    system("mkdir -p Q2/plots");
#endif

    /*
        CSV file
    */
    FILE* fp = fopen("Q2/csv/mergesort_data.csv", "w");

    if (fp == NULL)
    {
        printf("ERROR: Could not create CSV file.\n");
        return 1;
    }

    fprintf(fp,
            "n,mergesort_2way_ms,mergesort_3way_ms\n");

    int sizes[] = {
        1000,
        5000,
        10000,
        20000,
        40000,
        60000,
        80000,
        100000,
        150000,
        200000,
        300000
    };

    int numSizes =
        sizeof(sizes) / sizeof(sizes[0]);

    for (int s = 0; s < numSizes; s++)
    {
        int n = sizes[s];

        int *a1 = malloc(n * sizeof(int));
        int *a2 = malloc(n * sizeof(int));

        if (a1 == NULL || a2 == NULL)
        {
            printf("Memory allocation failed for n=%d\n", n);
            free(a1);
            free(a2);
            continue;
        }

        fillRandom(a1, n);

        /*
            Both algorithms receive exactly
            the same input.
        */
        memcpy(a2, a1, n * sizeof(int));


        /* Classic 2-way Merge Sort */

        clock_t t0 = clock();

        mergeSort2(a1, 0, n - 1);

        clock_t t1 = clock();

        double time2 =
            (double)(t1 - t0) *
            1000.0 / CLOCKS_PER_SEC;


        /* Modified 3-way Merge Sort */

        clock_t t2 = clock();

        mergeSort3(a2, 0, n - 1);

        clock_t t3 = clock();

        double time3 =
            (double)(t3 - t2) *
            1000.0 / CLOCKS_PER_SEC;


        if (!isSorted(a1, n) ||
            !isSorted(a2, n))
        {
            printf("ERROR: Sort failed for n=%d\n", n);
        }

        fprintf(fp,
                "%d,%.4f,%.4f\n",
                n,
                time2,
                time3);

        printf(
            "n=%7d   2-way = %8.3f ms   3-way = %8.3f ms\n",
            n,
            time2,
            time3
        );

        free(a1);
        free(a2);
    }

    fclose(fp);


    /*
        GNUPlot script
    */

    FILE* gp =
        fopen("Q2/gnuplot/mergesort_plot.gnu",
              "w");

    if (gp == NULL)
    {
        printf("ERROR: Could not create GNUPlot file.\n");
        return 1;
    }

    fprintf(gp,
        "set terminal pngcairo size 1200,700 enhanced font 'Arial,12'\n");

    fprintf(gp,
        "set output 'Q2/plots/mergesort_growth.png'\n");

    fprintf(gp,
        "set title 'Merge Sort vs Modified 3-way Merge Sort'\n");

    fprintf(gp,
        "set xlabel 'n (array size)'\n");

    fprintf(gp,
        "set ylabel 'Time (milliseconds)'\n");

    fprintf(gp,
        "set grid\n");

    fprintf(gp,
        "set key top left\n");

    fprintf(gp,
        "set datafile separator ','\n");

    fprintf(gp,
        "plot 'Q2/csv/mergesort_data.csv' "
        "using 1:2 with linespoints lw 2 pt 7 "
        "title 'Classic Merge Sort (2-way)', "
        "'Q2/csv/mergesort_data.csv' "
        "using 1:3 with linespoints lw 2 pt 5 "
        "title 'Modified Merge Sort (3-way)'\n"
    );

    fclose(gp);


    /*
        Run GNUPlot
    */

    int result =
        system("gnuplot \"Q2/gnuplot/mergesort_plot.gnu\"");

    if (result != 0)
    {
        printf("\nERROR: GNUPlot could not generate the graph.\n");
        printf("Check that GNUPlot is installed and available in PATH.\n");
    }
    else
    {
        printf("\nQ2 plot generated successfully!\n");
        printf("CSV  : Q2/csv/mergesort_data.csv\n");
        printf("Plot : Q2/plots/mergesort_growth.png\n");
    }

    return 0;
}