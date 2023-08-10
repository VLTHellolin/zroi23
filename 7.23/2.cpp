#include <numeric>
#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>
#include <bits/stdc++.h>

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
template <class T> using min_pq = __gnu_pbds::priority_queue<T, std::greater<T>>;
template <class T> using max_pq = __gnu_pbds::priority_queue<T, std::less<T>>;
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
#define allnof(x, n) x.begin(), x.begin() + n + 1
#define alllnof(x, n) x.begin() + 1, x.begin() + n + 2
#define pb emplace_back
#define dbg(x) std::cerr << __LINE__ << ": " << #x << " = " << x << '\n'

constexpr static int N = 25 * 1e4 + 11, Gr = 5555;
int n, x[N], y[N], xM, yM, xI, yI;
ll w[N], ans, now;
// class point {
// public:
//     int x,y;
//     ll w;
//     explicit point(int _x = 0, int _y = 0, ll _w = 0)
//         : x(_x)
//         , y(_y)
//         , w(_w) {}
// // };
// point r[N];
int r[Gr][Gr];
ll qz[Gr][Gr], qzz[Gr][Gr];
vec<int> Xs, Ys;
int is, js;
distribution<int> clbzdq;

void solve() {
    std::cin >> n;
    xI = yI = INT_MAX - 1;
    for(int i=1; i<=n; i++) {
        std::cin >> x[i] >> y[i] >> w[i];
        clbzdq.push(x[i]), clbzdq.push(y[i]);
    }
    for(int i=1; i<=n; i++) {
        x[i] = clbzdq.distribute(x[i]);
        y[i] = clbzdq.distribute(y[i]);
        r[x[i]][y[i]] += w[i];
        chmax(xM, x[i]), chmax(yM, y[i]);
        chmin(xI, x[i]), chmin(yI, y[i]);
        // r[i] = point(x, y, w);
        Xs.pb(x[i]), Ys.pb(y[i]);
    }
    std::sort(allof(Xs)), std::sort(allof(Ys));
    Xs.erase(std::unique(allof(Xs)), Xs.end());
    Ys.erase(std::unique(allof(Ys)), Ys.end());
    for(int i=xI; i<=xM; i++) {
        for(int j=yI; j<=yM; j++) {
            qz[i][j] = qz[i][j-1] + r[i][j];
        }
    } 
    for(int i=yI; i<=yM; i++) {
        for(int j=xI; j<=xM; j++) {
            qzz[j][i] = qzz[j-1][i] + qz[j][i];
            // dbg(j), dbg(i), dbg(qzz[j][i]);
        }
    }
    for(int i=0; i<(int)Xs.size(); i++) {
        is = Xs[i];
        for(int j=i; j<(int)Xs.size(); j++) {
            js = Xs[j];
            for(int ks : Ys) {
                now = qzz[js][ks] - qzz[is-1][ks];
                chmax(ans,now);
            }
        }
    }
    std::cout << ans << '\n';
}
} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin), freopen(".out", "w", stdout);
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    hellolin::solve();
    return 0;
}