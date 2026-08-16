# Q3 — Find Minimum and Maximum Using Divide and Conquer

## 1. Problem Statement

Using the divide-and-conquer approach, develop an algorithm to find the minimum and maximum elements in an array of `n` elements such that the number of comparisons is bounded by approximately:

\[
\frac{3n}{2}
\]

Implement the algorithm in C and validate the result by comparing the actual number of element comparisons with the theoretical bound.

The required comparison bound is:

\[
\boxed{\left\lceil\frac{3n}{2}\right\rceil - 2}
\]

---

## 2. Objective

The objectives of this program are to:

- Find the minimum element of an array.
- Find the maximum element of an array.
- Use a divide-and-conquer approach.
- Reduce the number of comparisons compared with finding the minimum and maximum independently.
- Count the number of element comparisons performed.
- Validate the comparison count against the theoretical bound.
- Analyze the time and auxiliary space complexity.

---

## 3. Straightforward Approach

A straightforward method is to find the minimum and maximum independently.

### Finding the Minimum

Finding the minimum among `n` elements requires:

\[
n-1
\]

comparisons.

### Finding the Maximum

Finding the maximum independently also requires:

\[
n-1
\]

comparisons.

Therefore, the total number of comparisons is:

\[
(n-1)+(n-1)
\]

\[
=2n-2
\]

Thus, the straightforward approach requires:

\[
\boxed{2n-2}
\]

comparisons.

The divide-and-conquer approach reduces this to approximately:

\[
\boxed{\frac{3n}{2}}
\]

comparisons.

---

## 4. Divide-and-Conquer Approach

The array is recursively divided into two smaller halves.

For each half, the algorithm finds:

- Minimum element
- Maximum element

The results from the two halves are then combined.

The divide-and-conquer process consists of three stages.

### 4.1 Divide

Divide the array into two halves using the midpoint:

\[
mid = \left\lfloor\frac{low+high}{2}\right\rfloor
\]

The two subarrays are:

```text
A[low ... mid]
A[mid+1 ... high]
```

### 4.2 Conquer

Recursively find the minimum and maximum of each half.

For the left half:

```text
left_min
left_max
```

For the right half:

```text
right_min
right_max
```

### 4.3 Combine

Combine the two results.

Only two comparisons are required:

1. Compare `left_min` and `right_min` to obtain the overall minimum.
2. Compare `left_max` and `right_max` to obtain the overall maximum.

Therefore, each combination step requires exactly:

\[
\boxed{2\text{ comparisons}}
\]

---

## 5. Base Cases

Two base cases are used.

### Case 1 — One Element

If the subarray contains one element:

```text
A[low]
```

then that element is both the minimum and maximum.

Therefore:

\[
T(1)=0
\]

comparisons.

### Case 2 — Two Elements

If the subarray contains two elements:

```text
A[low], A[high]
```

they are compared once.

If:

```text
A[low] < A[high]
```

then:

```text
minimum = A[low]
maximum = A[high]
```

Otherwise:

```text
minimum = A[high]
maximum = A[low]
```

Therefore:

\[
T(2)=1
\]

comparison.

---

## 6. Algorithm

The recursive algorithm can be summarized as follows:

1. If the subarray contains one element, return that element as both minimum and maximum.
2. If the subarray contains two elements, compare them once and determine the minimum and maximum.
3. Otherwise, divide the array into two halves.
4. Recursively find the minimum and maximum of the left half.
5. Recursively find the minimum and maximum of the right half.
6. Compare the two minimum values and select the smaller one.
7. Compare the two maximum values and select the larger one.
8. Return the overall minimum, maximum, and comparison count.

---

## 7. Pseudocode

