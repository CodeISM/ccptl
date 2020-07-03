# CCPTL
CodeISM Competitve Programming Template Library

## Aim
The aim of this repository is to provide copy-pastable code snippets which should be easy to modify to suit different problems. Focus is more on flexibility and efficiency/performance as opposed to readability.

## Usage
Code snippets in a file are meant to be self sufficient.

Note: A modern C++ compiler with support of `c++14` or later is required although most the files might work with lower versions too. Code is gauranteed to work with GCC/LLVM (Clang) toolchain but most of the code is portable across compilers and architectures.

## Directory
### Data Structures
- [BIT/Fenwick Tree](https://github.com/CodeISM/ccptl/blob/master/Data%20Structures/BIT.h): Supports prefix queries and point update in O(log N) after taking O(N) time to build with O(N) space.
- [Min Deque](https://github.com/CodeISM/ccptl/blob/master/Data%20Structures/min_deque.h): Finding minimum element out of current element in the deque. Overhead of one integer per element, but is quite space efficient in practice.
- [Ordered set](https://github.com/CodeISM/ccptl/blob/master/Data%20Structures/ordered_set.h): Dyanmic Order statistics in O(log N). Uses GNU's policy based data structure (pbds).
- [Sparse Table](https://github.com/CodeISM/ccptl/blob/master/Data%20Structures/sparse_table.h): Static data structure that can answer queries in O(1) after O(NlogN) preprocessing (for some functions).
- [DSU/Union-Find](https://github.com/CodeISM/ccptl/blob/master/Data%20Structures/DSU.h): Works in O(alpha(N)) and uses union by size heuristics. 

### Graph
- [2-SAT](https://github.com/CodeISM/ccptl/blob/master/Graph/2SAT.h): solves 2-SAT problem in O(#boolean variables + #clauses) with CNF based formulation.
- [DSU on tree](https://github.com/CodeISM/ccptl/blob/master/Graph/dsu_on_tree.h): In O(NlogN) answer all queries of type: *How many vertices in the subtree of vertex v has some property?*.
#### LCA
- [Tarjan's Offline LCA](https://github.com/CodeISM/ccptl/blob/master/Graph/tarjan_offline_lca.h): Most optimal algorithm for solving LCA. O(DFS + Q).
### Math
#### Number Theory
- [Wheel Factorization](https://github.com/CodeISM/ccptl/blob/master/Number%20Theory/wheel_factorization.h): 25% faster than sqrt(n) trial division
- [GCD (Greatest Common Divisor)](https://github.com/CodeISM/ccptl/blob/master/Number%20Theory/gcd.h): Iterative/Compile time constant
- [Extended Euclid](https://github.com/CodeISM/ccptl/blob/master/Number%20Theory/extended_euclid.h): iterative version, much faster than recursive.
- [Modular Exponentiation](https://github.com/CodeISM/ccptl/blob/master/Number%20Theory/modular_exponentiation.h): constexpr version.
- [Fibonacci Number](https://github.com/CodeISM/ccptl/blob/master/Number%20Theory/fibonacci.h): Time: O(logN) but much faster (small constant) than matrix exponentiation version. Uses iterative table doubling method.
#### Linear Algebra
- [Matrix](https://github.com/CodeISM/ccptl/blob/master/Linear%20Algebra/matrix.h): highly optimized: multiplication, exponentiation, transpose including versions with modular arithmetic.

### Dynamic Programming
### String Algorithms
- [Suffix Array and LCP](https://github.com/CodeISM/ccptl/blob/master/Strings/suffix_array.h): Contructs Suffix Array and LCP Array in linear space and time.
### Misc
- [Modular Arithmetic](https://github.com/CodeISM/ccptl/blob/master/Misc/modular.h): A convenient and efficient wrapper of plain `int` for modular arithmetic. Functionality provided: add, subtract, multiply, divide, exponentiation, inverse and IO.
- [Ska Sort](https://github.com/CodeISM/ccptl/blob/master/Misc/ska_sort.h): A much faster (2x w.r.t. std::sort) sorting algorithm.
- [All Permutations](https://github.com/CodeISM/ccptl/blob/master/Misc/all_permutations.h): Generate all permutations of a sequence (iterative) in some order (not lexicographic).
- [N-D vector](https://github.com/CodeISM/ccptl/blob/master/Misc/nd_vector.h): A less cumbersome declarator of next N-Dimensional `std::vector`.

## TODO
- Update this readme with new (updated) content
- Test the implementation for bugs

## Authorship
Many of the implementations are common in folklore of competitive programming and the authour is unknown. Whenever possible author of the code is added. Kindly contact us in case of any issues.

