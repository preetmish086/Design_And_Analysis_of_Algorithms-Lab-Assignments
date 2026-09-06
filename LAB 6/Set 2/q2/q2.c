#include <stdio.h>
#include <math.h>

#define MAX 20
#define EPS 1e-10
#define MAX_ITER 100

void readMatrix(double A[MAX][MAX], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%lf", &A[i][j]);
}

void printMatrix(double A[MAX][MAX], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf("%8.3lf ", A[i][j]);
        printf("\n");
    }
}

void addMatrix(double A[MAX][MAX], double B[MAX][MAX],
               double C[MAX][MAX], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void multiplyMatrix(double A[MAX][MAX], double B[MAX][MAX],
                    double C[MAX][MAX], int n)
{
    int i, j, k;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            C[i][j] = 0;

            for (k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    }
}

int isZeroMatrix(double A[MAX][MAX], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (fabs(A[i][j]) > EPS)
                return 0;

    return 1;
}

int isSymmetric(double A[MAX][MAX], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (fabs(A[i][j] - A[j][i]) > EPS)
                return 0;
        }
    }

    return 1;
}

double determinant(double A[MAX][MAX], int n)
{
    double B[MAX][MAX];
    double det = 1.0;
    int i, j, k, pivot;
    double factor, temp;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            B[i][j] = A[i][j];

    for (k = 0; k < n - 1; k++)
    {
        pivot = k;

        for (i = k + 1; i < n; i++)
        {
            if (fabs(B[i][k]) > fabs(B[pivot][k]))
                pivot = i;
        }

        if (fabs(B[pivot][k]) < EPS)
            return 0.0;

        if (pivot != k)
        {
            for (j = 0; j < n; j++)
            {
                temp = B[k][j];
                B[k][j] = B[pivot][j];
                B[pivot][j] = temp;
            }

            det = -det;
        }

        det *= B[k][k];

        for (i = k + 1; i < n; i++)
        {
            factor = B[i][k] / B[k][k];

            for (j = k + 1; j < n; j++)
                B[i][j] -= factor * B[k][j];
        }
    }

    det *= B[n - 1][n - 1];

    return det;
}

void transposeInPlace(double A[MAX][MAX], int n)
{
    int i, j;
    double temp;

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
    }
}

/*
   Jacobi eigenvalue algorithm.
   Intended for real symmetric matrices.
*/
void jacobiEigen(double A[MAX][MAX], int n,
                 double eigenvalues[MAX],
                 double eigenvectors[MAX][MAX])
{
    int i, j, p, q, iter;
    double maxOff, theta, c, s;
    double app, aqq, apq;
    double temp1, temp2;

    /* Eigenvector matrix initially = Identity */
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            eigenvectors[i][j] = (i == j) ? 1.0 : 0.0;
    }

    for (iter = 0; iter < MAX_ITER; iter++)
    {
        maxOff = 0.0;
        p = 0;
        q = 1;

        /* Find largest off-diagonal element */
        for (i = 0; i < n; i++)
        {
            for (j = i + 1; j < n; j++)
            {
                if (fabs(A[i][j]) > maxOff)
                {
                    maxOff = fabs(A[i][j]);
                    p = i;
                    q = j;
                }
            }
        }

        if (maxOff < EPS)
            break;

        theta = 0.5 * atan2(2.0 * A[p][q],
                             A[q][q] - A[p][p]);

        c = cos(theta);
        s = sin(theta);

        app = A[p][p];
        aqq = A[q][q];
        apq = A[p][q];

        A[p][p] = c * c * app
                - 2.0 * s * c * apq
                + s * s * aqq;

        A[q][q] = s * s * app
                + 2.0 * s * c * apq
                + c * c * aqq;

        A[p][q] = 0.0;
        A[q][p] = 0.0;

        for (i = 0; i < n; i++)
        {
            if (i != p && i != q)
            {
                temp1 = A[i][p];
                temp2 = A[i][q];

                A[i][p] = c * temp1 - s * temp2;
                A[p][i] = A[i][p];

                A[i][q] = s * temp1 + c * temp2;
                A[q][i] = A[i][q];
            }
        }

        /* Update eigenvectors */
        for (i = 0; i < n; i++)
        {
            temp1 = eigenvectors[i][p];
            temp2 = eigenvectors[i][q];

            eigenvectors[i][p] = c * temp1 - s * temp2;
            eigenvectors[i][q] = s * temp1 + c * temp2;
        }
    }

    for (i = 0; i < n; i++)
        eigenvalues[i] = A[i][i];
}

int main()
{
    double A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    double eigenvalues[MAX], eigenvectors[MAX][MAX];
    int n, i;

    printf("Enter order of square matrices: ");
    scanf("%d", &n);

    printf("\nEnter matrix A:\n");
    readMatrix(A, n);

    printf("\nEnter matrix B:\n");
    readMatrix(B, n);

    printf("\nA + B:\n");
    addMatrix(A, B, C, n);
    printMatrix(C, n);

    printf("\nA * B:\n");
    multiplyMatrix(A, B, C, n);
    printMatrix(C, n);

    printf("\nZero matrix test for A: ");
    printf("%s\n", isZeroMatrix(A, n) ? "YES" : "NO");

    printf("Symmetric matrix test for A: ");
    printf("%s\n", isSymmetric(A, n) ? "YES" : "NO");

    printf("\nDeterminant of A = %.4lf\n", determinant(A, n));

    printf("\nTranspose of A:\n");
    transposeInPlace(A, n);
    printMatrix(A, n);

    /*
       For eigenvalue/eigenvector calculation, A must be symmetric.
       Since A has been transposed above, its values are unchanged
       only if A is symmetric. In general, use the original symmetric
       matrix as input for this part.
    */

    if (isSymmetric(A, n))
    {
        double tempA[MAX][MAX];

        for (i = 0; i < n; i++)
        {
            int j;
            for (j = 0; j < n; j++)
                tempA[i][j] = A[i][j];
        }

        jacobiEigen(tempA, n, eigenvalues, eigenvectors);

        printf("\nEigenvalues:\n");
        for (i = 0; i < n; i++)
            printf("%.6lf ", eigenvalues[i]);

        printf("\n\nEigenvectors (columns):\n");
        printMatrix(eigenvectors, n);
    }
    else
    {
        printf("\nEigenvalue/eigenvector demonstration requires\n");
        printf("a real symmetric matrix for this Jacobi implementation.\n");
    }

    return 0;
}