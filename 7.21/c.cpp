#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>

#ifndef HELLOLIN_DISTRIBUTION_HPP
#define HELLOLIN_DISTRIBUTION_HPP 1
#include <algorithm>
#include <vector>

namespace hellolin {

template <class T>
class distribution {
    using st = size_t;

private:
    bool ready;
    std::vector<T> d;
    void init() {
        std::sort(d.begin(), d.end());
        d.erase(std::unique(d.begin(), d.end()), d.end());
        ready = 1;
    }

public:
    explicit distribution()
        : ready(0) {}
    void push(T x) {
        d.emplace_back(x);
        ready = 0;
    }
    st distribute(T x) {
        if (!ready) init();
        return std::lower_bound(d.begin(), d.end(), x) - d.begin() + 1;
    }
    T tribute(st x) {
        if (!ready) init();
        return d[x - 1];
    }
    st size() {
        return d.size();
    }
    void clear() {
        d.clear();
    }
};

} // namespace hellolin

#endif

namespace hellolin {
using ll = long long;
using ull = unsigned long long;
using lll = __int128;
template <class T> using min_pq = __gnu_pbds::priority_queue<T, std::greater<T>, __gnu_pbds::pairing_heap_tag>;
template <class T> using max_pq = __gnu_pbds::priority_queue<T, std::less<T>, __gnu_pbds::pairing_heap_tag>;
template <class T> using vec = std::vector<T>;
using vecll = vec<ll>;
template <class T> using vvec = vec<vec<T>>;
using vvecll = vec<vec<ll>>;
constexpr static ull mod_1e97 = 1e9 + 7, mod_998 = 998244353, mod_1e18 = 1e18, inf = LONG_LONG_MAX;
template <class T, class U> bool chmax(T &x, U y) { bool f = y > x; if(f) x = y; return f; }
template <class T, class U> bool chmin(T &x, U y) { bool f = y < x; if(f) x = y; return f; }
#define _x first
#define _y second
#define allof(x) x.begin(), x.end()
#define alllof(x) x.begin() + 1, x.end()
#define pb emplace_back
#define dbg(x) std::cerr << __LINE__ << ": " << #x << " = " << x << '\n'

constexpr static ll N = 2e5 + 11, RT = 41;

distribution<ll> dist;
vecll roo;

class segment_tree {
public:
    class tree_node final {
    public:
        ll ls, rs, sum;
        explicit tree_node(ll _s = 0)
            : sum(_s) {};
    };

private:
    vec<tree_node> tr;
    vecll a;
    ll all, n;

public:
    segment_tree() {}
    explicit segment_tree(ll _n, vecll _a)
        : n(_n)
        , a(_a) {
        roo.resize(N);
        tr.resize(N * RT);
    }
    // void create_node(ll x) {
        
    // }
    void insert(ll &l, ll r, ll lx, ll rx, ll p) {
        l = ++all;
        tr[l]=tr[r];
        ++tr[l].sum;
        if(lx==rx) return;
        ll mid = (lx + rx) >> 1;
        if (p <= mid) insert(tr[l].ls, tr[r].ls, lx, mid, p);
        else insert(tr[l].rs, tr[r].rs, mid+1, rx, p);
    }
    ll query(ll l, ll r, ll lx, ll rx, ll p) {
        if(lx==rx) {
            return lx;
        }
        ll mid = (lx+rx) >> 1;
        ll pyl = tr[tr[l].ls].sum - tr[tr[r].ls].sum;
        if(p <= pyl) return query(tr[l].ls, tr[r].ls, lx, mid, p);
        return query(tr[l].rs, tr[r].rs, mid+1, rx, p - pyl);
    }

};

vecll a;
ll n, m, x, y, k, real_n;
void solve() {
    std::cin >> n >> m;
    a.resize(n+1);
    for(ll i=1; i<=n; i++) {
        std::cin >> a[i];
        dist.push(a[i]);
    }
    for(ll i=1; i<=n; i++) {
        a[i] = dist.distribute(a[i]);
    }
    real_n = dist.size();
    segment_tree tr(n,a);
    for(ll i=1; i<=n; i++) {
        tr.insert(roo[i], roo[i-1], 1, real_n, a[i]);
    }
    for(ll i=1; i<=m; i++) {
        std::cin >> x >> y >> k;
        std::cout << dist.tribute(tr.query(roo[y], roo[x-1], 1, real_n, k)) << '\n';
    }
}
} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin), freopen(".out", "w", stdout);
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    hellolin::solve();
    return 0;
}