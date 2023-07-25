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

constexpr static ll N = 1e5 + 114;
ll n, mod, u, v;
std::vector<std::vector<ll>>g(N);
// std::vector<ll> tp;
ll dp[N][2], prep[N], sufp[N];

void dfs1(ll p, ll f) {
    ll orz = 1;
    // tp.clear();
    std::vector<ll> tp;
    dp[p][0] = 1;
    for(ll i : g[p]) {
        if(i!=f) {
            dfs1(i, p);
            tp.pb(i);
            dp[p][0] = dp[p][0] * (dp[i][0] + 1) % mod;
        }
    }
    for(ll i : tp) {
        prep[i] = orz;
        orz = orz * (dp[i][0] + 1) % mod;
    }
    orz = 1, reverse(allof(tp));
    for(ll i : tp) {
        sufp[i] = orz;
        orz = orz * (dp[i][0] + 1) % mod;
    }

}
void dfs2(ll p, ll f) {
    dp[p][1] = 1;

    if(~f) {
        dp[p][1] = dp[f][1];
        ll pro = prep[p] * sufp[p] % mod;
        dp[p][1] = (dp[p][1] * pro + 1) % mod;
    }
    for(ll i : g[p]) {
        if(i!=f) {
            dfs2(i, p);
        }
    }
}
void solve() {
    std::cin >> n >> mod;
    for(ll i=1; i<n; i++) {
        std::cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    dfs1(1, -1);
    dfs2(1, -1);
    for(ll i=1; i<=n; i++) std::cout << dp[i][0]*dp[i][1] % mod << '\n';
}
} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin), freopen(".out", "w", stdout);
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    hellolin::solve();
    return 0;
}