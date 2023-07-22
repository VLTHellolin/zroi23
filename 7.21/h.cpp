#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>

namespace hellolin {
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
using ll = long long;
using ull = unsigned long long;
using lll = __int128;
template <class T>
using min_pq = __gnu_pbds::priority_queue<T, greater<T>, pairing_heap_tag>;
template <class T>
using max_pq = __gnu_pbds::priority_queue<T, less<T>, pairing_heap_tag>;
template <class T>
using vec = vector<T>;
using vecll = vector<ll>;
template <class T>
using vvec = vec<vec<T>>;
using vvecll = vec<vec<ll>>;
constexpr static ull mod_1e97 = 1e9 + 7, mod_998 = 998244353, mod_1e18 = 1e18, inf = LONG_LONG_MAX;
#define _x first
#define _y second
#define allof(x) x.begin(), x.end()
#define alllof(x) x.begin() + 1, x.end()
#define pb emplace_back
#ifdef LOCAL
#define dbg(x) cerr << __LINE__ << ": " << #x << " = " << x << endl
#else
#define dbg(x) void(0)
#endif
template <class T>
T pow(T x, ll y, ull m) {
    T z = 1;
    while (y) {
        if (y & 1) z = (z * x) % m;
        x = (x * x) % m;
        y >>= 1;
    }
    return z;
}
template <class T>
void readarr(T st, T ed) {
    while (st != ed) {
        cin >> *st;
        ++st;
    }
}
template <class T>
void writearr(T st, T ed, char s = ' ', bool e = 1) {
    while (st != ed) {
        cout << *st << s;
        ++st;
    }
    if (e) cout << endl;
}
void solve();
} // namespace hellolin

#define FILEIO 0
#define FILENAME ""
#define FASTIO 0
#define MULTI 0

int main() {
#if FILEIO
    freopen(FILENAME ".in", "r", stdin), freopen(FILENAME ".out", "w", stdout);
#endif
#if FASTIO
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
#endif
#if MULTI
    long long Ts;
    std::cin >> Ts;
    while (Ts--)
        hellolin::solve();
#else
    hellolin::solve();
#endif

    return 0;
}

namespace hellolin {

#define ll int

constexpr static ll N = 1e5 + 11, RT = 45;
class node {
public:
    ll ls, rs, sum;
    explicit node(ll _s = 0)
        : sum(_s) {}
    node &operator=(const node &t) {
        ls = t.ls, rs = t.rs, sum = t.sum;
        return *this;
    }
};
static array<node, N * RT> g;
static array<ll, N * RT> his_fa, his_dep;

// node g[N * RT];
// ll his_fa[N], his_dep[N];
ll n, m, ret, all, sall;
ll op, x, y;
void build_tree(ll l, ll r, ll &ans) {
    ans = ++all;
    if (l == r) {
        g[ans].sum = ++sall;
        return;
    }
    ll mid = (l + r) >> 1;
    build_tree(l, mid, g[ans].ls);
    build_tree(mid + 1, r, g[ans].rs);
}
void modify(ll l, ll r, ll p, ll &ans, ll prev, ll val) {
    ans = ++all;
    g[ans] = g[prev];
    if (l == r) {
        g[ans].sum = val;
        return;
    }
    ll mid = (l + r) >> 1;
    if (p <= mid)
        modify(l, mid, p, g[ans].ls, g[prev].ls, val);
    else
        modify(mid + 1, r, p, g[ans].rs, g[prev].rs, val);
}
ll query(ll l, ll r, ll p, ll &ans) {
    if (l == r) {
        return g[ans].sum;
    }
    ll mid = (l + r) >> 1;
    if (p <= mid)
        return query(l, mid, p, g[ans].ls);
    else
        return query(mid + 1, r, p, g[ans].rs);
}

ll find(ll p, ll ver) {
    ll fp = query(1, n, p, his_fa[ver]);
    return p == fp ? p : find(fp, ver);
}
void merge(ll x, ll y, ll ver) {
    x = find(x, ver - 1);
    y = find(y, ver - 1);
    if (x == y) {
        his_fa[ver] = his_fa[ver - 1];
        his_dep[ver] = his_dep[ver - 1];
        return;
    }
    ll dx = query(1, n, x, his_dep[ver - 1]);
    ll dy = query(1, n, y, his_dep[ver - 1]);
    if (dx == dy) {
        modify(1, n, x, his_fa[ver], his_fa[ver - 1], y);
        // modify(1, n, x, his_dep[ver], his_dep[ver - 1], y);
        modify(1, n, y, his_dep[ver], his_dep[ver - 1], dy + 1);
        return;
    }
    if (dx > dy) swap(x, y);
    modify(1, n, x, his_fa[ver], his_fa[ver - 1], y);
    his_dep[ver] = his_dep[ver - 1];
}
bool same(ll x, ll y, ll ver) {
    return find(x, ver) == find(y, ver);
}

void solve() {
    // freopen("C:/Users/lin/Downloads/P3402_3.in","r",stdin);
    // freopen("C:/Users/lin/Downloads/TMP", "w", stdout);
    cin >> n >> m;
    build_tree(1, n, his_fa[0]);
    for (ll i = 1; i <= m; i++) {
        cin >> op >> x;
        if (op != 2) cin >> y;
        // dbg(op), dbg(x);

        if (op == 1) {
            merge(x, y, i);
        } else if (op == 2) {
            his_fa[i] = his_fa[x];
            his_dep[i] = his_dep[x];
        } else {
            his_fa[i] = his_fa[i - 1];
            his_dep[i] = his_dep[i - 1];
            cout << same(x, y, i) << '\n';
        }
    }
}
} // namespace hellolin