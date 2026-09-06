# Design and Analysis of Algorithms (DAA) Laboratory

![Language](https://img.shields.io/badge/Language-C-blue.svg)

![Course](https://img.shields.io/badge/Course-DAA-success.svg)

![Semester](https://img.shields.io/badge/Semester-3rd-green.svg)

![Institute](https://img.shields.io/badge/Institute-IIIT%20Bhubaneswar-orange.svg)

This repository contains all programming assignments for the **Design and Analysis of Algorithms (DAA) Laboratory**. The assignments focus on implementing algorithms, analyzing their complexity, and validating their performance through practical experimentation.

## Student Information

* **Name:** Preetika Mishra
* **Branch:** CSE-B (1)
* **Semester:** 3rd Semester
* **Institute:** IIIT Bhubaneswar

---

## Repository Structure

```text
DAA-Lab/
│
├── Lab 1/
│   ├── Code solutions/
│   ├── csv files/
│   ├── graphs/
│   └── README.md
│
├── Lab 2/
│   ├── Q1/
│   ├── Q2/
│   ├── Q3/
│   └── README.md
│
├── Lab 3/
│   ├── q1/
│   ├── q2/
│   ├── q3/
│   ├── q4/
│   ├── q5/
│   ├── q6/
│   └── README.md
│
├── Lab 4/
│   ├── q1/
│   ├── q2/
│   ├── q3/
│   ├── q4/
│   ├── q5/
│   ├── q6/
│   └── README.md
│
├── Lab 5/
│   ├── q1/
│   ├── q2/
│   ├── q3/
│   ├── q4/
│   └── README.md
│
├── Lab 6/
│   ├── Set 1/
│   │   ├── q1/
│   │   ├── q2/
│   │   ├── q3/
│   │   └── q4/
│   │
│   ├── Set 2/
│   │   ├── q1/
│   │   ├── q2/
│   │   ├── q3/
│   │   └── q4/
│   │
│   └── README.md
│
├── .gitignore
└── README.md
```

---

## Laboratory Assignments

| Lab       | Topics                                                                                                                                                       | Status |
| --------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------ | ------ |
| **Lab 1** | Growth Analysis, Coin Toss Simulation, Bubble Sort, Tower of Hanoi, Partition Point, Element Uniqueness                                                      | ✅      |
| **Lab 2** | Dictionary Operations, Merge Sort Comparison, k-way Merging                                                                                                  | ✅      |
| **Lab 3** | Binary vs Ternary Search, Defective Coin, Min-Max, Strassen Matrix Multiplication, Special-Pattern Matrix Multiplication, Loop Invariants and Selection Sort | ✅      |
| **Lab 4** | Applications of Sorting                                                                                                                                      | ✅      |
| **Lab 5** | Selection using Quickselect, Quick Sort, Heap Sort                                                                                                           | ✅      |
| **Lab 6** | 1D Array Operations, 2D Matrix Operations, FFT-Based Convolution, Sorting via Reversal                                                                       | ✅      |

---

## Algorithms Covered

* Asymptotic Growth Analysis
* Experimental Algorithm Analysis
* Sorting Algorithms
* Bubble Sort
* Selection Sort
* Merge Sort
* Modified 3-way Merge Sort
* Quick Sort
* Heap Sort
* Quickselect
* Dictionary Operations
* Arrays and Linked Lists
* Binary Search
* Ternary Search
* Divide and Conquer
* Recursive Algorithms
* Strassen's Matrix Multiplication
* Special-Pattern Matrix Multiplication
* Minimum and Maximum using Pairwise Comparison
* Defective Coin Problem
* Loop Invariants
* Sequential Merging
* Pairwise Merging
* k-way Merging
* Randomized Algorithms
* Selection Algorithms
* Order Statistics
* Median Finding
* kth Smallest Element
* Partitioning
* Heap Construction
* Time Complexity Analysis
* Space Complexity Analysis
* Sorting-based Problem Solving
* Counting/Bucket-Based Sorting
* Combination Generation
* Recursive Search
* Event-Based Sorting
* Sweep-Line Technique
* Interval Merging
* Interval Overlap Analysis
* Event Ordering
* Maintaining Active Intervals
* 1D Array Operations
* 2D Matrix Operations
* Matrix Addition
* Matrix Multiplication
* Matrix Transposition
* Matrix Determinant
* Symmetric Matrix Checking
* Eigenvalue and Eigenvector Computation
* Convolution
* Fast Fourier Transform (FFT)
* FFT-Based Divide and Conquer
* Weighted Reversal Cost
* Reversal-Based Sorting
* Stable Partitioning

---

## Programming Language

* **Language:** C
* **Compiler:** GCC

---

## Folder Organization

Each lab contains:

* C source code (`.c`)
* Algorithm and complexity analysis
* CSV files where applicable
* Graph generation programs and graphs where applicable
* Individual README files

Lab 2 includes experimental data that can be imported into Microsoft Excel for performance graphs.

Lab 3 contains C implementations and documentation for algorithm explanation, correctness analysis, comparison counting, recurrence analysis, and complexity analysis.

Lab 4 contains C implementations and algorithm/complexity analysis for sorting-based applications.

Lab 5 contains C implementations and algorithm analysis for Quickselect, Quick Sort, and Heap Sort.

Lab 6 contains C implementations and corresponding algorithm/complexity analysis for array operations, matrix operations, FFT-based convolution, and reversal-based sorting.

---

## Learning Objectives

* Understand algorithm design techniques.
* Analyze time and space complexity.
* Compare algorithms experimentally.
* Study asymptotic growth of functions.
* Visualize algorithm performance using graphs.
* Compare different data structures and algorithmic approaches.
* Understand and implement divide-and-conquer algorithms.
* Analyze recursive algorithms using recurrence relations.
* Apply loop invariants to prove algorithm correctness.
* Minimize the number of comparisons in algorithms.
* Understand selection algorithms and order statistics.
* Find median without explicitly sorting input.
* Find kth smallest using partitioning.
* Understand Quick Sort.
* Understand heap construction and Heap Sort.
* Work with randomly generated input stored in files.
* Analyze operations on 1D arrays and 2D matrices.
* Implement convolution using FFT.
* Analyze algorithms involving weighted operation costs.
* Design sorting algorithms using reversals.
* Improve problem-solving skills using C programming.

---

## How to Use

Clone the repository:

```bash
git clone https://github.com/<username>/DAA-Lab.git
cd DAA-Lab
```

Compile and run a program:

```bash
gcc "Code solutions/Q1_FunctionGraph.c" -o Q1 -lm
./Q1
```

For Lab 2:

```bash
gcc Q2/mergesort_compare.c -o Q2
./Q2
```

For Lab 3:

```bash
gcc Q1/binary_ternary_search.c -o Q1
./Q1
```

For Lab 4:

```bash
gcc q1/q1.c -o q1
./q1
```

For Lab 5:

```bash
gcc q1/q1.c -o q1
./q1
```

For Lab 6:

```bash
gcc q1/q1.c -o q1 -lm
./q1
```

---

## Laboratory Contents

### Lab 1

1. Growth Rate Analysis
2. Coin Toss Simulation
3. Bubble Sort
4. Tower of Hanoi
5. Partition Point
6. Element Uniqueness

### Lab 2

1. Dictionary Operations using different data structures
2. Comparison of 2-way Merge Sort and Modified 3-way Merge Sort
3. Comparison of Sequential and Pairwise k-way Merging

### Lab 3

1. Binary Search vs Ternary Search
2. Search for Defective Coin using Divide and Conquer
3. Min/Max using Pairwise Comparison
4. Strassen Matrix Multiplication
5. Special-Pattern Matrix Multiplication using Divide and Conquer
6. Loop Invariants and Selection Sort

### Lab 4

1. Sorting Elements by Colour
2. Pair with Given Sum
3. k Elements with Given Sum
4. Maximum Simultaneous Party Attendance
5. Merge Overlapping Intervals
6. Point with Maximum Interval Overlap

### Lab 5

1. Median of N Numbers without Sorting
2. kth Smallest Element without Sorting
3. Quick Sort for N Random Elements Stored in File
4. Heap Sort for N Random Elements Stored in File

### Lab 6

#### Set 1

1. 1D Array Operations
2. 2D Matrix Operations
3. Convolution of Two Vectors
4. Sorting via Reversal

#### Set 2

1. 1D Array Operations
2. 2D Matrix Operations
3. Convolution of Two Vectors
4. Sorting via Reversal

---

## Complexity Highlights

| Lab       | Major Complexity                                                                                    |
| --------- | --------------------------------------------------------------------------------------------------- |
| **Lab 1** | Various basic and recursive algorithms                                                              |
| **Lab 2** | Merge-based algorithms and k-way merging                                                            |
| **Lab 3** | Divide and Conquer, Strassen, Selection Sort                                                        |
| **Lab 4** | O(n), O(n log n), O(n^(k−1) log n)                                                                  |
| **Lab 5** | Quickselect, Quick Sort, Heap Sort                                                                  |
| **Lab 6** | Array/Matrix operations, O(n log n) FFT convolution, O(n) reversal count, O(n log² n) reversal cost |

---  

# Future Additions

* More DAA laboratory assignments
* Additional graph visualizations
* Algorithm comparisons
* Performance benchmarking
* Improved documentation

---

# Author

**Preetika Mishra**

B.Tech – Computer Science & Engineering

IIIT Bhubaneswar

---

This repository is maintained as part of the Design and Analysis of Algorithms Laboratory coursework.