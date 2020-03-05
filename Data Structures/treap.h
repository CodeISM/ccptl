class treap {
    // treap is a syntactic sugar of the index of buffer of nodes
    // whose _top indicates the next free position to create a treap node
    // a treap::node holds data and treap object holds the index to the node
  private:
    const static int SIZE = 1e6;
    using index = unsigned; // syntactic sugar to indentify indexes, easier to read
    struct node {
        index l = SIZE + 1, r = SIZE + 1; // initialized with invalid indexes
        int val, y, c = 1;
        int sum;

        node(int val) : val(val), y(rand()), sum(val) {}

        int cnt(index n) { return valid(n) ? _buf[n].c : 0; }
        int getSum(index n) { return valid(n) ? _buf[n].sum : 0; }
        void recalc() {
            c = cnt(l) + cnt(r) + 1;
            sum = val + getSum(l) + getSum(r);
        }
    };

  public:
    treap() : _root{_top++} {}
    treap(index i) : _root{i} {} // used for typecasting index to treap
    friend pair<treap, treap> split(treap n, int k);
    friend treap merge(treap l, treap r);
    static bool valid(index i) { return i <= SIZE; }
    static index invalid() { return SIZE; }
    operator index() { return _root; } // used for typecasting treap to index

    treap ins(treap t, treap n, int pos) {
        auto pa = split(t, pos);
        return merge(merge(pa.first, n), pa.second);
    }
    int &val = _buf[_root].val;

  private:
    index _root = SIZE + 1;
    static std::array<node, SIZE + 1> _buf;
    static index _top;
};
treap::index treap::_top = 0;

treap merge(treap l, treap r) {
    if (!treap::valid(l)) return r;
    if (!treap::valid(r)) return l;
    treap::node &left = treap::_buf[l], &right = treap::_buf[r];
    if (left.y > right.y) {
        left.r = merge(left.r, r);
        left.recalc();
        return l;
    } else {
        right.l = merge(l, right.l);
        right.recalc();
        return r;
    }
}

pair<treap, treap> split(treap t, int k) {
    if (!treap::valid(t)) return {treap::invalid(), treap::invalid()};
    treap::node &n = treap::_buf[t];
    if (k <= n.val) { // for lower_bound(k)
        auto pa = split(n.l, k);
        n.l = pa.second;
        n.recalc();
        return {pa.first, t};
    } else {
        auto pa = split(n.r, k);
        n.r = pa.first;
        n.recalc();
        return {t, pa.second};
    }
}
