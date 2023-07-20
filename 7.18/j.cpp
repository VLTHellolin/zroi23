#include <vector>
#ifndef HELLOLIN_EXTENSIONS_HPP
#define HELLOLIN_EXTENSIONS_HPP 1
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
using db = double;
using ld = long double;
template <class T>
using min_pq = __gnu_pbds::priority_queue<T, greater<T>, pairing_heap_tag>;
template <class T>
using max_pq = __gnu_pbds::priority_queue<T, less<T>, pairing_heap_tag>;
template <class T>
using vec = vector<T>;
using vecll = vector<ll>;
template <class T>
using vvec = vec<vec<T>>;

constexpr static ull mod_1e97 = 1e9 + 7;
constexpr static ull mod_998 = 998244353;
constexpr static ull mod_1e18 = 1e18;

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
#define fiio(x)                   \
    freopen(x ".in", "r", stdin); \
    freopen(x ".out", "w", stdout)
#define fios                      \
    std::ios::sync_with_stdio(0); \
    std::cin.tie(nullptr);        \
    std::cout.tie(nullptr)

template <class T, class U>
void chmax(T &x, U y) { x = max(x, y); }
template <class T, class U>
void chmin(T &x, U y) { x = min(x, y); }
template <class T>
T gcd(T x, T y) { return y ? gcd(y, x % y) : x; }
template <class T>
T lcm(T x, T y) { return x * y / gcd(x, y); }
template <class T>
T pow(T x, ll y) {
    T z = 1;
    while (y) {
        if (y & 1) z *= x;
        x *= x;
        y >>= 1;
    }
    return z;
}
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
template <int M>
void _yesno(bool x) {
    string y[3] = {"yes", "Yes", "YES"}, n[3] = {"no", "No", "NO"};
    cout << (x ? y[M] : n[M]) << endl;
}
#define yesno _yesno<0>
#define YesNo _yesno<1>
#define YESNO _yesno<2>
void solve();
} // namespace hellolin

#endif

int main() {
    // fiio("task");
    fios;

    // int Ts; std::cin>>Ts; while(Ts--)
    hellolin::solve();

    return 0;
}

namespace hellolin {

constexpr static ll N = 1e5 + 11, LogN = 21, NN = 1e5, BIGN = 5e6 + 11;

class segement_tree {
private:
public:
};

ll n, m, a, b, va;
vecll ans(N);
vvec<ll> g(N), f(N, vecll(LogN + 1));
vecll deg(N);

namespace LCA {

void init(ll x = 1) { // ? OK
    for (ll i = 1; i <= LogN; i++) {
        f[x][i] = f[f[x][i-1]][i-1];
    }
    // dbg(1919);
    for (ll i : g[x]) {
        if (f[x][0] != i) {
            f[i][0] = x;
            deg[i] = deg[x];
            ++deg[i];
            init(i);
        }
    }
    // dbg(810);
}
ll lca(ll a, ll b) { // ? OK
    if (deg[a] < deg[b]) swap(a, b);
    ll c = deg[a] - deg[b];// , cc = -1;
    // dbg(114);
    for (ll i = 0; c; i++, c>>=1) {
        if (c & 1) a = f[a][i];
    }
    // if (cc != -1) a = f[a][cc];
    if (a == b) return a;
    for (ll i = LogN - 1; i + 1; i--) {
        if (f[a][i] != f[b][i]) {
            a = f[a][i];
            b = f[b][i];
        }
    }
    // dbg(514);
    // dbg(f[a][0]);
    return f[a][0];
}

} // namespace LCA

vecll as(BIGN);

class segment_tree final {
public:
    class node final {
    public:
        ll sum, ls, rs;
    };
    vec<node> tr;

private:
    ll n, ret;

    void update(ll x = 1) {
        if (tr[tr[x].ls].sum >= tr[tr[x].rs].sum) {
            as[x] = as[tr[x].ls];
            tr[x].sum = tr[tr[x].ls].sum;
        } else {
            as[x] = as[tr[x].rs];
            tr[x].sum = tr[tr[x].rs].sum;
        }
    }

public:
    explicit segment_tree(ll _n)
        : n(_n) {
        tr.resize(BIGN);
    }
    ll modify(ll l, ll r, ll col, ll v, ll x = 1) {
        if (!x) x = ++ret;
        if (l == r) {
            tr[x].sum += v;
            as[x] = col;
            return x;
        }
        ll mid = (l + r) >> 1;
        if (col <= mid)
            tr[x].ls = modify(l, mid, col, v, tr[x].ls);
        else
            tr[x].rs = modify(mid + 1, r, col, v, tr[x].rs);
        update(x);
        // dbg(x);
        return x;
    }
    ll merge(ll t1, ll t2, ll l, ll r) {
        if (!t1) return t2;
        if (!t2) return t1;
        if (l == r) {
            tr[t1].sum += tr[t2].sum;
            return t1;
        }
        ll mid = (l + r) >> 1;
        tr[t1].ls = merge(tr[t1].ls, tr[t2].ls, l, mid);
        tr[t1].rs = merge(tr[t1].rs, tr[t2].rs, mid + 1, r);
        update(t1);
        // dbg(t1);
        return t1;
    }
};
vecll roo(N);

void yuanshenqidong(segment_tree &tr, ll now = 1) {
    // dbg(now);
    for (ll i : g[now]) {
        if (f[now][0] != i) {
            yuanshenqidong(tr, i);
            roo[now] = tr.merge(roo[now], roo[i], 1, NN);
        }
    }
    ans[now] = (tr.tr[roo[now]].sum) ? (as[roo[now]]) : 0;
}

void solve() {
    cin >> n >> m;
    segment_tree tr(n);
    for (ll i = 1; i < n; i++) {
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }
    LCA::init(1);
    for (ll i = 1; i <= m; i++) {
        ll tmp, ttmp;
        cin >> a >> b >> va;
        // dbg(2);
        roo[a] = tr.modify(1, NN, va, 1, roo[a]);
        roo[b] = tr.modify(1, NN, va, 1, roo[b]);
        // dbg(1);
        tmp = LCA::lca(a, b);
        ttmp = f[tmp][0];
        roo[tmp] = tr.modify(1, NN, va, -1, roo[tmp]);
        roo[ttmp] = tr.modify(1, NN, va, -1, roo[ttmp]);
    }
    yuanshenqidong(tr, 1);
    for (ll i = 1; i <= n; i++) {
        cout << ans[i] << endl;
    }
}
} // namespace hellolin