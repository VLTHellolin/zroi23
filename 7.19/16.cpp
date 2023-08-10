#include <cstdio>
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
#define FASTIO 1
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

namespace vars {

constexpr static ll N = 1e5 + 114, A = 16384, LogA = 14;

ll n, m, k, len;
ll tl, tr;
array<ll, N> bk, a, p, bt, ans;
vecll ek;

class node final {
public:
    ll l, r, col, v;
    node() {}
    explicit node(ll _l, ll _r, ll _col, ll _v)
        : l(_l)
        , r(_r)
        , col(_col)
        , v(_v) {}
};

class info final {
public:
    ll l, r;
    ll id, ret;
    bool operator<(const info &t) const {
        return bk[l] == bk[t.l] ? r < t.r : l < t.l;
    }
};

array<info, N> qwq;
array<vec<node>, N> g;
#define popcount __builtin_popcountll

} // namespace vars

using namespace vars;

namespace mo_algo {

void init() {
    len = n / sqrt(m);
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
        bk[i] = (i - 1) / len + 1;
    }
    for (ll i = 1; i <= m; i++) {
        qwq[i].id = i;
        cin >> qwq[i].l >> qwq[i].r;
    }
    sort(qwq.begin() + 1, qwq.begin() + 1 + m);
    for (ll i = 0; i < A; i++) {
        if (popcount(i) == k) ek.pb(i);
    }
    for (ll i = 1; i <= n; i++) {
        p[i] = bt[a[i]];
        for (ll j : ek) {
            ++bt[a[i] ^ j];
        }
    }
    fill(allof(bt), 0);
}

void main() {
    tl = 1,  tr = 0;
    for (ll i = 1; i <= m; i++) {
        if (tl > qwq[i].l) {
            g[tr].pb(qwq[i].l, tl - 1, i, 1);
        }
        while (tl > qwq[i].l) {
            --tl;
            qwq[i].ret -= p[tl];
        }
        if (tr < qwq[i].r) {
            g[tl - 1].pb(tr + 1, qwq[i].r, i, -1);
        }
        while (tr < qwq[i].r) {
            ++tr;
            qwq[i].ret += p[tr];
        }

        if (tl < qwq[i].l) {
            g[tr].pb(tl, qwq[i].l - 1, i, -1);
        }
        while (tl < qwq[i].l) {
            qwq[i].ret += p[tl];
            ++tl;
        }
        if (tr > qwq[i].r) {
            g[tl - 1].pb(qwq[i].r + 1, tr, i, 1);
        }
        while (tr > qwq[i].r) {
            qwq[i].ret -= p[tr];
            --tr;
        }
    }
}

} // namespace mo_algo

namespace scanning {

void main() {
    for (ll i = 1; i <= n; i++) {
        for (ll j : ek) {
            ++bt[a[i] ^ j];
        }
        for (auto w : g[i]) {
            for (ll j = w.l; j <= w.r; j++) {
                qwq[w.col].ret += w.v * (bt[a[j]] - (j <= i && !k));
            }
        }
    }

    for(ll i=1; i<=m; i++) {
        qwq[i].ret += qwq[i-1].ret;
        ans[qwq[i].id] = qwq[i].ret;
    }
}

} // namespace scanning

void solve() {
    cin >> n >> m >> k;
    if (k > LogA) {
        while (m--)
            cout << 0 << "\n";
        return;
    }
    mo_algo::init();
    mo_algo::main();
    scanning::main();
    for(ll i=1; i<=m; i++) cout << ans[i] << endl;
}
} // namespace hellolin