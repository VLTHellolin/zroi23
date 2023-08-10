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
    std::vector<T> g;

public:
    explicit dsu(unsigned long long _n = 0)
        : n(_n)
        , g(_n + 1) {
        for (unsigned long long i = 1; i <= n; i++) {
            g[i] = i;
        }
    }
    T find(T x) {
        return g[x] == x ? x : g[x] = find(g[x]);
    }
    void merge(T x, T y) {
        x = find(x);
        y = find(y);
        // if (x == y) return;
        // if (sz[x] < sz[y]) std::swap(x, y);
        // sz[x] += sz[y];
        g[x] = y;
        // return x;
    }
    // bool same(T x, T y) {
    //     return find(x) == find(y);
    // }
    // void erase(T x) {
    //     --sz[find(x)];
    //     g[x] = x;
    // }
    // void move(T x, T y) {
    //     T xf = find(x), yf = find(y);
    //     if (xf == yf) return;
    //     --sz[xf], ++sz[yf];
    //     g[x] = yf;
    // }
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
void pre();
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
    hellolin::pre();
    long long Ts;
    std::cin >> Ts;
    while (Ts--)
        hellolin::solve();
#else
    hellolin::solve();
#endif

    return 0;
}

namespace hellolin { // ! 我不理解！！！！！！！！！

#define ll int

namespace vars {

constexpr static ll N = 1e5 + 114, Sn = 320, RealN = 1e5;

array<ll, Sn> ls, rs;
array<ll, N> id;
set<ll> beg, end;
array<dsu<ll>, Sn> d;

class block final {
private:
    array<long long, N> v;
    array<long long, Sn> lz;

public:
    void modify(ll x, ll val) { // ? OK
        for (ll i = x; i <= rs[id[x]]; i++)
            v[i] += val;
        for (ll i = id[x] + 1; i < Sn; i++)
            lz[i] += val;
        // dbg(rs[id[p]]), dbg(p);
    }
    long long query(ll l, ll r) { // ? OK
        if (l > r) return 0;
        return v[r] - v[l - 1] + lz[id[r]] - lz[id[l - 1]];
    }
} b1, all;

ll Ts;
ll op, x, y, z;
ll aft, bef;
ll sum, ans, tt;
bool failed;

} // namespace vars

using namespace vars;

void pre() { // ? OK
    for (auto &i : d) {
        i = dsu<ll>(N + Sn + 114);
    }
    for (ll i = 1; i <= RealN; i++)
        id[i] = i / Sn;
    for (ll i = 0; i <= id[RealN]; i++) {
        ls[i] = max(i * Sn, (ll) 1);
        rs[i] = min((i + 1) * Sn - 1, RealN);
        // dbg(ls[i]), dbg(rs[i]);
    }
    beg.insert(-1000000145), beg.insert(1000000145);
    /* end.insert(-inf), */ end.insert(1000000145);
}
void solve() {
    pre();
    cin >> Ts;
    while (Ts--) {
        cin >> op;
        if (op == 1) { // ? OK
            ll x, y;
            cin >> x >> y;
            b1.modify(x, 1), all.modify(x, y);
            if (!y) {
                auto tp = beg.lower_bound(x);
                ll aft = *tp, bef = *(--tp);
                for (ll i = 1; i < Sn; i++) {
                    ll awa = max({bef, x - i, (ll) 0});
                    ll qwq = min(x - 1, aft - 1 - i);
                    for (ll j = awa; j <= qwq; j++)
                        d[i].merge(j, j + i);
                }
                beg.insert(x);
                dbg(bef), dbg(aft);
                continue;
            }
            end.insert(x);
        } else { // ? OK
            ll z;
            cin >> z;
            // failed = 0;
            ll sum = 0, ans = 0;
            // while(x) {
            // while (!failed) {
            while (1) {
                failed = 1;
                if (z < Sn) {
                    ll tp = *end.upper_bound(sum);
                    ll QWQ = min(d[z].find(sum), (tp - sum - 1) / z * z + sum);
                    ans += (QWQ - sum) / z;
                    sum = QWQ;
                    // continue;
                    dbg(tp), dbg(QWQ);
                }
                ++ans;
                ll tt = b1.query(sum + 1, min(RealN, z + sum));
                // dbg(tt);
                if (tt) {
                    long long QAQ = all.query(sum + 1, min(RealN, z + sum));
                    dbg(QAQ);
                    if (z > QAQ) {
                        sum += z;
                        z -= QAQ;
                        failed = 0;
                    }
                }

                if (failed) break;
                dbg(sum), dbg(ans);
            }
            cout << ans << endl;
        }
    }
}
} // namespace hellolin