#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

/*
    Allocate an n x n matrix dynamically.
*/
ll **allocate_matrix(int n)
{
    ll **M = malloc((size_t)n * sizeof(ll *));

    if (M == NULL)
        return NULL;

    for (int i = 0; i < n; i++)
    {
        M[i] = calloc((size_t)n, sizeof(ll));

        if (M[i] == NULL)
        {
            for (int j = 0; j < i; j++)
                free(M[j]);

            free(M);
            return NULL;
        }
    }

    return M;
}


/*
    Free an n x n dynamically allocated matrix.
*/
void free_matrix(ll **M, int n)
{
    if (M == NULL)
        return;

    for (int i = 0; i < n; i++)
        free(M[i]);

    free(M);
}


/*
    Add two n x n matrices:

        C = A + B
*/
void add_matrix(ll **A, ll **B, ll **C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}


/*
    Subtract two n x n matrices:

        C = A - B
*/
void subtract_matrix(ll **A, ll **B, ll **C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}


/*
    Strassen's Matrix Multiplication

    Multiplies two n x n matrices using the
    divide-and-conquer Strassen algorithm.

    The method reduces the usual 8 recursive
    matrix multiplications to 7.

    Base case:
        For a 1 x 1 matrix:

            C[0][0] = A[0][0] * B[0][0]

    Recursive case:
        Divide A and B into four submatrices:

            A11 A12        B11 B12
            A21 A22        B21 B22

        Compute seven products P1 ... P7.

        Then combine them to obtain C11, C12,
        C21 and C22.
*/
void strassen(ll **A, ll **B, ll **C, int n)
{
    /*
        Base case: 1 x 1 matrix.
    */
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    /*
        Divide A and B into four submatrices each.

            A = | A11 A12 |
                | A21 A22 |

            B = | B11 B12 |
                | B21 B22 |
    */

    ll **A11 = allocate_matrix(k);
    ll **A12 = allocate_matrix(k);
    ll **A21 = allocate_matrix(k);
    ll **A22 = allocate_matrix(k);

    ll **B11 = allocate_matrix(k);
    ll **B12 = allocate_matrix(k);
    ll **B21 = allocate_matrix(k);
    ll **B22 = allocate_matrix(k);


    /*
        Seven matrices for the seven recursive
        multiplications.
    */

    ll **M1 = allocate_matrix(k);
    ll **M2 = allocate_matrix(k);
    ll **M3 = allocate_matrix(k);
    ll **M4 = allocate_matrix(k);
    ll **M5 = allocate_matrix(k);
    ll **M6 = allocate_matrix(k);
    ll **M7 = allocate_matrix(k);


    /*
        Temporary matrices used to calculate
        sums and differences.
    */

    ll **T1 = allocate_matrix(k);
    ll **T2 = allocate_matrix(k);


    /*
        Check memory allocation.
    */
    if (!A11 || !A12 || !A21 || !A22 ||
        !B11 || !B12 || !B21 || !B22 ||
        !M1 || !M2 || !M3 || !M4 ||
        !M5 || !M6 || !M7 ||
        !T1 || !T2)
    {
        fprintf(stderr, "Memory allocation failed.\n");

        /*
            Free everything that may have been
            allocated before terminating.
        */
        free_matrix(A11, k);
        free_matrix(A12, k);
        free_matrix(A21, k);
        free_matrix(A22, k);

        free_matrix(B11, k);
        free_matrix(B12, k);
        free_matrix(B21, k);
        free_matrix(B22, k);

        free_matrix(M1, k);
        free_matrix(M2, k);
        free_matrix(M3, k);
        free_matrix(M4, k);
        free_matrix(M5, k);
        free_matrix(M6, k);
        free_matrix(M7, k);

        free_matrix(T1, k);
        free_matrix(T2, k);

        exit(EXIT_FAILURE);
    }


    /*
        Divide A and B into four k x k blocks.
    */

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }


    /*
        CLRS STRASSEN FORMULATION

        M1 = (A11 + A22)(B11 + B22)
    */

    add_matrix(A11, A22, T1, k);
    add_matrix(B11, B22, T2, k);
    strassen(T1, T2, M1, k);


    /*
        M2 = (A21 + A22)B11
    */

    add_matrix(A21, A22, T1, k);
    strassen(T1, B11, M2, k);


    /*
        M3 = A11(B12 - B22)
    */

    subtract_matrix(B12, B22, T2, k);
    strassen(A11, T2, M3, k);


    /*
        M4 = A22(B21 - B11)
    */

    subtract_matrix(B21, B11, T2, k);
    strassen(A22, T2, M4, k);


    /*
        M5 = (A11 + A12)B22
    */

    add_matrix(A11, A12, T1, k);
    strassen(T1, B22, M5, k);


    /*
        M6 = (A21 - A11)(B11 + B12)
    */

    subtract_matrix(A21, A11, T1, k);
    add_matrix(B11, B12, T2, k);
    strassen(T1, T2, M6, k);


    /*
        M7 = (A12 - A22)(B21 + B22)
    */

    subtract_matrix(A12, A22, T1, k);
    add_matrix(B21, B22, T2, k);
    strassen(T1, T2, M7, k);


    /*
        Combine the seven products.

            C11 = M1 + M4 - M5 + M7

            C12 = M3 + M5

            C21 = M2 + M4

            C22 = M1 - M2 + M3 + M6
    */

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            C[i][j] =
                M1[i][j]
                + M4[i][j]
                - M5[i][j]
                + M7[i][j];

            C[i][j + k] =
                M3[i][j]
                + M5[i][j];

            C[i + k][j] =
                M2[i][j]
                + M4[i][j];

            C[i + k][j + k] =
                M1[i][j]
                - M2[i][j]
                + M3[i][j]
                + M6[i][j];
        }
    }


    /*
        Free all dynamically allocated matrices.
    */

    free_matrix(A11, k);
    free_matrix(A12, k);
    free_matrix(A21, k);
    free_matrix(A22, k);

    free_matrix(B11, k);
    free_matrix(B12, k);
    free_matrix(B21, k);
    free_matrix(B22, k);

    free_matrix(M1, k);
    free_matrix(M2, k);
    free_matrix(M3, k);
    free_matrix(M4, k);
    free_matrix(M5, k);
    free_matrix(M6, k);
    free_matrix(M7, k);

    free_matrix(T1, k);
    free_matrix(T2, k);
}


