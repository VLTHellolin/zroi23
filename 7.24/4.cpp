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

constexpr static int N = 54;
int n;
int dp[N][N][N][N];
char tp;
bool q[N][N];

int dfs(std::pair<int,int>p1, std::pair<int,int>p2) {
    int &p = dp[p1.fi][p1.se][p2.fi][p2.se];
    if(~p) return p;
    if(p1 == p2) {
        return p = q[p1.fi][p2.se];
    }
    int res = std::max(p2.fi - p1.fi + 1, p2.se - p1.se + 1);
    for(int i=p1.fi; i<p2.fi; i++) {
        chmin(res, dfs(p1, {i, p2.se}) + dfs({i+1, p1.se}, p2));
    }
    for(int i=p1.se; i<p2.se; i++) {
        chmin(res, dfs(p1, {p2.fi, i}) + dfs({p1.fi, i+1}, p2));
    }
    return p = res;
}

void solve() {
    std::cin >> n;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            std::cin >> tp;
            q[i][j] = tp == '#';
        }
        
    }
    memset(dp, -1, sizeof(dp));
    std::cout << dfs({1,1}, {n,n}) << '\n';
}
} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin), freopen(".out", "w", stdout);
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    hellolin::solve();
    return 0;
}