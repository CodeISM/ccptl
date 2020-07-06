/*
* Author: Madhur Chauhan
* Use: Static DS which requires O(N logN) preprocessing after which queries
*      can be answered very fast - O(1) for some functions.
* Time Complexity: 
*       O(NlogN) to build
*       O(1) or O(logN) for query (depends on function)
* Space Complexity: O(NlogN)
* Notes: 1. An example operation class is shown (compare_min), replace "min" with your desired operation.
*           Create a different class for each operation or use STLs function objects: plus<int>, less<int>, etc.
*        2. query_fast is O(1) and is useful when queries can be answered by two *overlapping* ranges.
*           Examples: min, max, gcd and NOT sum.
*        3. query_slow is O(logN) and is useful for rest of the functions like sum.
* Usage:
*       SparseTable<int, compare_min> st(vec);  // constructs sparse table from vec (vector<int>)
*       st.query(left, right);       // Query range: [left,right] in O(logN)
*       st.query_fast(left, right);  // Query range: [left,right] in O(1)
*       st(i,j); // to access element at ith row (out of logN rows) and jth column (out of N columns)
* Status: Tested
*/

#include "Data Structures/dynamic_matrix.h"
template <typename T>
struct compare_min {
    constexpr T operator()(const T &a, const T &b) const {
        return a < b ? a : b; // change this function (currently: minimum)
    }
};
template <typename T, class F = compare_min<T>>
class sparse_table {
  public:
    sparse_table(const vector<T> &v) : N{(int32_t)v.size()}, K{31 - __builtin_clz(N)}, table(K + 1, N) {
        copy(begin(v), end(v), table.begin());
        for (int j = 1; j <= K; ++j)
            for (int i = 0; i + (1 << j) <= N; ++i)
                table(j, i) = _op(table(j - 1, i), table(j - 1, i + (1 << (j - 1))));
    }
    T query_fast(int l, int r) { // 0-based interval: [l,r]
        int dep = 31 - __builtin_clz(r - l + 1);
        return _op(table(dep, l), table(dep, r - (1 << dep) + 1));
    }
    // O(log N)/query
    T query(int l, int r) { // 0-based interval: [l,r]
        T ans = table(0, l++);
        for (int j = K; j >= 0; j--) {
            if ((1 << j) <= r - l + 1) {
                ans = _op(ans, table(j, l));
                l += 1 << j;
            }
        }
        return ans;
    }

  private:
    int32_t N, K; // K = ceil(log(N))
    dynamic_matrix<T> table;
    F _op = F();
};
