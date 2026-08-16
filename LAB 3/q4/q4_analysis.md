# Q4 - Matrix Multiplication Using Strassen's Method

## 1. Objective

Multiply two square matrices of size $n \times n$ using **Strassen's divide-and-conquer matrix multiplication algorithm**.

Unlike conventional matrix multiplication, which requires eight recursive matrix multiplications at each divide-and-conquer step, Strassen's method reduces this to **seven recursive multiplications**.

This reduces the asymptotic time complexity from:

\[
\Theta(n^3)
\]

to:

\[
\Theta(n^{\log_2 7}) \approx \Theta(n^{2.807})
\]

---

## 2. Divide-and-Conquer Approach

Given two matrices:

\[
A=
\begin{bmatrix}
A_{11} & A_{12}\\
A_{21} & A_{22}
\end{bmatrix}
\]

and

\[
B=
\begin{bmatrix}
B_{11} & B_{12}\\
B_{21} & B_{22}
\end{bmatrix}
\]

each matrix is divided into four equal-sized submatrices.

Instead of performing the eight recursive multiplications required by ordinary block matrix multiplication, Strassen's algorithm computes seven products.

---

## 3. Strassen's Seven Products

The seven products are:

\[
M_1=(A_{11}+A_{22})(B_{11}+B_{22})
\]

\[
M_2=(A_{21}+A_{22})B_{11}
\]

\[
M_3=A_{11}(B_{12}-B_{22})
\]

\[
M_4=A_{22}(B_{21}-B_{11})
\]

\[
M_5=(A_{11}+A_{12})B_{22}
\]

\[
M_6=(A_{21}-A_{11})(B_{11}+B_{12})
\]

\[
M_7=(A_{12}-A_{22})(B_{21}+B_{22})
\]

Each multiplication above is performed recursively using Strassen's method.

---

## 4. Combining the Results

After calculating the seven products, the four blocks of the resulting matrix:

\[
C=AB
\]

are obtained as follows:

\[
C_{11}=M_1+M_4-M_5+M_7
\]

\[
C_{12}=M_3+M_5
\]

\[
C_{21}=M_2+M_4
\]

\[
C_{22}=M_1-M_2+M_3+M_6
\]

The four blocks are then combined to form the final matrix:

\[
C=
\begin{bmatrix}
C_{11} & C_{12}\\
C_{21} & C_{22}
\end{bmatrix}
\]

---

## 5. Base Case

The recursion terminates when the matrix size becomes $1 \times 1$.

For two single elements:

\[
C_{11}=A_{11}B_{11}
\]

Therefore, the base case is:

```text
if n = 1
    C[0][0] = A[0][0] * B[0][0]
```

---

## 6. Handling Matrix Size

The basic recursive formulation of Strassen's algorithm works conveniently when `n` is a power of two.

For example:

\[
2 \times 2
\]

\[
4 \times 4
\]

\[
8 \times 8
\]

\[
16 \times 16
\]

\[
\cdots
\]

The implementation also supports arbitrary positive values of `n`.

If `n` is not a power of two, the program pads the matrices with zeros to the next power of two.

For example:

\[
3\times3 \rightarrow 4\times4
\]

and:

\[
5\times5 \rightarrow 8\times8
\]

Since the added elements are zero, padding does not affect the required portion of the final product.

After multiplication, only the original $n \times n$ portion of the result is displayed.

---

## 7. Algorithm

1. Read the size `n`.
2. Determine the next power of two greater than or equal to `n`.
3. Dynamically allocate the matrices using the padded size.
4. Read the two input matrices.
5. Store the input values in the upper-left $n \times n$ portion of the padded matrices.
6. Recursively divide each matrix into four equal-sized blocks.
7. Compute the seven Strassen products `M1` through `M7`.
8. Recursively repeat the process for each required multiplication.
9. Combine the seven products to obtain `C11`, `C12`, `C21`, and `C22`.
10. Combine the four blocks into the final product matrix.
11. Display only the original $n \times n$ portion.
12. Free all dynamically allocated memory.

---

## 8. Pseudocode

