class treap {
    // treap is a syntactic sugar of the index of buffer of nodes
    // whose _top indicates the next free position to create a treap node
    // a treap::node holds data and treap object holds the index to the node
  private:
    using index = unsigned; // syntactic sugar to indentify indexes, easier to read
    struct node {
        index l = invalid(), r = invalid(); // initialized with invalid indexes
        int val, y, c = 1;
        int sum;

        node(int val = 0) : val(val), y(rand()), sum(val) {}

        int cnt(index n) { return valid(n) ? _buf[n].c : 0; }
        int getSum(index n) { return valid(n) ? _buf[n].sum : 0; }
        void recalc() {
            c = cnt(l) + cnt(r) + 1;
            sum = val + getSum(l) + getSum(r);
        }
    };

  public:
    treap() : _root{_top}, data{_buf[_top]} { _top++; }
    treap(index i) : _root{i}, data{_buf[i]} {} // used for typecasting index to treap
    treap &operator=(const treap &t) {
        _root = t._root;
        data = t.data;
        return *this;
    }
    friend pair<treap, treap> split(treap n, int k);
    friend treap merge(treap l, treap r);
    friend treap ins(treap t, treap n, int pos);
    static bool valid(index i) { return i <= SIZE; } // checks whether treap is valid
    static treap invalid() { return SIZE + 1; }      // returns invalid treap
    operator index() { return _root; }               // used for typecasting treap to index

    //private:
    const static int SIZE = 2e5;
    index _root = invalid();
    static std::array<node, SIZE + 1> _buf;
    static index _top;

  public:
    node &data; // storing values in treap
};
treap::index treap::_top = 0;
array<treap::node, treap::SIZE + 1> treap::_buf;

treap merge(treap l, treap r) {
    if (!treap::valid(l))
        return r;
    else if (!treap::valid(r))
        return l;
    else if (l.data.y > r.data.y) {
        l.data.r = merge(l.data.r, r);
        l.data.recalc();
        return l;
    } else {
        r.data.l = merge(l, r.data.l);
        r.data.recalc();
        return r;
    }
}

pair<treap, treap> split(treap t, int k) {
    if (!treap::valid(t)) return {treap::invalid(), treap::invalid()};
    if (k <= t.data.val) { // for lower_bound(k)
        auto pa = split(t.data.l, k);
        t.data.l = pa.second;
        t.data.recalc();
        return {pa.first, t};
    } else {
        auto pa = split(t.data.r, k);
        t.data.r = pa.first;
        t.data.recalc();
        return {t, pa.second};
    }
}

treap ins(treap t, treap n, int pos) {
    auto pa = split(t, pos);
    return merge(merge(pa.first, n), pa.second);
}
