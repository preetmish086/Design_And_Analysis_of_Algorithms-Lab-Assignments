#include <stdio.h>
#include <string.h>

#define MAXN 100
#define MAXLEN 1000

int overlap(char *a, char *b) {
    int la = strlen(a);
    int lb = strlen(b);

    int maxOverlap = 0;

    int limit = la < lb ? la : lb;

    for (int len = 1; len <= limit; len++) {

        if (strncmp(a + la - len, b, len) == 0)
            maxOverlap = len;
    }

    return maxOverlap;
}

void mergeStrings(char *a, char *b, char *result) {
    int ov = overlap(a, b);

    strcpy(result, a);
    strcat(result, b + ov);
}

int main() {
    int n;

    printf("Enter number of strings: ");
    scanf("%d", &n);

    char s[MAXN][MAXLEN];

    for (int i = 0; i < n; i++) {
        scanf("%s", s[i]);
    }

    while (n > 1) {

        int bestI = 0;
        int bestJ = 1;
        int bestOverlap = -1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {

                if (i == j)
                    continue;

                int ov = overlap(s[i], s[j]);

                if (ov > bestOverlap) {
                    bestOverlap = ov;
                    bestI = i;
                    bestJ = j;
                }
            }
        }

        char merged[MAXLEN * 2];

        mergeStrings(
            s[bestI],
            s[bestJ],
            merged
        );

        printf("Merge: %s + %s -> %s\n",
               s[bestI],
               s[bestJ],
               merged);

        strcpy(s[bestI], merged);

        /* Remove bestJ */
        for (int i = bestJ; i < n - 1; i++)
            strcpy(s[i], s[i + 1]);

        n--;
    }

    printf("\nGreedy superstring = %s\n", s[0]);

    return 0;
}