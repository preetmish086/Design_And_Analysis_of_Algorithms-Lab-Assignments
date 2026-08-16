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
    Free an n x n matrix.
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
    Special-pattern matrix multiplication.

    The matrices have the recursive form:

             | A1  A2 |
        A =  |        |
             | A2  A1 |

             | B1  B2 |
        B =  |        |
             | B2  B1 |

    Their product has the same form:

             | C1  C2 |
        C =  |        |
             | C2  C1 |

    We have:

        C1 = A1B1 + A2B2
        C2 = A1B2 + A2B1

    Instead of calculating four recursive products, use:

        P = (A1 + A2)(B1 + B2)
        Q = (A1 - A2)(B1 - B2)

    Then:

        C1 = (P + Q) / 2
        C2 = (P - Q) / 2

    Therefore, only TWO recursive multiplications
    are required.

    Recurrence:

        T(n) = 2T(n/2) + O(n^2)

    Hence:

        T(n) = O(n^2)
*/
void special_multiply(ll **A, ll **B, ll **C, int n)
{
    /*
        Base case: 1 x 1 matrices.
    */
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;


    /*
        Only two unique blocks exist in each matrix:

             | A1  A2 |
        A =  |        |
             | A2  A1 |

             | B1  B2 |
        B =  |        |
             | B2  B1 |
    */

    ll **A1 = allocate_matrix(k);
    ll **A2 = allocate_matrix(k);

    ll **B1 = allocate_matrix(k);
    ll **B2 = allocate_matrix(k);


    /*
        Temporary matrices for:

            P = (A1 + A2)(B1 + B2)
            Q = (A1 - A2)(B1 - B2)
    */

    ll **P = allocate_matrix(k);
    ll **Q = allocate_matrix(k);

    ll **T1 = allocate_matrix(k);
    ll **T2 = allocate_matrix(k);

    ll **T3 = allocate_matrix(k);
    ll **T4 = allocate_matrix(k);


    if (!A1 || !A2 || !B1 || !B2 ||
        !P || !Q || !T1 || !T2 || !T3 || !T4)
    {
        fprintf(stderr, "Memory allocation failed.\n");

        free_matrix(A1, k);
        free_matrix(A2, k);
        free_matrix(B1, k);
        free_matrix(B2, k);
        free_matrix(P, k);
        free_matrix(Q, k);
        free_matrix(T1, k);
        free_matrix(T2, k);
        free_matrix(T3, k);
        free_matrix(T4, k);

        exit(EXIT_FAILURE);
    }


    /*
        Extract A1, A2, B1 and B2.
    */

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            A1[i][j] = A[i][j];
            A2[i][j] = A[i][j + k];

            B1[i][j] = B[i][j];
            B2[i][j] = B[i][j + k];
        }
    }


    /*
        P = (A1 + A2)(B1 + B2)
    */

    add_matrix(A1, A2, T1, k);
    add_matrix(B1, B2, T2, k);

    special_multiply(T1, T2, P, k);


    /*
        Q = (A1 - A2)(B1 - B2)
    */

    subtract_matrix(A1, A2, T3, k);
    subtract_matrix(B1, B2, T4, k);

    special_multiply(T3, T4, Q, k);


    /*
        Recover C1 and C2:

            C1 = (P + Q) / 2
            C2 = (P - Q) / 2

        Then:

             | C1  C2 |
        C =  |        |
             | C2  C1 |
    */

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            ll C1 = (P[i][j] + Q[i][j]) / 2;
            ll C2 = (P[i][j] - Q[i][j]) / 2;

            C[i][j] = C1;
            C[i][j + k] = C2;
            C[i + k][j] = C2;
            C[i + k][j + k] = C1;
        }
    }


    /*
        Free all dynamically allocated memory.
    */

    free_matrix(A1, k);
    free_matrix(A2, k);
    free_matrix(B1, k);
    free_matrix(B2, k);

    free_matrix(P, k);
    free_matrix(Q, k);

    free_matrix(T1, k);
    free_matrix(T2, k);
    free_matrix(T3, k);
    free_matrix(T4, k);
}


int main(void)
{
    int k;


    printf("============================================\n");
    printf(" SPECIAL-PATTERN MATRIX MULTIPLICATION\n");
    printf("============================================\n");


    /*
        The question specifies:

            n = 2^k

        Therefore, the user enters k and
        the program calculates n automatically.
    */

    printf("\nEnter k: ");

    if (scanf("%d", &k) != 1 || k < 0)
    {
        printf("k must be a non-negative integer.\n");
        return 1;
    }


    int n = 1 << k;


    printf("Matrix size: n = 2^%d = %d\n", k, n);


    /*
        Allocate matrices.
    */

    ll **A = allocate_matrix(n);
    ll **B = allocate_matrix(n);
    ll **C = allocate_matrix(n);

    if (!A || !B || !C)
    {
        printf("Memory allocation failed.\n");

        free_matrix(A, n);
        free_matrix(B, n);
        free_matrix(C, n);

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
        Perform special-pattern multiplication.
    */

    special_multiply(A, B, C, n);


    /*
        Display result.
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
        Complexity.
    */

    printf("\n============================================\n");
    printf("                COMPLEXITY\n");
    printf("============================================\n");

    printf("Recurrence : T(n) = 2T(n/2) + O(n^2)\n");
    printf("Time       : O(n^2)\n");
    printf("Auxiliary  : O(n^2)\n");


    /*
        Free memory.
    */

    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(C, n);

    return 0;
}