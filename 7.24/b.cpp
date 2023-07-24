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

constexpr static int N = 514;
int n, a[N];
int dp[N][N];

void solve() {
    std::cin >> n;
    for(int i=1; i<=n; i++) {
        std::cin >> a[i];
    }
    for(int i=1; i<=n; i++) for(int j=1; j<=n; j++) dp[i][j] = 5141145;
    for(int i=1; i<=n; i++) dp[i][i] = 1;
    for(int i=1; i<n; i++) {
        dp[i][i+1] = (a[i]!=a[i+1]) + 1;
    }

    for(int i=3; i<=n; i++) {
        for(int j=1; j<=n-i+1; j++) {
            int l = j, r = j+i-1;
            if(a[l] == a[r]) dp[l][r] = dp[l+1][r-1];
            for(int k=l; k<r; k++) chmin(dp[l][r], dp[l][k] + dp[k+1][r]);
        }
    }
    std::cout << dp[1][n] << '\n';
}
} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin), freopen(".out", "w", stdout);
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    hellolin::solve();
    return 0;
}