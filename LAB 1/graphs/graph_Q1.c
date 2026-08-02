#include <stdio.h>
#include <math.h>

int main()
{
    FILE *fp = fopen("q1_growth.csv", "w");

    if(fp == NULL)
    {
        printf("Unable to create file.\n");
        return 1;
    }

    fprintf(fp,
    "n,1_over_n,log2_n,12sqrt_n,50sqrt_n,n_pow_051,2pow32_n,nlogn,n2_minus324,100n2_plus6n,2n3,nlogpower,3pow_n\n");

    for(double n = 100; n <= 10000; n += 100)
    {
        double f1  = log10(1.0/n);

        double f2  = log10(log2(n));

        double f3  = log10(12*sqrt(n));

        double f4  = log10(50*sqrt(n));

        double f5  = log10(pow(n,0.51));

        double f6  = log10(pow(2,32)*n);

        double f7  = log10(n*log2(n));

        double f8  = log10(n*n-324);

        double f9  = log10(100*n*n+6*n);

        double f10 = log10(2*n*n*n);

        /* log10(n^(log2 n)) */
        double f11 = log2(n)*log10(n);

        /* log10(3^n) */
        double f12 = n*log10(3);

        fprintf(fp,
        "%.0lf,%.6lf,%.6lf,%.6lf,%.6lf,%.6lf,%.6lf,%.6lf,%.6lf,%.6lf,%.6lf,%.6lf,%.6lf\n",
        n,f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12);
    }

    fclose(fp);

    printf("CSV Generated Successfully : q1_growth.csv\n");

    return 0;
}