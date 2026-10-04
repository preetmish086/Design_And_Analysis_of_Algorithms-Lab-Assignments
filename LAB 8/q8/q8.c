#include <stdio.h>
#include <stdlib.h>
#include <float.h>

double min(double a, double b) {
    return (a < b) ? a : b;
}

double optimalBST(double p[], double q[], int n) {

    /*
       e[i][j] = minimum expected cost
       w[i][j] = sum of probabilities
    */

    double **e = malloc((n + 2) * sizeof(double *));
    double **w = malloc((n + 2) * sizeof(double *));

    for (int i = 0; i <= n + 1; i++) {
        e[i] = malloc((n + 1) * sizeof(double));
        w[i] = malloc((n + 1) * sizeof(double));
    }

    /* Empty subtrees */
    for (int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    /* Increasing subtree length */
    for (int length = 1; length <= n; length++) {

        for (int i = 1; i <= n - length + 1; i++) {

            int j = i + length - 1;

            e[i][j] = DBL_MAX;

            w[i][j] = w[i][j - 1]
                    + p[j]
                    + q[j];

            /* Try every key as root */
            for (int r = i; r <= j; r++) {

                double cost =
                    e[i][r - 1]
                    + e[r + 1][j]
                    + w[i][j];

                if (cost < e[i][j])
                    e[i][j] = cost;
            }
        }
    }

    double answer = e[1][n];

    for (int i = 0; i <= n + 1; i++) {
        free(e[i]);
        free(w[i]);
    }

    free(e);
    free(w);

    return answer;
}

int main() {
    int n;

    printf("Enter number of keys: ");
    scanf("%d", &n);

    double *p = malloc((n + 1) * sizeof(double));
    double *q = malloc((n + 1) * sizeof(double));

    printf("Enter successful probabilities p1...pn:\n");

    for (int i = 1; i <= n; i++)
        scanf("%lf", &p[i]);

    printf("Enter unsuccessful probabilities q0...qn:\n");

    for (int i = 0; i <= n; i++)
        scanf("%lf", &q[i]);

    printf("Minimum expected search cost = %.4f\n",
           optimalBST(p, q, n));

    free(p);
    free(q);

    return 0;
}