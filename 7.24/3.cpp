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
int n;
ll a[N], dp[N][N];
ll dfs(ll l, ll r) {
    // fprintf(stderr, "l=%lld, r=%lld\n", l, r);
    ll tmp = l;
    ll qx=0, qy=0;
    if(l>=r) return dp[l][r] = 1;
    if(dp[l][r]) return dp[l][r];
    for(int i=l+1; i<=r; i++) {
        if(a[tmp] > a[i]) tmp = i;
    }
    for(int i=l; i<=tmp; i++) qx = (qx + dfs(l, i-1) * dfs(i, tmp-1) % mod_998) % mod_998;
    for(int i=tmp; i<=r; i++) qy = (qy + dfs(i+1, r) * dfs(tmp+1, i) % mod_998) % mod_998;
    return dp[l][r] = qx * qy % mod_998;
}
void solve() {
    std::cin >> n >> n;
    for(int i=1; i<=n; i++) std::cin >> a[i];
    std::cout << dfs(1, n) % mod_998 << '\n';
}
} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin), freopen(".out", "w", stdout);
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    hellolin::solve();
    return 0;
}