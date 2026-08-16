# Q5 — Special-Pattern Matrix Multiplication Using Divide and Conquer

## 1. Problem Statement

Two square matrices of size `n × n` are given, where:

\[
n = 2^k
\]

for some natural number `k`.

Each matrix has the following recursive structure:

\[
M =
\begin{bmatrix}
M_1 & M_2 \\
M_2 & M_1
\end{bmatrix}
\]

That is:

- The two diagonal blocks are identical.
- The two off-diagonal blocks are identical.
- Each block itself has the same recursive structure.
- The recursion continues until `1 × 1` matrices are reached.

The objective is to design a **divide-and-conquer algorithm** to multiply two such matrices in:

\[
\boxed{O(n^2)}
\]

time.

---

## 2. Objective

The program should:

- Take `k` as input.
- Calculate the matrix size automatically as:

\[
n = 2^k
\]

- Accept two `n × n` matrices having the required special structure.
- Multiply them using a divide-and-conquer approach.
- Exploit the repeated diagonal and off-diagonal blocks.
- Achieve `O(n²)` time complexity.
- Display the resulting matrix.

---

## 3. Special Matrix Structure

Let the two input matrices be:

\[
A =
\begin{bmatrix}
A_1 & A_2 \\
A_2 & A_1
\end{bmatrix}
\]

and

\[
B =
\begin{bmatrix}
B_1 & B_2 \\
B_2 & B_1
\end{bmatrix}
\]

where each block has size:

\[
\frac{n}{2} \times \frac{n}{2}
\]

The important observation is that only **two distinct blocks** exist in each matrix.

For example, the lower-left block of `A` is the same as `A₂`, and the lower-right block is the same as `A₁`.

The same property holds for `B`.

---

## 4. Ordinary Block Multiplication

If ordinary block matrix multiplication is applied:

\[
C = AB
\]

then:

\[
C =
\begin{bmatrix}
C_1 & C_2 \\
C_2 & C_1
\end{bmatrix}
\]

where:

\[
C_1 = A_1B_1 + A_2B_2
\]

and:

\[
C_2 = A_1B_2 + A_2B_1
\]

Directly calculating these expressions would require four recursive matrix multiplications:

\[
A_1B_1,\quad A_2B_2,\quad A_1B_2,\quad A_2B_1
\]

However, the special structure allows us to reduce this to only **two recursive multiplications**.

---

## 5. Divide-and-Conquer Optimization

Define:

\[
P=(A_1+A_2)(B_1+B_2)
\]

Expanding:

\[
P =
A_1B_1+A_1B_2+A_2B_1+A_2B_2
\]

Now define:

\[
Q=(A_1-A_2)(B_1-B_2)
\]

Expanding:

\[
Q =
A_1B_1-A_1B_2-A_2B_1+A_2B_2
\]

Adding `P` and `Q`:

\[
P+Q =
2A_1B_1+2A_2B_2
\]

Therefore:

\[
\boxed{
C_1=\frac{P+Q}{2}
}
\]

Similarly, subtracting:

\[
P-Q =
2A_1B_2+2A_2B_1
\]

Therefore:

\[
\boxed{
C_2=\frac{P-Q}{2}
}
\]

Thus, instead of four recursive matrix multiplications, only two are required.

---

## 6. Resulting Matrix

After calculating `C₁` and `C₂`, the result is:

\[
C =
\begin{bmatrix}
C_1 & C_2 \\
C_2 & C_1
\end{bmatrix}
\]

Therefore, the resulting matrix has exactly the same special structure as the input matrices.

This means the structure is preserved recursively at every level.

---

## 7. Algorithm

### Special Matrix Multiplication

Given:

\[
A=
\begin{bmatrix}
A_1&A_2\\
A_2&A_1
\end{bmatrix}
\]

and:

\[
B=
\begin{bmatrix}
B_1&B_2\\
B_2&B_1
\end{bmatrix}
\]

perform the following:

1. If `n = 1`, multiply the two elements directly.
2. Divide `A` and `B` into four equal-sized blocks.
3. Extract the two unique blocks `A₁`, `A₂`, `B₁`, and `B₂`.
4. Calculate:

\[
P=(A_1+A_2)(B_1+B_2)
\]

5. Calculate:

\[
Q=(A_1-A_2)(B_1-B_2)
\]

6. Recursively compute `P` and `Q`.
7. Calculate:

\[
C_1=\frac{P+Q}{2}
\]

8. Calculate:

\[
C_2=\frac{P-Q}{2}
\]

9. Construct:

