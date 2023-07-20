#ifndef HELLOLIN_EXTENSIONS_HPP
#define HELLOLIN_EXTENSIONS_HPP 1
#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>

#ifndef HELLOLIN_DISTRIBUTION_HPP
#define HELLOLIN_DISTRIBUTION_HPP
#include <algorithm>
#include <vector>

namespace hellolin {

template <class T>
class dist {
private:
    bool ready;
    std::vector<T> d;
    void init() {
        std::sort(d.begin(), d.end());
        d.erase(std::unique(d.begin(), d.end()), d.end());
        ready = 1;
    }

public:
    explicit dist()
        : ready(0) {}
    void push(T x) {
        d.emplace_back(x);
        ready = 0;
    }
    T distribute(T x) {
        if (!ready) init();
        return lower_bound(d.begin(), d.end(), x) - d.begin() + 1;
    }
    T tribute(T x) {
        if (!ready) init();
        return d[x - 1];
    }
    unsigned long long size() const {
        return d.size();
    }
    void clear() {
        d.clear();
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

    // int Ts; std::cin>>Ts; while(Ts--)
    hellolin::solve();

    return 0;
}

namespace hellolin {

constexpr static ll N = 1e6+10, INF = LONG_LONG_MAX;

dist<ll> qwq;
pair<ll, ll> st; // * 1: loc, 2: val.

class segment_tree final {
public:
    class node final {
    public:
        ll l, r, v;
        explicit node(ll _l = 0, ll _r = 0, ll _v = 0)
            : l(_l)
            , r(_r)
            , v(_v) {}
        bool operator<(const node &t) const {
            return (r == t.r) ? (l < t.l) : (r < t.r); //
        }
    };

private:
    ll n;
    vecll lz, mx, nt;
    // vecll a;

    void update(ll x = 1) {
        mx[x] = max(mx[x << 1], mx[x << 1 | 1]);
        if(mx[x<<1] > mx[x<<1|1]) nt[x] = nt[x<<1];
        else nt[x] = nt[x<<1|1];
    }
    void push_down(ll x = 1) {
        if (lz[x]) {
            lz[x << 1] += lz[x];
            lz[x << 1 | 1] += lz[x];
            mx[x << 1] += lz[x];
            mx[x << 1 | 1] += lz[x];
            lz[x] = 0;
        }
    }
    void build_tree(ll l, ll r, ll x = 1) {
        if (l == r) {
            nt[x] = l;
            mx[x] -= qwq.tribute(l);
            return;
        }
        ll mid = (l + r) >> 1;
        build_tree(l, mid, x << 1);
        build_tree(mid + 1, r, x << 1 | 1);
        update(x);
    }

public:
    explicit segment_tree(ll _n)
        : n(_n) {
        lz.resize(N << 2 | 1, 0), mx.resize(N << 2 | 1, 0), nt.resize(N << 2 | 1, 0);
        build_tree(1, n);
    }
    void modify(ll l, ll r, ll lx, ll rx, ll v, ll x = 1) {
        if (l <= lx && rx <= r) {
            lz[x] += v;
            mx[x] += v;
            return;
        }
        push_down(x);
        ll mid = (lx + rx) >> 1;
        if (l <= mid) modify(l, r, lx, mid, v, x << 1);
        if (mid < r) modify(l, r, mid + 1, rx, v, x << 1 | 1);
        update(x);
    }
    pair<ll, ll> query(ll l, ll r, ll lx, ll rx, ll x = 1) { // QAQ
        if (l <= lx && rx <= r) return {mx[x], nt[x]};
        push_down(x);
        pair<ll, ll> ans = {-INF, -INF};
        ll mid = (lx + rx) >> 1;
        if (l <= mid) chmax(ans, query(l, r, lx, mid, x << 1));
        if (mid < r) chmax(ans, query(l, r, mid + 1, rx, x << 1 | 1));
        return ans;
    }
};

ll n, x, y, c, ti;
vec<segment_tree::node> g;
vvec<pair<ll, ll>> p;
pair<ll, ll> ans;
// vecll a;
ll real_n, real_ans = -INF;
void solve() {
    cin >> n;
    // st._y = LONG_LONG_MIN;
    g.resize(N);
    p.resize(N);

    for (ll i = 1; i <= n; i++) {
        cin >> x >> y >> c;
        qwq.push(x), qwq.push(y);
        g[i] = segment_tree::node(min(x, y), max(x, y), c);
    }
    for (ll i = 1; i <= n; i++) {
        g[i].l = qwq.distribute(g[i].l), g[i].r = qwq.distribute(g[i].r);
        chmax(real_n, g[i].r);
        p[g[i].l].pb(make_pair(g[i].r, g[i].v));
        // p[g[i].r].pb(make_pair(g[i].l, g[i].v));
        // dbg(g[i].l);
    }
    segment_tree tr(real_n);


    for (ll i = real_n; i; i--) {
        // dbg(i);
        for (ll j = 0; j < (ll) p[i].size(); j++) {
            // dbg(j);
            auto w = p[i][j];
            // dbg(w._x), dbg(w._y);
            tr.modify(w._x, real_n, 1, real_n, w._y);
        }
        auto w = tr.query(i, real_n, 1, real_n);
        // dbg(w._x), dbg(w._y);
        ti = qwq.tribute(i);
        if (w._x + ti > real_ans) {
            real_ans = w._x + ti;
            ans = {qwq.tribute(i), qwq.tribute(w._y)};
        }
    }

    if (real_ans <= 0) {
        real_ans = 0;
        ans = {2e9-1, 2e9-1};
    }

    cout << real_ans << endl << ans._x << ' ' << ans._x << ' ' << ans._y << ' ' << ans._y << endl;
}
} // namespace hellolin