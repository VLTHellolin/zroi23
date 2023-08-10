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

constexpr static int N = 1e5 + 11;
int n, u, v;
std::vector<std::vector<int>>g(N);
ll dp[N][2], w[N];

void dfs(int p, int f) {
    for(int i : g[p]) {
        if(i!=f) {
            dfs(i, p);
            chmax(dp[p][0], dp[i][0]);
            chmax(dp[p][1], dp[i][1]);
        }
    }
    if(dp[p][0] + w[p] > dp[p][1]) dp[p][1] = dp[p][0] + w[p];
    else dp[p][0] = dp[p][1] - w[p];
}

void solve() {
    std::cin >> n;
    for(int i=1; i<n; i++) {
        std::cin >> u >> v;
        g[u].pb(v), g[v].pb(u);
    }
    for(int i=1; i<=n; i++) {
        std::cin >> w[i];
    }
    dfs(1, -1);
    std::cout << dp[1][0] + dp[1][1] << '\n';
}
} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin), freopen(".out", "w", stdout);
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    hellolin::solve();
    return 0;
}