\[
C=
\begin{bmatrix}
C_1&C_2\\
C_2&C_1
\end{bmatrix}
\]

10. Return `C`.

---

## 8. Pseudocode

```text
SPECIAL-MULTIPLY(A, B, n)

    if n = 1
        C[1][1] ← A[1][1] × B[1][1]
        return C

    Divide A into A1, A2, A2, A1
    Divide B into B1, B2, B2, B1

    P ← SPECIAL-MULTIPLY(A1 + A2, B1 + B2, n/2)

    Q ← SPECIAL-MULTIPLY(A1 - A2, B1 - B2, n/2)

    C1 ← (P + Q) / 2

    C2 ← (P - Q) / 2

    C ← | C1  C2 |
         | C2  C1 |

    return C
```

## 9. Recurrence Relation

At each recursive level:

- The matrices are divided into blocks of size `n/2`.
- Only two recursive matrix multiplications are performed.
- Matrix additions and subtractions require `O(n²)` time.

Therefore:

\[
T(n)=2T(n/2)+O(n^2)
\]

For the base case:

\[
T(1)=O(1)
\]

## 10. Complexity Analysis

Using the Master Theorem:

\[
T(n)=aT(n/b)+f(n)
\]

where:

\[
a=2
\]

\[
b=2
\]

\[
f(n)=O(n^2)
\]

Calculate:

\[
n^{\log_b a}=n^{\log_2 2}=n
\]

Since:

\[
f(n)=O(n^2)
\]

dominates:

\[
n^{\log_2 2}=n
\]

the recurrence falls under Case 3 of the Master Theorem.

Therefore:

\[
T(n)=O(n^2)
\]

Hence, the required multiplication can be performed in:

\[
O(n^2)
\]

time.

## 11. Why the Algorithm is O(n²)

The key improvement comes from exploiting the repeated blocks.

Without using the special structure, four recursive multiplications would be required.

Using the special structure:

\[
2\text{ recursive multiplications}
\]

are sufficient.

The additional additions and subtractions take:

\[
O(n^2)
\]

time.

Therefore:

\[
T(n)=2T(n/2)+O(n^2)
\]

which results in:

\[
O(n^2)
\]

time complexity.

## 12. Space Complexity

The matrices and temporary matrices require quadratic storage.

Therefore, the auxiliary matrix storage is:

\[
O(n^2)
\]

The recursion depth is:

\[
O(\log n)
\]

## 13. Input Handling

The problem specifies:

\[
n=2^k
\]

Therefore, the program asks the user to enter `k` instead of `n`.

The program automatically calculates:

\[
n=2^k
\]

For example:

| `k` | `n = 2^k` |
| ---: | ---: |
| 0 | 1 |
| 1 | 2 |
| 2 | 4 |
| 3 | 8 |
| 4 | 16 |
| 5 | 32 |

Thus, the matrix size always satisfies the condition given in the problem.

## 14. Correctness

The algorithm is correct because the product of two matrices having the given structure also has the same structure.

Given:

\[
A=
\begin{bmatrix}
A_1&A_2\\
A_2&A_1
\end{bmatrix}
\]

and:

\[
B=
\begin{bmatrix}
B_1&B_2\\
B_2&B_1
\end{bmatrix}
\]

their product is:

\[
AB=
\begin{bmatrix}
A_1B_1+A_2B_2 & A_1B_2+A_2B_1\\
A_1B_2+A_2B_1 & A_1B_1+A_2B_2
\end{bmatrix}
\]

Therefore, the resulting diagonal blocks are identical and the resulting off-diagonal blocks are also identical.

The algorithm calculates exactly these two blocks using `P` and `Q`.

Hence, the algorithm produces the correct matrix product.

## 15. Conclusion

The special recursive structure of the matrices can be exploited to design an efficient divide-and-conquer multiplication algorithm.

For matrices of the form:

\[
\begin{bmatrix}
M_1&M_2\\
M_2&M_1
\end{bmatrix}
\]

only two recursive multiplications are required:

\[
P=(A_1+A_2)(B_1+B_2)
\]

and:

\[
Q=(A_1-A_2)(B_1-B_2)
\]

The required result blocks are then obtained using:

\[
C_1=\frac{P+Q}{2}
\]

and:

\[
C_2=\frac{P-Q}{2}
\]

This gives the recurrence:

\[
T(n)=2T(n/2)+O(n^2)
\]

and hence:

\[
T(n)=O(n^2)
\]

Therefore, the special structure allows the matrix multiplication to be performed in the required O(n²) time.
