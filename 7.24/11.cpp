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

constexpr static int N = 6e3 + 11;
int n, dp[N][2], roo, fa[N], head[N], nxt[N], r[N];
bool deg[N];
int u, v;

void do_dp(int p) {
    for(int i=head[p]; ~i; i = nxt[i]) {
        do_dp(i);
        chmax(dp[p][0], std::max({dp[i][0], dp[i][1], dp[i][1] + dp[p][0]}));
        chmax(dp[p][1], std::max(dp[i][0], dp[i][0] + dp[p][1]));
    }
}

void solve() {
    std::cin >> n;
    memset(nxt, -1, sizeof(nxt)), memset(head, -1, sizeof(nxt));
    for(int i=1; i<=n; i++) {
        std::cin >> r[i];
        dp[i][1] = r[i];
    }
    for(int i=1; i<n; i++) {
        std::cin >> u >> v;
        std::swap(u, v); // * 反向存边
        deg[v] = 1;
        nxt[v] = head[u];
        head[u] = v;
    }
    for(int i=1; i<=n; i++) {
        if(!deg[i]) {
            roo = i;
            break;
        }
    }
    do_dp(roo);
    std::cout << std::max(dp[roo][0], dp[roo][1]) << '\n';
}
} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin), freopen(".out", "w", stdout);
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    hellolin::solve();
    return 0;
}