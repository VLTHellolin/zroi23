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

constexpr static int N = 5141;
constexpr static ll inf = 114514191981011451;
int n, m;
ll x[N];
std::pair<ll, ll> h[N];
ll dp[N][N], pres[N], press[N], que[N];
ll tp[N], qtop, qbot;

void solve() {
    auto pr = [&](const std::pair<ll,ll>&a, const std::pair<ll,ll>&b){return a.se+b.se;};
    std::cin >> n >> m;
    for(int i=1; i<=n; i++) dp[0][i] = inf;
    for(int i=1; i<=n; i++) std::cin >> x[i];
    // mT = std::accumulate(x+1, x+1+n, 0ll);
    for(int i=1; i<=m; i++) {
        std::cin >> h[i].fi >> h[i].se;
    }
    // hT = std::accumulate(h+1, h+1+n, 0ll, pr);
    std::sort(x+1, x+1+n);
    std::sort(h+1, h+1+m);
    for(int i=1; i<=m; i++) pres[i] = pres[i-1] + h[i].se;
    // std::partial_sum(h+1, h+1+m, pres+1, pr);
    if(n>pres[m]) {
        std::cout << -1 << '\n';
        return;
    }
    for(int i=1; i<=m; i++) {
        qbot = 1, qtop = 0;
        for(int j=1; j<=n; j++)
            press[j] = press[j-1] + abs(x[j] - h[i].fi);
        for(int j=0; j<=n; j++) {
            while(qtop >= qbot && que[qbot] < j - h[i].se) ++qbot;
            while(qtop >= qbot && dp[i-1][j] <= tp[qtop] + press[j]) --qtop;
            que[++qtop] = j;
            tp[qtop] = dp[i-1][j] - press[j];
            dp[i][j] = pres[i] < j ? inf : press[j] + tp[qbot];
        }
        std::cerr << qbot << ' ' << qtop << '\n';
    }
    if(dp[m][n] == inf) dp[m][n] = -1; 
    std::cout << dp[m][n] << '\n';

}
} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin), freopen(".out", "w", stdout);
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    hellolin::solve();
    return 0;
}