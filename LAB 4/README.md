# Questions  

### 1. Application of sorting-I:   

Assume that we are given n pairs of items as input, where the first item is a number and the second item is one of three colours (red, blue, or yellow).  
Further assume that the items are sorted by number. Give an O(n) algorithm to sort
the items by colour (all reds before all blues before all yellows) such that the numbers for
identical colours stay sorted. By choosing the proper input representation, write a program
in C to validate your algorithm.  

### 2. Application of sorting-II:   

Given two sets S1 and S2 (each of size n), and a number x, describe an O(n · logn) algorithm for finding whether there exists a pair of elements, one from S1 and one from S2, that add up to x. By choosing the proper input representation,
write a program in C to validate your algorithm.  

### 3. Application of sorting-III:   

Given a set S of n integers and an integer T, give an O(nk−1·log n) algorithm to test whether k of the integers in S add up to T. By choosing the properinput representation, write a program in C to validate your algorithm.  

### 4. Application of sorting-IV:   

A camera at the door tracks the entry time ai and exit time bi(assume bi > ai) for each of n the persons pi attending a party. Give an O(n·logn) algorithm that analyses this data to determine the time when the most people were simultaneously
present at the party. Assume that all entry and exit times are distinct (no ties). By choosing
the proper input representation, write a program in C to validate your algorithm.  

### 5. Application of sorting-V:   

Given a list I of n intervals, specified as (xi,yi) pairs, return a list where the overlapping intervals are merged. For I = {(1,3),(2,6),(8,10),(7,18)} the output should be {(1,6),(7,18)}. Your algorithm should run in worst-case O(n·logn) time
complexity. By choosing a suitable input and output representation, write a program in C
to validate your algorithm.  

### 6. Application of sorting-VI:   

You are given a set S of n intervals on a line, with the ith interval described by its left and right endpoints (li,ri). Give an O(n · logn) algorithm to identify a point p on the line that is in the largest number of intervals. As an example, for S ={(10,40),(20,60),(50,90),(15,70)} no point exists in all four intervals, but p = 50 is an example of a point in three intervals. You can assume an endpoint counts as being in
its interval. By choosing a suitable input and output representation, write a program in C
to validate your algorithm