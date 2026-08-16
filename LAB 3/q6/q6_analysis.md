# Q6 - Selection Sort Using Loop Invariants

## 1. Problem Statement

Consider sorting `n` numbers stored in an array:

\[
A[1 \ldots n]
\]

The algorithm first finds the smallest element in `A[1...n]` and exchanges it with `A[1]`.

It then finds the smallest element in `A[2...n]` and exchanges it with `A[2]`.

This process continues until the first `n-1` elements have been processed.

This algorithm is known as **Selection Sort**.

The objective is to:

- Write the pseudocode for the algorithm.
- Identify the loop invariant.
- Prove correctness using initialization, maintenance, and termination.
- Explain why only the first `n-1` elements need to be processed.
- Determine the worst-case running time.
- Determine whether the best-case running time is better.
- Implement the algorithm in C and validate the analysis.

---

## 2. Algorithm

At iteration `i`, the algorithm finds the smallest element in:

\[
A[i \ldots n-1]
\]

and places it at position `i`.

The algorithm therefore gradually builds a sorted prefix.

Example:

```text
Initial:
5 3 8 1 4

After iteration 1:
1 3 8 5 4

After iteration 2:
1 3 8 5 4

After iteration 3:
1 3 4 5 8

After iteration 4:
1 3 4 5 8
```

## 3. Pseudocode

```text
SELECTION-SORT(A, n)

    for i <- 1 to n - 1

        min_index <- i

        for j <- i + 1 to n

            if A[j] < A[min_index]

                min_index <- j

        exchange A[i] with A[min_index]

    return A
```

## 4. Loop Invariant

The loop invariant of the outer loop is:

At the beginning of iteration `i`, the subarray `A[1...i-1]` contains the `i-1` smallest elements of the original array in sorted order.

In zero-based indexing used by the C program:

At the beginning of iteration `i`, `A[0...i-1]` contains the `i` smallest elements in sorted order.

## 5. Proof of Correctness

The correctness of the algorithm is established using the three properties of a loop invariant:

### 5.1 Initialization

Before the first iteration:

\[
i=0
\]

The sorted portion of the array is empty.

An empty array is trivially sorted and contains zero smallest elements.

Therefore, the loop invariant is true before the first iteration.

### 5.2 Maintenance

Assume the loop invariant is true at the beginning of iteration `i`.

Therefore:

```text
A[0...i-1]
```

already contains the `i` smallest elements in sorted order.

The algorithm searches:

```text
A[i...n-1]
```

and finds the smallest element in this remaining portion.

It exchanges that element with `A[i]`.

Therefore, `A[i]` becomes the smallest element among all remaining elements.

Consequently:

```text
A[0...i]
```

contains the `i+1` smallest elements in sorted order.

Thus, the loop invariant is maintained.

### 5.3 Termination

The outer loop terminates after processing position `n-2`.

At this point:

```text
A[0...n-2]
```

contains the first `n-1` smallest elements in sorted order.

Only one element remains at position `n-1`.

Since all other elements are already correctly positioned, the remaining element must also be in its correct position.

Therefore, the entire array is sorted.

Hence, the algorithm is correct.

## 6. Why Only n-1 Elements Need to be Processed

The algorithm does not need to process the last element.

After the first `n-1` positions have been correctly filled, there is exactly one element remaining.

That element must be the largest remaining element and therefore must already be in its correct position.

Searching a one-element subarray would perform no useful work.

Therefore, the algorithm only needs:

\[
n-1
\]

iterations.

## 7. Running Time Analysis

During iteration `i`, the algorithm compares the current minimum with every remaining element.

The number of comparisons is:

\[
(n-1)+(n-2)+(n-3)+\cdots+1
\]

Using the arithmetic series formula:

\[
T(n)=\frac{n(n-1)}{2}
\]

Therefore:

\[
T(n)=\Theta(n^2)
\]

## 8. Worst-Case Running Time

In the worst case, the algorithm still performs:

\[
\frac{n(n-1)}{2}
\]

element comparisons.

Therefore:

\[
\text{Worst-case time}=\Theta(n^2)
\]

## 9. Best-Case Running Time

The best case occurs when the array is already sorted.

However, Selection Sort still searches the entire remaining unsorted portion during every iteration.

Therefore, it still performs:

\[
\frac{n(n-1)}{2}
\]

comparisons.

Hence:

\[
\text{Best-case time}=\Theta(n^2)
\]

The best-case running time is therefore not asymptotically better than the worst-case running time.

## 10. Swaps

The number of swaps can depend on the initial arrangement of the array.

If the minimum element is already at the current position, no exchange is necessary.

The implementation therefore performs a swap only when:

```text
min_index != i
```

However, this does not change the asymptotic running time because the minimum-search loop still performs all required comparisons.

## 11. Complexity Summary

| Case | Time Complexity |
| --- | ---: |
| Best Case | $\Theta(n^2)$ |
| Average Case | $\Theta(n^2)$ |
| Worst Case | $\Theta(n^2)$ |
| Auxiliary Space | $\Theta(1)$ |

The algorithm sorts the array in-place and requires only a constant amount of additional memory.

## 12. Experimental Validation

The C implementation counts the number of element comparisons.

For an input of size `n`, the program calculates the theoretical comparison count:

\[
\frac{n(n-1)}{2}
\]

and compares it with the actual number of comparisons performed.

For example, for:

\[
n=5
\]

the number of comparisons is:

\[
\frac{5(5-1)}{2}=10
\]

Thus, even for an already sorted array of five elements, the algorithm performs ten comparisons.

This validates that the best-case running time remains:

\[
\Theta(n^2)
\]

## 13. Conclusion

The given sorting algorithm is Selection Sort.

Its loop invariant states that the already processed portion of the array contains the smallest elements in sorted order.

The invariant is:

- Initialized before the first iteration.
- Maintained by placing the smallest remaining element at the next position.
- Terminated when the first `n-1` positions are correctly sorted.

The algorithm performs:

\[
\frac{n(n-1)}{2}
\]

comparisons regardless of the initial ordering of the array.

Therefore:

\[
\text{Best Case}=\Theta(n^2)
\]

and:

\[
\text{Worst Case}=\Theta(n^2)
\]

Thus, the best-case running time is not asymptotically better than the worst-case running time.
