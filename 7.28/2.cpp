// * HELLOLIN'S CP CODE TEMPLATE v2.1.1
#ifndef ONLINE_JUDGE
#pragma GCC optimize(2, "inline", "unroll-loops", "no-stack-protector", "-ffast-math")
#endif
#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>

namespace hellolin {
namespace lib {
using ll = long long;
using ull = unsigned long long;
using lll = __int128;
using ld = long double;
constexpr static ull mod_1e97 = 1e9 + 7, mod_998 = 998244353, mod_1e18 = 1e18;
template <class T, class U> inline bool chmax(T &x, U y) { return y > x ? (x = y, 1) : 0; }
template <class T, class U> inline bool chmin(T &x, U y) { return y < x ? (x = y, 1) : 0; }
#define fi first
#define se second
#define allof(x) x.begin(), x.end()
#define alof(x) x.begin() + 1, x.end()
#define allnof(x, n) x.begin(), x.begin() + n + 1
#define alnof(x, n) x.begin() + 1, x.begin() + n + 2
#define pb emplace_back
}
using namespace lib;
namespace DS {

}

constexpr static ll N = 1e5 + 11;
ll n;
ll a[N], acc;
ld ave;
ll now, noww;
void solve() {
    std::cout << std::fixed << std::setprecision(8);
    std::cin >> n;
    for(ll i=1; i<=n; i++) {
        std::cin >> a[i];
    }
    acc = std::accumulate(a+1, a+1+n, 0ll);
    ave = acc * 1.0 / (n+1);
    std::cout << ave * 2 << ' ';
    for(ll i=2; i<=n; i++) std::cout << ave << " \n"[i==n];
    // for(ll i=1; i<=n; i++) std::cout << a[i] << " \n"[i==n];
}
} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin), freopen(".out", "w", stdout);
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    hellolin::solve();
    return 0;
}