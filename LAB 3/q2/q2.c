#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
    Each coin stores:
    - weight : used only by the balance-scale simulation
    - id     : original coin identity, used for validation
*/
typedef struct
{
    double weight;
    int id;
} Coin;


/*
    Simulates a balance scale.

    Return value:
       -1 -> left side is lighter
        0 -> both sides are equal
       +1 -> right side is lighter

    IMPORTANT:
    The divide-and-conquer algorithm does not see the
    actual weights. It only receives this result.
*/
int weigh(const Coin coins[],
          int left_start, int left_end,
          int right_start, int right_end)
{
    double left_sum = 0.0;
    double right_sum = 0.0;

    for (int i = left_start; i < left_end; i++)
        left_sum += coins[i].weight;

    for (int i = right_start; i < right_end; i++)
        right_sum += coins[i].weight;

    if (left_sum < right_sum)
        return -1;

    if (left_sum > right_sum)
        return 1;

    return 0;
}


/*
    Divide-and-conquer algorithm.

    Parameters:
        coins      -> shuffled coins
        left       -> beginning of candidate interval
        right      -> end of candidate interval
        reference  -> index of a known-good coin
        weighings  -> number of balance weighings

    The algorithm NEVER checks the absolute weight
    of a coin.

    It only uses the result of weigh().
*/
int find_defective(const Coin coins[],
                   int left,
                   int right,
                   int reference,
                   int *weighings)
{
    int count = right - left;

    /*
        Base case: two coins.

        Compare the two candidates directly.
    */
    if (count == 2)
    {
        (*weighings)++;

        int result = weigh(
            coins,
            left, left + 1,
            left + 1, right
        );

        if (result < 0)
            return left;

        if (result > 0)
            return left + 1;

        return -1;
    }


    /*
        Base case: one candidate.

        A known-good reference coin is available.
    */
    if (count == 1)
    {
        (*weighings)++;

        int result = weigh(
            coins,
            left, right,
            reference, reference + 1
        );

        if (result < 0)
            return left;

        return -1;
    }


    /*
        Divide the candidate set into two equal groups.
    */
    int half = count / 2;

    int mid = left + half;

    /*
        Compare:

            left group
                vs
            right group
    */
    (*weighings)++;

    int result = weigh(
        coins,
        left, mid,
        mid, mid + half
    );


    /*
        Case 1:
        Left group is lighter.

        Therefore the defective coin is in the
        left group.

        A coin from the right group is known good
        and becomes the reference.
    */
    if (result < 0)
    {
        int new_reference = mid;

        return find_defective(
            coins,
            left,
            mid,
            new_reference,
            weighings
        );
    }


    /*
        Case 2:
        Right group is lighter.

        Therefore the defective coin is in the
        right group.

        A coin from the left group is known good.
    */
    if (result > 0)
    {
        int new_reference = left;

        return find_defective(
            coins,
            mid,
            mid + half,
            new_reference,
            weighings
        );
    }


    /*
        Case 3:
        Both groups are equal.

        Since there is at most one defective coin,
        all coins in the two weighed groups are normal.

        If there is no remainder, there is no
        defective coin.
    */
    if (mid + half == right)
        return -1;


    /*
        Odd number of coins.

        The last coin is the unweighed remainder.
        It is the only possible defective coin.

        Compare it with a known-good coin from
        one of the balanced groups.
    */
    int remainder = mid + half;

    (*weighings)++;

    int remainder_result = weigh(
        coins,
        remainder, remainder + 1,
        left, left + 1
    );

    if (remainder_result < 0)
        return remainder;

    /*
        If the remainder balances with the known-good
        reference, then there is no defective coin.
    */
    return -1;
}


/*
    Fisher-Yates shuffle.

    The weights and IDs stay together because the
    complete Coin structure is shuffled.
*/
void shuffle(Coin coins[], int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);

        Coin temp = coins[i];
        coins[i] = coins[j];
        coins[j] = temp;
    }
}