/*
    Find the smallest power of 2 greater than
    or equal to n.

    Example:

        n = 3  -> 4
        n = 5  -> 8
        n = 8  -> 8
*/
int next_power_of_two(int n)
{
    int p = 1;

    while (p < n)
        p *= 2;

    return p;
}


int main(void)
{
    int n;


    printf("============================================\n");
    printf("       STRASSEN MATRIX MULTIPLICATION\n");
    printf("============================================\n");


    /*
        Input matrix size.
    */
    printf("\nEnter matrix size n: ");

    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Matrix size must be a positive integer.\n");
        return 1;
    }


    /*
        Strassen's basic recursive formulation
        works most conveniently when n is a power
        of 2.

        If n is not a power of 2, zero padding is
        used internally.
    */
    int p = next_power_of_two(n);


    /*
        Allocate padded matrices.
        calloc initializes all elements to zero,
        so the extra padded positions automatically
        contain zero.
    */

    ll **A = allocate_matrix(p);
    ll **B = allocate_matrix(p);
    ll **C = allocate_matrix(p);


    if (A == NULL || B == NULL || C == NULL)
    {
        printf("Memory allocation failed.\n");

        free_matrix(A, p);
        free_matrix(B, p);
        free_matrix(C, p);

        return 1;
    }


    /*
        Input matrix A.
    */
    printf("\nEnter matrix A (%d x %d):\n", n, n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%lld", &A[i][j]);
        }
    }


    /*
        Input matrix B.
    */
    printf("\nEnter matrix B (%d x %d):\n", n, n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%lld", &B[i][j]);
        }
    }


    /*
        Perform Strassen multiplication.
    */
    strassen(A, B, C, p);


    /*
        Display only the original n x n portion.
        Any extra rows/columns created by padding
        are ignored.
    */
    printf("\n============================================\n");
    printf("              PRODUCT MATRIX\n");
    printf("============================================\n\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%lld ", C[i][j]);
        }

        printf("\n");
    }


    /*
        Display complexity information.
    */
    printf("\n============================================\n");
    printf("                COMPLEXITY\n");
    printf("============================================\n");

    printf("Strassen recurrence : T(n) = 7T(n/2) + O(n^2)\n");
    printf("Time complexity     : O(n^log2(7))\n");
    printf("                    : O(n^2.807)\n");
    printf("Auxiliary space     : O(n^2)\n");


    if (p != n)
    {
        printf("\nInput size           : %d x %d\n", n, n);
        printf("Internal padded size : %d x %d\n", p, p);
    }


    /*
        Free all dynamically allocated memory.
    */
    free_matrix(A, p);
    free_matrix(B, p);
    free_matrix(C, p);


    return 0;
}