```text
FIND-MIN-MAX(A, low, high)

    if low = high
        min ← A[low]
        max ← A[low]
        comparisons ← 0
        return min, max, comparisons

    if high = low + 1
        compare A[low] and A[high]

        if A[low] < A[high]
            min ← A[low]
            max ← A[high]
        else
            min ← A[high]
            max ← A[low]

        comparisons ← 1
        return min, max, comparisons

    mid ← floor((low + high) / 2)

    left_min, left_max, left_comparisons
        ← FIND-MIN-MAX(A, low, mid)

    right_min, right_max, right_comparisons
        ← FIND-MIN-MAX(A, mid + 1, high)

    compare left_min and right_min

    if left_min < right_min
        min ← left_min
    else
        min ← right_min

    compare left_max and right_max

    if left_max > right_max
        max ← left_max
    else
        max ← right_max

    comparisons ←
        left_comparisons
        + right_comparisons
        + 2

    return min, max, comparisons
```

---

## 8. Example

Consider the array:

```text
A = [7, 2, 9, 4, 1, 8, 3, 6]
```

The array is divided recursively:

```text
                 [7 2 9 4 1 8 3 6]
                         |
                    Divide
                   /      \
             [7 2 9 4]  [1 8 3 6]
                 |            |
              Divide       Divide
               /  \          /  \
            [7 2][9 4]    [1 8][3 6]
```

### First-level base cases

For `[7, 2]`:

```text
Comparison: 7 vs 2

Minimum = 2
Maximum = 7
Comparisons = 1
```

For `[9, 4]`:

```text
Comparison: 9 vs 4

Minimum = 4
Maximum = 9
Comparisons = 1
```

Combining these two results:

```text
Compare minimums: 2 vs 4  → 1 comparison
Compare maximums: 7 vs 9  → 1 comparison
```

Therefore:

```text
Minimum = 2
Maximum = 9
Comparisons = 1 + 1 + 2 = 4
```

Similarly, for `[1, 8, 3, 6]`:

```text
Minimum = 1
Maximum = 8
Comparisons = 4
```

Finally, combine the two halves:

```text
Compare minimums: 2 vs 1  → 1 comparison
Compare maximums: 9 vs 8  → 1 comparison
```

Final result:

```text
Minimum = 1
Maximum = 9
```

Total comparisons:

\[
4+4+2=10
\]

---

## 9. Comparison Count Analysis

The algorithm performs:

- `0` comparisons for one element.
- `1` comparison for two elements.
- `2` additional comparisons whenever two solved subarrays are combined.

The recurrence is:

\[
T(n)=T(\lfloor n/2\rfloor)+T(\lceil n/2\rceil)+2
\]

with:

\[
T(1)=0
\]

and:

\[
T(2)=1
\]

For the standard divide-and-conquer solution, the total number of comparisons is bounded by:

\[
\boxed{T(n)\leq\left\lceil\frac{3n}{2}\right\rceil-2}
\]

Thus, the required approximately `3n/2` comparison bound is satisfied.

---

## 10. Comparison Count for Even n

For an even number of elements, the exact number of comparisons is:

\[
T(n)=\frac{3n}{2}-2
\]

For example, for:

\[
n=8
\]

the comparison count is:

\[
T(8)=\frac{3(8)}{2}-2
\]

\[
=12-2
\]

\[
=10
\]

The program therefore produces:

```text
Actual comparisons      : 10
Theoretical upper bound : 10
```

---

## 11. Comparison Count for Odd n

For an odd number of elements, the number of comparisons is:

\[
T(n)=\frac{3(n-1)}{2}
\]

This is equivalent to:

\[
T(n)=\left\lceil\frac{3n}{2}\right\rceil-2
\]

For example, for:

\[
n=7
\]

\[
T(7)=\frac{3(7-1)}{2}
\]

\[
=\frac{18}{2}
\]

\[
=9
\]

The theoretical bound is:

\[
\left\lceil\frac{21}{2}\right\rceil-2
\]

\[
=11-2
\]

\[
=9
\]

Therefore, the bound is satisfied exactly.

---

## 12. Correctness

The algorithm maintains the following property:

> For every recursive subarray `A[low...high]`, the returned `min` is the minimum element of that subarray and the returned `max` is the maximum element of that subarray.

### Base Case: One Element

For a subarray containing one element, that element is necessarily both the minimum and maximum.

