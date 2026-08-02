#include <stdio.h>
#include <math.h>

int main()
{
    FILE *fp=fopen("q4_toh.csv","w");

    if(fp==NULL)
    {
        printf("Cannot create file.\n");
        return 1;
    }

    fprintf(fp,"Disks,Moves\n");

    for(int n=1;n<=20;n++)
    {
        unsigned long long moves=(1ULL<<n)-1;

        fprintf(fp,"%d,%llu\n",n,moves);
    }

    fclose(fp);

    printf("CSV Generated : q4_toh.csv\n");

    return 0;
}