/*
    Find the actual defective coin.

    This is ONLY for validation.
    The divide-and-conquer algorithm does not use this.
*/
int get_actual_defective_position(
    const Coin coins[],
    int n,
    double normal_weight
)
{
    for (int i = 0; i < n; i++)
    {
        if (coins[i].weight < normal_weight)
            return i;
    }

    return -1;
}


int main(void)
{
    int n;
    int make_defective;

    double normal_weight;
    double defective_weight;

    srand((unsigned)time(NULL));


    printf("============================================\n");
    printf("         SEARCH THE DEFECTIVE COIN\n");
    printf("============================================\n");


    /*
        n = 1 cannot be solved with only a balance
        scale and no known-good reference.
    */
    printf("\nEnter number of coins (n >= 2): ");
    scanf("%d", &n);

    if (n < 2)
    {
        printf("n must be at least 2.\n");
        return 1;
    }


    printf("Enter normal coin weight: ");
    scanf("%lf", &normal_weight);

    printf("Enter defective coin weight: ");
    scanf("%lf", &defective_weight);

    if (defective_weight >= normal_weight)
    {
        printf("Defective coin must be lighter than normal coin.\n");
        return 1;
    }


    printf("Create a defective coin? (1 = yes, 0 = no): ");
    scanf("%d", &make_defective);

    if (make_defective != 0 && make_defective != 1)
    {
        printf("Invalid choice.\n");
        return 1;
    }


    /*
        Generate n identical normal coins.
    */
    Coin *coins = malloc((size_t)n * sizeof(Coin));

    if (coins == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }


    for (int i = 0; i < n; i++)
    {
        coins[i].weight = normal_weight;
        coins[i].id = i + 1;
    }


    /*
        Manually make exactly one coin defective.
    */
    int actual_id = -1;

    if (make_defective)
    {
        int defective_index = rand() % n;

        coins[defective_index].weight = defective_weight;

        actual_id = coins[defective_index].id;
    }


    /*
        Randomly shuffle the pile.
    */
    shuffle(coins, n);


    /*
        Find actual defective position AFTER shuffling.
        This is only used for validation.
    */
    int actual_position =
        get_actual_defective_position(
            coins,
            n,
            normal_weight
        );


    printf("\n============================================\n");
    printf("             SHUFFLED COINS\n");
    printf("============================================\n");

    /*
        We intentionally do NOT print the weights.

        The algorithm should not be given absolute
        weight information.
    */
    for (int i = 0; i < n; i++)
    {
        printf("Position %d -> Coin ID %d\n",
               i + 1,
               coins[i].id);
    }


    /*
        Run the divide-and-conquer algorithm.
    */
    int weighings = 0;

    /*
        For n >= 2, no reference coin is initially
        required because the first operation compares
        two groups directly.

        -1 means "no reference currently available".
    */
    int found_position =
        find_defective(
            coins,
            0,
            n,
            -1,
            &weighings
        );


    printf("\n============================================\n");
    printf("                 RESULT\n");
    printf("============================================\n");


    if (found_position == -1)
    {
        printf("No defective coin found.\n");
    }
    else
    {
        printf(
            "Defective coin found at shuffled position: %d\n",
            found_position + 1
        );

        printf(
            "Coin ID: %d\n",
            coins[found_position].id
        );
    }


    printf("\nBalance weighings used: %d\n", weighings);


    /*
        Validation.
    */
    printf("\n============================================\n");
    printf("               VALIDATION\n");
    printf("============================================\n");


    if (!make_defective)
    {
        if (found_position == -1)
        {
            printf(
                "Validation: Correct - no defective coin exists.\n"
            );
        }
        else
        {
            printf(
                "Validation: Incorrect - no defective coin was generated.\n"
            );
        }
    }
    else
    {
        printf(
            "Actual defective coin ID: %d\n",
            actual_id
        );

        printf(
            "Actual defective shuffled position: %d\n",
            actual_position + 1
        );

        if (found_position == actual_position)
        {
            printf(
                "Validation: Correct - defective coin identified.\n"
            );
        }
        else
        {
            printf(
                "Validation: Incorrect - positions do not match.\n"
            );
        }
    }


    printf("\nTheoretical complexity: O(log2 n) balance weighings.\n");


    free(coins);

    return 0;
}