Therefore, the property holds.

### Base Case: Two Elements

The two elements are compared directly.

The smaller element is returned as the minimum and the larger element as the maximum.

Therefore, the property holds.

### Maintenance / Recursive Case

Assume the algorithm correctly finds the minimum and maximum of both halves.

The overall minimum must be the smaller of:

```text
left_min
right_min
```

Similarly, the overall maximum must be the larger of:

```text
left_max
right_max
```

The algorithm performs exactly these two comparisons.

Therefore, the returned values are the minimum and maximum of the entire subarray.

Hence, by recursion, the algorithm correctly finds the minimum and maximum of the complete array.

---

## 13. Complexity Analysis

### Time Complexity

Every element participates in the recursive process, and each combination requires only a constant number of comparisons.

The recurrence is:

\[
T(n)=2T(n/2)+O(1)
\]

Using the Master Theorem:

\[
T(n)=O(n)
\]

Therefore:

\[
\boxed{\text{Time Complexity} = O(n)}
\]

In fact, the algorithm performs a linear number of element comparisons.

### Auxiliary Space Complexity

The algorithm is recursive.

At most `O(log n)` recursive calls exist on the recursion stack at a time.

Therefore:

\[
\boxed{\text{Auxiliary Space Complexity} = O(\log n)}
\]

The input array itself requires:

\[
O(n)
\]

memory, but this is not counted as auxiliary space.

---

## 14. Comparison with the Straightforward Method

| Method | Number of Comparisons | Time Complexity |
| --- | ---: | ---: |
| Find Min and Max Separately | `2n - 2` | `O(n)` |
| Divide and Conquer | `ceil(3n/2) - 2` | `O(n)` |

For large `n`:

\[
\left\lceil\frac{3n}{2}\right\rceil-2
<
2n-2
\]

Therefore, the divide-and-conquer approach performs fewer element comparisons while retaining linear time complexity.

---

## 15. Experimental Validation

The C program accepts an array from the user and displays:

- Minimum element
- Maximum element
- Actual number of comparisons
- Theoretical comparison bound
- Validation result
- Time complexity
- Auxiliary space complexity

The actual comparison count is checked against:

\[
\boxed{\left\lceil\frac{3n}{2}\right\rceil-2}
\]

If:

```text
Actual comparisons <= Theoretical upper bound
```

the required comparison bound is satisfied.

---

## 16. Sample Input

```text
============================================
   MINIMUM AND MAXIMUM USING DIVIDE & CONQUER
============================================

Enter number of elements: 8
Enter 8 elements:
7 2 9 4 1 8 3 6
```

---

## 17. Sample Output

```text
============================================
                 RESULT
============================================

Minimum = 1
Maximum = 9

--------------------------------------------
COMPARISON ANALYSIS
--------------------------------------------
Actual comparisons      : 10
Theoretical upper bound : ceil(3n/2) - 2 = 10

--------------------------------------------
VALIDATION
--------------------------------------------
Validation: Comparison count satisfies
the theoretical 3n/2 bound.

============================================
                COMPLEXITY
============================================
Time Complexity       : O(n)
Auxiliary Space       : O(log n)
```

---

## 18. Conclusion

The divide-and-conquer algorithm successfully finds both the minimum and maximum elements of an array while keeping the number of element comparisons within the required bound:

\[
\boxed{\left\lceil\frac{3n}{2}\right\rceil-2}
\]

The algorithm recursively divides the array into smaller subarrays, solves each subproblem independently, and combines their results using only two comparisons.

Compared with the straightforward approach requiring:

\[
2n-2
\]

comparisons, the divide-and-conquer approach requires approximately:

\[
\frac{3n}{2}
\]

comparisons.

The algorithm has:

\[
\boxed{O(n)}
\]

time complexity and:

\[
\boxed{O(\log n)}
\]

auxiliary space complexity due to recursion.

Therefore, the implementation validates that the divide-and-conquer approach is more comparison-efficient for finding both the minimum and maximum elements of an array.
