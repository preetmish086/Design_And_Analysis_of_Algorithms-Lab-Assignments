# Q1 — Binary Search vs Ternary Search

## Objective

Search for an element `x` in a sorted list using both binary search and ternary search, and validate the claim that binary search is better. The lab question asks for an implementation and validation rather than a graph.

## Algorithm

### Binary Search

1. Set `low = 0` and `high = n-1`.
2. Find `mid = low + (high-low)/2`.
3. If `A[mid] == x`, return the position.
4. If `x < A[mid]`, continue in the left half.
5. Otherwise continue in the right half.
6. Repeat until `low > high`.

### Ternary Search

1. Set `low = 0` and `high = n-1`.
2. Divide the interval into three parts using `mid1` and `mid2`.
3. Compare `x` with both middle elements.
4. Select the appropriate one-third interval.
5. Repeat until the interval becomes empty.

## Basic-timestep model

The program explicitly maintains a counter. To make the comparison reproducible, one basic timestep is counted for:

- a loop-condition check,
- a midpoint/partition calculation,
- a key comparison,
- a search-boundary update.

The same counting rules are used for both algorithms.

This is an operation-counting model, not a hardware clock measurement.

## Complexity

Binary search:

\[
T_b(n)=T_b(n/2)+O(1)
\]

Therefore:

\[
T_b(n)=O(\log_2 n)
\]

Ternary search:

\[
T_t(n)=T_t(n/3)+O(1)
\]

Therefore:

\[
T_t(n)=O(\log_3 n)
\]

Although `log3(n)` has a smaller mathematical value than `log2(n)`, each ternary-search iteration performs more work: two middle positions and up to two key comparisons, i.e, c' is larger thsan c because a ternary iteration requires more comparisons than a binary iteration. The timestep experiment validates that constant-factor difference under the particular RAM counting convention.

## Validation

### Input 1

```text
============================================
       INDIVIDUAL SEARCH COMPARISON
============================================
Enter n (n <= 1000): 10
Enter 10 sorted elements:
1 2 3 4 5 6 7 8 9 10
Enter the element to be searched: 6

--------------------------------------------
Binary Search
--------------------------------------------
Element found at position: 5
Total basic timesteps: 17

--------------------------------------------
Ternary Search
--------------------------------------------
Element found at position: 5
Total basic timesteps: 18

--------------------------------------------
Comparison for this input
--------------------------------------------
Binary Search is better for this input.
```

### Input 2

```text
============================================
       INDIVIDUAL SEARCH COMPARISON
============================================
Enter n (n <= 1000): 5
Enter 5 sorted elements:
10 20 30 40 50
Enter the element to be searched: 10

--------------------------------------------
Binary Search
--------------------------------------------
Element found at position: 0
Total basic timesteps: 12

--------------------------------------------
Ternary Search
--------------------------------------------
Element found at position: 0
Total basic timesteps: 15

--------------------------------------------
Comparison for this input
--------------------------------------------
Binary Search is better for this input.
```

### Input 3

```text
============================================
       INDIVIDUAL SEARCH COMPARISON
============================================
Enter n (n <= 1000): 20
Enter 20 sorted elements:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
Enter the element to be searched: 15

--------------------------------------------
Binary Search
--------------------------------------------
Element found at position: 14
Total basic timesteps: 12

--------------------------------------------
Ternary Search
--------------------------------------------
Element found at position: 14
Total basic timesteps: 23

--------------------------------------------
Comparison for this input
--------------------------------------------
Binary Search is better for this input.
```
