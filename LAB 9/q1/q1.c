#include <stdio.h>

typedef struct {
    double value;
    double weight;
    double lambda;
    double density;
    int used;
} Item;

int main() {
    int n;
    double W;

    printf("Enter number of items: ");
    scanf("%d", &n);

    Item items[n];

    printf("Enter capacity: ");
    scanf("%lf", &W);

    for (int i = 0; i < n; i++) {
        printf("Item %d (value weight decay_rate): ", i + 1);
        scanf("%lf %lf %lf",
              &items[i].value,
              &items[i].weight,
              &items[i].lambda);

        items[i].density = items[i].value / items[i].weight;
        items[i].used = 0;
    }

    double totalValue = 0.0;
    int time = 0;

    while (W > 0) {

        int best = -1;
        double bestDensity = -1e18;

        /* Find item with maximum current effective density */
        for (int i = 0; i < n; i++) {

            if (!items[i].used) {

                double effectiveDensity =
                    items[i].density -
                    items[i].lambda * time;

                if (effectiveDensity > bestDensity) {
                    bestDensity = effectiveDensity;
                    best = i;
                }
            }
        }

        if (best == -1)
            break;

        double amount;

        if (items[best].weight <= W)
            amount = items[best].weight;
        else
            amount = W;

        totalValue += amount * bestDensity;

        printf("Time %d: Take %.2f weight from item %d "
               "(effective density = %.2f)\n",
               time, amount, best + 1, bestDensity);

        W -= amount;

        items[best].used = 1;

        time++;
    }

    printf("\nMaximum value = %.2f\n", totalValue);

    return 0;
}