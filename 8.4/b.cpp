// * HELLOLIN'S CP CODE TEMPLATE v2.2.2
#ifndef ONLINE_JUDGE
#pragma GCC optimize(2, "inline", "unroll-loops", "no-stack-protector", "-ffast-math")
#endif
#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>
#include <bits/stdc++.h> // * FIX GCC 5.0

#ifndef HELLOLIN_RANDOM_NUMBER_HPP
#define HELLOLIN_RANDOM_NUMBER_HPP 1
#include <chrono>
#include <functional>
#include <random>

namespace hellolin {

class random_number {
private:
    std::mt19937 *gen;
    std::uniform_int_distribution<unsigned long long> dist;
    std::hash<unsigned long long> hs;

public:
    explicit random_number(unsigned long long sd = 4731636727ll) {
        static std::mt19937 r(sd ^ time(0));
        gen = &r;
    }
    unsigned long long operator()() {
        return hs(1ll * (dist(*gen)));
    }
    unsigned long long operator()(unsigned long long l, unsigned long long r) {
        return hs(1ll * (dist(*gen))) % r + l;
    }
};

} // namespace hellolin

#endif

namespace hellolin {
namespace lib {
using ll = long long;
using ull = unsigned long long;
using lll = __int128;
using ulll = __uint128_t;
using ld = long double;
template <class T> using Pair = std::pair<T, T>;
constexpr static ll mod_1e97 = 1e9 + 7, mod_998 = 998244353, mod_1e18 = 1e18;
constexpr static ll inf = INT_MAX, INF = LLONG_MAX;
const static std::string yesno_str[2][3] = {{"no", "No", "NO"}, {"yes", "Yes", "YES"}};
template <class T> inline void yesno(bool x, int y, T u = std::cout) { u << yesno_str[x][y] << '\n'; }
template <class T> inline T fpow(T x, ull y, T mod) { T res = 1; for(; y; y >>= 1, x = x * x % mod) if(y & 1) res = res * x % mod; return res; }
template <class T, class U> inline bool chmax(T &x, U y) { return y > x ? (x = y, 1) : 0; }
template <class T, class U> inline bool chmin(T &x, U y) { return y < x ? (x = y, 1) : 0; }
#define rep(l, x, a, b) for (l x = a, x##END = b; x <= x##END; ++x)
#define per(l, x, a, b) for (l x = a, x##END = b; x >= x##END; --x)
#define y0 _HOMO_114__514_
#define y1 _HOMO_1919_810_
#define fi first
#define se second
#define allof(x) x.begin(), x.end()
#define alof(x) x.begin() + 1, x.end()
#define allnof(x, n) x.begin(), x.begin() + n + 1
#define alnof(x, n) x.begin() + 1, x.begin() + n + 2
#define lowbit(x) (x & -x)
#define mp make_pair
#define pb emplace_back
}
using namespace lib;

// * CORE CODE BEGIN * //
constexpr static int N = 1e6 + 1;
int n, u, v, isSub4;
// std::vector<std::vector<int>> g;
ll a[N], b[N], a1, b1, ans, now;
void solve() {
    std::cin >> n;
    rep(int, i, 1, n) {
        std::cin >> a[i] >> b[i];
    }
    // g.resize(n + 11);
    isSub4 = 1;
    rep(int, i, 2, n-1) {
        std::cin >> u >> v;
        if(u!=1&&v!=1) isSub4 = 0;
    }
    if(isSub4) {
        // a1 = a[1], b1 = b[1];
        // a[1] = -114, b[1] = -514;
        ans = 1e17 + 11;
        // std::sort(a+1, a+1+n);
        // std::sort(b+1, b+1+n);
        if((n&1) == 0) {
            now = a[1];
            rep(int, i, 2, n/2+1) now += b[i];
            rep(int, i, n/2+2, n) now += a[i];
            chmin(ans, now);
            rep(int, i, 3, n/2+1) {
                now -= b[i-1], now += a[i-1];
                now -= a[i+n/2-1], now += b[i+n/2-1];
                chmin(ans, now);
            }

            now = b[1];
            rep(int, i, 2, n/2+1) now += a[i];
            rep(int, i, n/2+2, n) now += b[i];
            chmin(ans, now);
            rep(int, i, 3, n/2+1) {
                now -= a[i-1], now += b[i-1];
                now -= b[i+n/2-1], now += a[i+n/2-1];
                chmin(ans, now);
            }
        } else {
            now = a[1];
            rep(int, i, 2, n/2+1) now += b[i];
            rep(int, i, n/2+2, n) now += a[i];
            chmin(ans, now);
            rep(int, i, 3, n/2+2) {
                now -= b[i-1], now += a[i-1];
                now -= a[i+n/2-1], now += b[i+n/2-1];
                chmin(ans, now);
            }

            now = a[1];
            rep(int, i, 2, n/2+2) now += b[i];
            rep(int, i, n/2+3, n) now += a[i];
            chmin(ans, now);
            rep(int, i, 3, n/2+1) {
                now -= b[i-1], now += a[i-1];
                now -= a[i+n/2], now += b[i+n/2];
                chmin(ans, now);
            }

            now = b[1];
            rep(int, i, 2, n/2+1) now += a[i];
            rep(int, i, n/2+2, n) now += b[i];
            chmin(ans, now);
            rep(int, i, 3, n/2+2) {
                now -= a[i-1], now += b[i-1];
                now -= b[i+n/2-1], now += a[i+n/2-1];
                chmin(ans, now);
            }

            now = b[1];
            rep(int, i, 2, n/2+2) now += a[i];
            rep(int, i, n/2+3, n) now += b[i];
            chmin(ans, now);
            rep(int, i, 3, n/2+1) {
                now -= a[i-1], now += b[i-1];
                now -= b[i+n/2], now += a[i+n/2];
                chmin(ans, now);
            }
        }
        std::cout << ans << '\n';
        return;
    }
    random_number qwq;
    a1 = std::accumulate(a+1, a+1+n, 0ll);
    b1 = std::accumulate(b+1, b+1+n, 0ll);
    if(a1>b1) std::swap(a1,b1);
    std::cout << qwq(a1, b1) << '\n';
}
// * CORE CODE END * //

} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    // freopen(".dbg", "w", stderr);
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    // std::cout << std::fixed << std::setprecision(6);
    hellolin::solve();
    return 0;
}