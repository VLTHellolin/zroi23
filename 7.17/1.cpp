#ifndef HELLOLIN_EXTENSIONS_HPP
#define HELLOLIN_EXTENSIONS_HPP 1
#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>

#ifndef HELLOLIN_DSU_HPP
#define HELLOLIN_DSU_HPP 1
#include <algorithm>
#include <numeric>
#include <vector>

namespace hellolin {

template <class T>
class dsu {
private:
    unsigned long long n;
    std::vector<T> g, sz;

public:
    explicit dsu(unsigned long long _n = 0)
        : n(_n)
        , g(_n << 1)
        , sz(_n << 1, 1) {
        std::iota(g.begin(), g.begin() + n, n);
        std::iota(g.begin() + n, g.end(), n);
    }
    T find(T x) {
        return g[x] == x ? x : g[x] = find(g[x]);
    }
    T merge(T x, T y) {
        x = find(x);
        y = find(y);
        if (x == y) return -1;
        if (sz[x] < sz[y]) std::swap(x, y);
        sz[x] += sz[y];
        g[y] = x;
        return x;
    }
    bool same(T x, T y) {
        return find(x) == find(y);
    }
    void erase(T x) {
        --sz[find(x)];
        g[x] = x;
    }
    void move(T x, T y) {
        T xf = find(x), yf = find(y);
        if (xf == yf) return;
        --sz[xf], ++sz[yf];
        g[x] = yf;
    }
    
};

} // namespace hellolin

#endif

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

    int Ts; std::cin>>Ts; while(Ts--)
        hellolin::solve();

    return 0;
}

namespace hellolin {
constexpr static ll N = 1e16+10;
class info {
public:
    ll l, r, p;
    explicit info(ll _l = 0, ll _r = 0, ll _p = 0)
        : l(_l)
        , r(_r)
        , p(_p) {}
    bool operator<(const info&x) const {
        return p>x.p;
    }
};
ll n, mx;
bool ans;
// set<ll>s;
map<ll,ll>b;
vec<info> d;
void ls() {
    b.clear();
    mx = 0;
    for(ll i=1; i<=n; i++) {
        cin>>d[i].l>>d[i].r>>d[i].p;
        b[d[i].l] = ++mx;
        b[d[i].r] = ++mx;
    }
    for(ll i=1; i<=n; i++) {
        d[i].l = b[d[i].l];
        d[i].r = b[d[i].r];
    }
}
void solve() {
    cin >> n;
    d.resize(n+11);
    d.clear();
    ls();
    dsu<ll> g(mx + 1);
    sort(d.begin()+1, d.begin()+n+1);
    ans = 1;
    for(ll i=1; i<=n; i++) {
        if(d[i].p) {
            g.merge(d[i].l, d[i].r);

        } else {
            if(g.same(d[i].l, d[i].r)) {
                ans = 0;
                break;
            }
        }
    }
    YESNO(ans);
}
} // namespace hellolin