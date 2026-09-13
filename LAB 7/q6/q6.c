#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int year;
    int type;   // 0 = death, 1 = birth
} Event;

int compareEvents(const void *a, const void *b)
{
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    // Sort by year
    if (e1->year != e2->year)
        return e1->year - e2->year;

    // If same year, death before birth
    return e1->type - e2->type;
}

int main()
{
    int n;

    printf("Enter number of scientists: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid input.\n");
        return 1;
    }

    Event *events = (Event *)malloc(2 * n * sizeof(Event));

    if (events == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter birth year and death year for each scientist:\n");

    for (int i = 0; i < n; i++)
    {
        int birth, death;

        printf("Scientist %d: ", i + 1);
        scanf("%d %d", &birth, &death);

        events[2 * i].year = birth;
        events[2 * i].type = 1;      // birth

        events[2 * i + 1].year = death;
        events[2 * i + 1].type = 0;  // death
    }

    // Sort all events
    qsort(events, 2 * n, sizeof(Event), compareEvents);

    int alive = 0;
    int maxAlive = 0;
    int bestYear = events[0].year;

    for (int i = 0; i < 2 * n; i++)
    {
        if (events[i].type == 0)
            alive--;        // death
        else
            alive++;        // birth

        if (alive > maxAlive)
        {
            maxAlive = alive;
            bestYear = events[i].year;
        }
    }

    printf("\nBest time/year = %d\n", bestYear);
    printf("Maximum number of scientists alive = %d\n",
           maxAlive);

    free(events);

    return 0;
}