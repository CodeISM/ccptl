/*
 * Author : Madhur Chauhan
 * Common Names: Fenwick Tree, Binary Indexed Tree
 * Use : Data structures which does prefix/range operation in O(log N) (small constant) with point updates.
 * Time Complexity : O(N) to build
 *                   O(logN) to query a range
 *                   O(logN) to update a point
 * Space Complexity: O(N)
 * Usage Notes: 1. USES 1-BASED INDEXING FOR ALL FUNCTIONS
 *              2. Template arguments: <element type "T",	// ex - int, long long
 *                                      operation "op">		// change line 24 with desired operation
 *              3. Examples:
 *                   BIT<long long> b(1e5, 67); // creates a bit with 10^5 elements initialized to 67
 *                                              // defaults to 0
 *                   BIT<long long> b(v);   // creates a bit on vector<long long> v
 *                   b.query(10);   // return op(b[1], b[2], ... , b[10])
 *                   b.update(pos, diff); // tree[pos] = op(tree[pos], diff)
 *                   b.lower_bound(target); // returns first occurence with prefix value as target
 */

template <typename T>
struct func {
    const T constexpr operator()(const T &a, const T &b) const {
        return a + b;
    }
};
template <typename T = int, class op = func<T>>
struct BIT {
    // constructs a BIT with a given size
    BIT(int size, T val = 0) : tree(size + 1, val) {}

    // constructs a BIT with given elements
    BIT(const vector<T> &list) : tree{0} {
        tree.insert(tree.end(), list.begin(), list.end());
        for (int size = tree.size(), i = 1; i < size; ++i) {
            int idx = i + (i & -i);
            if (idx < size)
                tree[idx] = func(tree[idx], tree[i]);
        }
    }
    void update(int pos, T diff) { // tree[pos] = func(tree[pos], diff);
        for (int sz = tree.size(); pos < sz; pos += pos & -pos)
            tree[pos] = func(tree[pos], diff);
    }
    T query(int pos) const { // prefix operation of values [1...pos]
        T res = tree[pos];
        for (pos -= pos & -pos; pos; pos -= pos & -pos)
            res = func(res, tree[pos]);
        return res;
    }
    int32_t lower_bound(T target) { // returns lower_bound(sum)
        int32_t ans = 0;
        T cur = 0;
        for (int sz = tree.size(), i = 1 << (31 - __builtin_clz(sz)); i && target; i >>= 1) {
            if (ans + i < sz && func(cur, tree[ans + i]) < target)
                cur = func(cur, tree[ans += i]);
        }
        return ans + 1;
    }

    vector<T> tree;
    const op func = op();
};