```text
STRASSEN(A, B, C, n)

    if n = 1
        C[0][0] <- A[0][0] * B[0][0]
        return

    Divide A into A11, A12, A21, A22
    Divide B into B11, B12, B21, B22

    M1 <- STRASSEN(A11 + A22, B11 + B22)
    M2 <- STRASSEN(A21 + A22, B11)
    M3 <- STRASSEN(A11, B12 - B22)
    M4 <- STRASSEN(A22, B21 - B11)
    M5 <- STRASSEN(A11 + A12, B22)
    M6 <- STRASSEN(A21 - A11, B11 + B12)
    M7 <- STRASSEN(A12 - A22, B21 + B22)

    C11 <- M1 + M4 - M5 + M7
    C12 <- M3 + M5
    C21 <- M2 + M4
    C22 <- M1 - M2 + M3 + M6

    Combine C11, C12, C21, C22

    return C
```

---

## 9. Why Strassen's Method is Faster

In conventional divide-and-conquer matrix multiplication, each recursive step requires:

\[
8
\]

matrix multiplications of size $n/2 \times n/2$.

Therefore:

\[
T(n)=8T(n/2)+\Theta(n^2)
\]

which gives:

\[
T(n)=\Theta(n^3)
\]

Strassen's algorithm reduces the number of recursive multiplications from `8` to `7`.

Therefore:

\[
T(n)=7T(n/2)+\Theta(n^2)
\]

By the Master Theorem:

\[
T(n)=\Theta(n^{\log_2 7})
\]

Since:

\[
\log_2 7 \approx 2.807
\]

the complexity is:

\[
\boxed{\Theta(n^{2.807})}
\]

Thus, Strassen's method has a better asymptotic time complexity than conventional matrix multiplication.

---

## 10. Space Complexity

The implementation dynamically creates submatrices and temporary matrices during the recursive process.

The space required for storing matrices and temporary matrices is:

\[
\boxed{O(n^2)}
\]

The recursive call stack has depth:

\[
O(\log n)
\]

but the dominant auxiliary matrix storage is quadratic.

---

## 11. Example

For two $2 \times 2$ matrices:

\[
A=
\begin{bmatrix}
1 & 2\\
3 & 4
\end{bmatrix}
\]

\[
B=
\begin{bmatrix}
5 & 6\\
7 & 8
\end{bmatrix}
\]

the resulting product is:

\[
C=AB
\]

\[
C=
\begin{bmatrix}
19 & 22\\
43 & 50
\end{bmatrix}
\]

The program produces the same result using Strassen's seven recursive products.

---

## 12. Validation

The implementation validates the algorithm by:

- Accepting two square matrices as input.
- Performing multiplication using Strassen's divide-and-conquer method.
- Displaying the resulting matrix.
- Supporting non-power-of-two input sizes through zero padding.
- Printing the theoretical recurrence and time complexity.
- Properly deallocating all dynamically allocated memory.

---

## 13. Complexity Summary

| Operation | Complexity |
| --- | ---: |
| Matrix addition/subtraction | $\Theta(n^2)$ |
| Conventional matrix multiplication | $\Theta(n^3)$ |
| Strassen matrix multiplication | $\Theta(n^{\log_2 7})$ |
| Strassen approximate complexity | $\Theta(n^{2.807})$ |
| Auxiliary matrix storage | $O(n^2)$ |
| Recursion depth | `O(log n)` |

---

## 14. Conclusion

Strassen's algorithm is a divide-and-conquer technique for multiplying square matrices.

Its main improvement is reducing the number of recursive matrix multiplications from eight to seven. Although this introduces additional matrix additions and subtractions, those operations require only $\Theta(n^2)$ time.

The resulting recurrence is:

\[
T(n)=7T(n/2)+\Theta(n^2)
\]

which gives:

\[
\boxed{T(n)=\Theta(n^{\log_2 7})\approx\Theta(n^{2.807})}
\]

Therefore, Strassen's algorithm has a better asymptotic time complexity than conventional $\Theta(n^3)$ matrix multiplication.
