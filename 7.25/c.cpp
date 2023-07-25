// * HELLOLIN'S CP CODE TEMPLATE v2.0.1
#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>

namespace hellolin {
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

constexpr static int N = 4e5 + 114, A = 25, RealA = 20, _2_A = 1e6 + 114514, Real2_A = 1048576;
int n, a[N], tp, _, _____;
ll dp[_2_A], ans[A], pf[A][A];
void solve() {
    std::cin >> n;
    for(int i=1; i<=n; i++) {
        std::cin >> tp;
        for(int j=1; j<=RealA; j++) pf[j][tp] += ans[j];
        ++ans[tp];
        a[i] = tp;
    }
    memset(dp, INT_MAX, sizeof(dp));
    dp[0] = 0;
    for(int i=1; i<=Real2_A; i++) {
        for(int j=1; j<=RealA; j++) {
            if((i >> (j-1)) & 1) continue;
            _____ = 0;
            _ = i | (1 << (j-1));
            for(int k=1; k<=RealA; k++) {
                if(dp[])
            }
            chmin(dp[_], _____ + dp[i]);
        }
    }
    std::cout << --dp[Real2_A] << '\n';
}
} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin), freopen(".out", "w", stdout);
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    hellolin::solve();
    return 0;
}