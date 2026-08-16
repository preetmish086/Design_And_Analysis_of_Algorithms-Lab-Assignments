# Design and Analysis of Algorithms (DAA) Laboratory

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Course](https://img.shields.io/badge/Course-DAA-success.svg)
![Semester](https://img.shields.io/badge/Semester-3rd-green.svg)
![Institute](https://img.shields.io/badge/Institute-IIIT%20Bhubaneswar-orange.svg)

This repository contains all the programming assignments completed as part of the **Design and Analysis of Algorithms (DAA) Laboratory**.

The objective of this repository is to implement, analyze and compare classical algorithms while studying their time and space complexities through practical experimentation.

---

# Student Information

| Field         | Details                          |
| ------------- | -------------------------------- |
| **Name**      | Preetika Mishra                  |
| **Branch**    | Computer Science and Engineering |
| **Semester**  | 3rd Semester                     |
| **Institute** | IIIT Bhubaneswar                 |

---

# Repository Structure

```text
DAA-Lab
│
├── Lab 1
│   ├── Code solutions
│   ├── csv files
│   ├── graphs
│   ├── README.md
│   └── ...
│
├── Lab 2
│   ├── Q1
│   │   ├── csv
│   │   ├── plots
│   │   └── ...
│   │
│   ├── Q2
│   │   ├── mergesort_compare.c
│   │   ├── mergesort_plot.gnu
│   │   └── ...
│   │
│   ├── Q3
│   │   ├── kway_merge_compare.c
│   │   ├── kway_plot.gnu
│   │   └── ...
│   │
│   └── README.md
│
├LAB 3/
├── q1/
│   ├── q1.c
│   └── q1_analysis.md
├── q2/
│   ├── q2.c
│   └── q2_analysis.md
├── q3/
│   ├── q3.c
│   └── q3_analysis.md
├── q4/
│   ├── q4.c
│   └── q4_analysis.md
├── q5/
│   ├── q5.c
│   └── q5_analysis.md
└── q6/
    ├── q6.c
    └── q6_analysis.md
│
├── README.md
└── .gitignore
```

---

# Laboratory Assignments

| Lab   | Topics Covered                                                                                          | Status |
| ----- | ------------------------------------------------------------------------------------------------------- | :----: |
| Lab 1 | Growth Analysis, Coin Toss Simulation, Bubble Sort, Tower of Hanoi, Partition Point, Element Uniqueness |    ✅   |
| Lab 2 | Dictionary Operations, Merge Sort Comparison, k-way Merging                                             |    ✅   |
| Lab 3 | Binary vs Ternary Search, Defective Coin, Min-Max using Pairwise Comparison, Strassen Matrix Multiplication, Special-Pattern Matrix Multiplication, Loop Invariants and Selection Sort |    ✅   |
| Lab 4 | ...                                                                                                     |   ...  |
| Lab 5 | ...                                                                                                     |   ...  |

---

# Algorithms Covered

Throughout the laboratory assignments, the following algorithmic techniques are implemented and analyzed:

* Asymptotic Growth Analysis
* Experimental Algorithm Analysis
* Sorting Algorithms
* Bubble Sort
* Selection Sort
* Merge Sort
* Modified 3-way Merge Sort
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
* Time Complexity Analysis
* Space Complexity Analysis

---

# Programming Language

* C

Compiler used:

* GCC (GNU Compiler Collection)

---

# Folder Organization

Each laboratory folder contains:

* Source code (`.c`)
* Generated CSV files
* Graph generation programs
* Graph images where applicable
* Individual README describing the assignment
* Complexity analysis

For **Lab 2**, experimental data is stored in CSV format and can be imported into **Microsoft Excel** to generate the required performance graphs.

For **Lab 3**, each question contains its corresponding C implementation and documentation, including algorithm explanation, correctness analysis, comparison counting, recurrence analysis, and complexity analysis where applicable.

---

# Learning Objectives

The aim of these laboratory assignments is to:

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
* Improve problem-solving skills using C programming.

---

# How to Use

Clone the repository

```bash
git clone https://github.com/<username>/DAA-Lab.git
```

Open any lab folder and compile the required C program.

Example:

```bash
gcc "Code solutions/Q1_FunctionGraph.c" -o Q1 -lm
./Q1
```

For **Lab 2**, navigate to the corresponding question folder and compile the required program using GCC.

Example:

```bash
gcc Q2/mergesort_compare.c -o Q2
./Q2
```

For **Lab 3**, navigate to the corresponding question folder and compile the required C program.

Example:

```bash
gcc Q1/binary_ternary_search.c -o Q1
./Q1
```

---

# Laboratory Contents

## Lab 1

Lab 1 contains:

* **Q1:** Growth Rate Analysis
* **Q2:** Coin Toss Simulation
* **Q3:** Bubble Sort
* **Q4:** Tower of Hanoi
* **Q5:** Partition Point
* **Q6:** Element Uniqueness

---

## Lab 2

Lab 2 contains:

* **Q1:** Dictionary Operations using different data structures
* **Q2:** Comparison of 2-way Merge Sort and modified 3-way Merge Sort
* **Q3:** Comparison of Sequential and Pairwise k-way Merging

---

## Lab 3

Lab 3 contains:

* **Q1:** Binary Search vs Ternary Search
* **Q2:** Search the Defective Coin using Divide and Conquer
* **Q3:** Minimum and Maximum using Pairwise Comparison
* **Q4:** Matrix Multiplication using Strassen's Method
* **Q5:** Special-Pattern Matrix Multiplication using Divide and Conquer
* **Q6:** Loop Invariants and Selection Sort

### Lab 3 Complexity Highlights

| Question | Algorithm | Complexity |
| -------- | --------- | ---------- |
| Q1 | Binary Search | `O(log₂ n)` |
| Q1 | Ternary Search | `O(log₃ n)` |
| Q2 | Defective Coin | `O(log n)` |
| Q3 | Pairwise Min-Max | `O(n)` |
| Q4 | Strassen's Matrix Multiplication | `O(n^log₂7)` ≈ `O(n^2.807)` |
| Q5 | Special-Pattern Matrix Multiplication | `O(n²)` |
| Q6 | Selection Sort | `Θ(n²)` |

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