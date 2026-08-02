#include <stdio.h>

int main()
{
    FILE *fp = fopen("q3_bubble.csv","w");

    if(fp==NULL)
    {
        printf("Unable to create file.\n");
        return 1;
    }

    fprintf(fp,"ArraySize,WorstCase_BubbleSort,BestCase_EarlyTermination\n");

    for(int n=100;n<=5000;n+=100)
    {
        long long worst=(long long)n*(n-1)/2;

        long long best=n-1;

        fprintf(fp,"%d,%lld,%lld\n",
                n,
                worst,
                best);
    }

    fclose(fp);

    printf("CSV Generated Successfully : q3_bubble.csv\n");

    return 0;
}