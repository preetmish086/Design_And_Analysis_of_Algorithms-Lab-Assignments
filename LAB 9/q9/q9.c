#include <stdio.h>
#include <limits.h>

#define MAX 100
#define NODE_MAX (4 * MAX)

typedef struct {
    long long weight;
    int left;
    int right;
    int leaf_index;
    int is_original_leaf;
} Node;

static long long w[MAX];
static Node phase1[NODE_MAX];
static Node alphabetic_tree[NODE_MAX];
static int leaf_depth[MAX];
static int phase1_count;
static int tree_count;

static int new_phase1_node(long long weight, int left, int right, int leaf_index, int is_original_leaf) {
    int id = phase1_count++;
    phase1[id].weight = weight;
    phase1[id].left = left;
    phase1[id].right = right;
    phase1[id].leaf_index = leaf_index;
    phase1[id].is_original_leaf = is_original_leaf;
    return id;
}

static int new_tree_node(long long weight, int left, int right, int leaf_index) {
    int id = tree_count++;
    alphabetic_tree[id].weight = weight;
    alphabetic_tree[id].left = left;
    alphabetic_tree[id].right = right;
    alphabetic_tree[id].leaf_index = leaf_index;
    return id;
}

static void assign_leaf_depths(int node, int depth) {
    if (phase1[node].leaf_index >= 0) {
        leaf_depth[phase1[node].leaf_index] = depth;
        return;
    }
    assign_leaf_depths(phase1[node].left, depth + 1);
    assign_leaf_depths(phase1[node].right, depth + 1);
}

static void print_tree(int node, int depth, long long *cost) {
    if (alphabetic_tree[node].leaf_index >= 0) {
        int idx = alphabetic_tree[node].leaf_index;
        printf("Leaf %d (weight %lld), depth %d\n", idx + 1, w[idx], depth);
        *cost += w[idx] * depth;
        return;
    }
    printf("Internal node at depth %d\n", depth);
    print_tree(alphabetic_tree[node].left, depth + 1, cost);
    print_tree(alphabetic_tree[node].right, depth + 1, cost);
}

int main(void) {
    int n;
    int active[MAX];
    int active_count;

    printf("Enter number of leaves (1-%d): ", MAX);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter %d non-negative weights:\n", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%lld", &w[i]) != 1 || w[i] < 0) {
            printf("Invalid weight.\n");
            return 1;
        }
        active[i] = new_phase1_node(w[i], -1, -1, i, 1);
    }
    active_count = n;

    if (n == 1) {
        printf("\nMinimum weighted path cost = 0\n");
        printf("Leaf 1 (weight %lld), depth 0\n", w[0]);
        return 0;
    }

    /* --- Phase I: Combination --- */
    while (active_count > 1) {
        int leaf_prefix[MAX + 1] = {0};
        for (int i = 0; i < active_count; i++) {
            leaf_prefix[i + 1] = leaf_prefix[i] + phase1[active[i]].is_original_leaf;
        }

        int best_p = -1, best_q = -1;
        long long best_sum = LLONG_MAX;

        for (int p = 0; p < active_count; p++) {
            for (int q = p + 1; q < active_count; q++) {
                /* Hu-Tucker compatibility: adjacent OR no original leaves strictly between them */
                int is_adjacent = (q == p + 1);
                int leaves_between = leaf_prefix[q] - leaf_prefix[p + 1];

                if (!is_adjacent && leaves_between > 0)
                    continue;

                long long sum = phase1[active[p]].weight + phase1[active[q]].weight;
                if (sum < best_sum) {
                    best_sum = sum;
                    best_p = p;
                    best_q = q;
                }
            }
        }

        int parent = new_phase1_node(
            best_sum, active[best_p], active[best_q], -1, 0);
        active[best_p] = parent;

        for (int i = best_q; i < active_count - 1; i++) {
            active[i] = active[i + 1];
        }
        active_count--;
    }

    /* --- Phase II: Level Assignment --- */
    assign_leaf_depths(active[0], 0);

    /* --- Phase III: Alphabetic Tree Reconstruction --- */
    int stack_node[MAX];
    int stack_depth[MAX];
    int top = -1;

    for (int i = 0; i < n; i++) {
        int leaf = new_tree_node(w[i], -1, -1, i);
        top++;
        stack_node[top] = leaf;
        stack_depth[top] = leaf_depth[i];

        while (top >= 2 && stack_depth[top - 2] == stack_depth[top - 1]) {
            int right = stack_node[top - 1];
            int left = stack_node[top - 2];
            int p_depth = stack_depth[top - 1] - 1;
            long long p_weight =
                alphabetic_tree[left].weight + alphabetic_tree[right].weight;

            int parent = new_tree_node(p_weight, left, right, -1);

            stack_node[top - 2] = parent;
            stack_depth[top - 2] = p_depth;
            stack_node[top - 1] = stack_node[top];
            stack_depth[top - 1] = stack_depth[top];
            top--;
        }
    }

    while (top > 0) {
        int right = stack_node[top];
        int left = stack_node[top - 1];
        int p_depth = stack_depth[top] - 1;
        long long p_weight =
            alphabetic_tree[left].weight + alphabetic_tree[right].weight;

        int parent = new_tree_node(p_weight, left, right, -1);
        stack_node[top - 1] = parent;
        stack_depth[top - 1] = p_depth;
        top--;
    }

    long long calculated_cost = 0;
    printf("\nAlphabetic tree structure:\n");
    print_tree(stack_node[0], 0, &calculated_cost);
    printf("\nMinimum weighted path cost = %lld\n", calculated_cost);

    return 0;
}