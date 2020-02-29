#include "bits/stdc++.h"
using namespace std;

/////////////////// TYPES & MACROS ///////////////////////////////
#define mp make_pair
#define eb emplace_back
#define pb push_back
#define all(x) x.begin(), x.end()
#define ff first
#define ss second
#define vv vector
#define exist(s, e) (s.find(e) != s.end())
#define SZ(x) ((int)(x).size())
//#define int int64_t
#define el '\n'
template <class T>
bool inline rmn(T &a, T b) { return a > b ? (a = b, true) : false; }
template <class T>
bool inline rmx(T &a, T b) { return a < b ? (a = b, true) : false; }
const int32_t MOD = 1'000'000'007, INF = 0x3f3f3f3f;
const int64_t INFLL = ((int64_t)INF << 32) | INF;

//////////////////// DEBUG /////////////////////////////////////////
#ifdef LOCAL
#define D(x) cerr << #x << " is:\t" << x << '\n';
#define DD(x, y) cerr << '(' << #x << ',' << #y << ") are:\t" << x << ' ' << y << '\n';
#define DDD(x, y, z) cerr << '(' << #x << ',' << #y << ',' << #z << ") are:\t" << x << ' ' << y << ' ' << z << '\n';
#else
#define D(x) ;
#define DD(x, y) ;
#define DDD(x, y, z) ;
#endif

/////////////////// VARIABLES & FUNCTIONS//////////////////////////
vv<vv<int>> adj;
vv<int> vis, color;
int dx8[] = {0, 1, 1, 1, 0, -1, -1, -1}, dy8[] = {1, 1, 0, -1, -1, -1, 0, 1}, dx4[] = {0, 1, 0, -1}, dy4[] = {1, 0, -1, 0};

template <typename T>
class treap {

	struct node { // contains (X,Y) where X: key (BST), Y: priority (heap)
		using itr = typename std::vector<node>::iterator;
		itr l, r;
		T val;
		int y, c = 1;
		long long sum;
		node(T val, itr l, itr r) : l{l}, r{r}, val(val), y(rand()), sum(val) {}
	};
	using itr = typename std::vector<node>::iterator;

	int cnt(itr p) { return valid(p) ? p->c : 0; }
	long long getSum(itr p) { return valid(p) ? p->sum : 0; }
	void recalc(itr p) { p->c = cnt(p->l) + cnt(p->r) + 1, p->sum = p->val + getSum(p->l) + getSum(p->r); }

  public:
	treap(int sz = 1e5) {
		_buf.reserve(sz);
		srand(time(NULL));
	}
	bool valid(itr p) { return p != end(_buf); }

	pair<itr, itr> split(int k) { return split(root, k); }
	pair<itr, itr> split(itr p, int k) {
		if (!valid(p)) return {};
		if (p->val >= k) { // "n->val >= k" for lower_bound(k)
			auto pa = split(p->l, k);
			p->l = pa.second;
			recalc(p);
			return {pa.first, p};
		} else {
			auto pa = split(p->l, k); // and just "k"
			p->r = pa.first;
			recalc(p);
			return {p, pa.second};
		}
	}

	itr merge(itr l, itr r) {
		if (!valid(l)) return r;
		if (!valid(r)) return l;
		if (l->y > r->y) {
			l->r = merge(l->r, r);
			recalc(l);
			return l;
		} else {
			r->l = merge(l, r->l);
			recalc(l);
			return r;
		}
	}

	void insert(T val, int pos = 0) {
		_buf.emplace_back(val, end(_buf), end(_buf));
		if (!valid(root)) root = begin(_buf);
		auto pa = split(root, pos);
		root = merge(merge(pa.first, prev(end(_buf))), pa.second);
	}

  private:
	vector<node> _buf;

  public:
	itr root;
};
///////////////////// MAIN STARTS //////////////////////////////////
int32_t main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cout << fixed << setprecision(13);
	cerr << fixed << setprecision(3);

	int n;
	cin >> n;
	vector<int> x(n), v(n);
	for (int i = 0; i < n; i++)
		cin >> x[i];
	for (int i = 0; i < n; i++)
		cin >> v[i];
	vector<pair<int, int>> pts(n);
	for (int i = 0; i < n; i++)
		pts[i] = {v[i], x[i]};
	sort(pts.begin(), pts.end());
	treap<int> t(2e5);
	t.insert(pts[0].second);
	long long ans = 0;
	for (int i = 1; i < n; i++) {
		auto pa = t.split(pts[i].second);
		if (t.valid(pa.first)) {
			ans += pa.first->c * 1ll * pts[i].second - pa.first->sum;
		}
		t.root = t.merge(pa.first, pa.second);
		t.insert(pts[i].second, pts[i].second);
	}
	cout << ans << endl;

	return 0;
}

