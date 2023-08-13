// * HELLOLIN'S CP CODE TEMPLATE v2.2.3
#ifndef ONLINE_JUDGE
#pragma GCC optimize(2, "inline", "unroll-loops", "no-stack-protector", "-ffast-math")
#endif
#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>
#include <bits/stdc++.h> // * FIX GCC 5.0

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
inline std::string yesno(bool x, int y) { return yesno_str[x][y] + '\n'; }
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

constexpr static int N = 5e4 + 11, M = 5e5 + 11;

int n, a[N], k, q;
__gnu_pbds::priority_queue<std::pair<ll, int>, std::greater<std::pair<ll,int>>> pq;
ll dis[M];
bool vis[M];
void dij(int s) {
    std::fill(dis+1, dis+M, inf * 100);
    std::fill(vis+1, vis+1+n, 0);
    dis[s] = 0;
    pq.push({dis[s], s});
    while(pq.size()) {
        int tp = pq.top().se;
        pq.pop();
        if(!vis[tp]) vis[tp] = 1;
        else continue;
        for(int i=2; i<=n; i++) {
            ll w = a[i];
            int j = (tp + w) % a[1];
            if(dis[j] > dis[tp] + w) {
                dis[j] = dis[tp] + w;
                pq.push({dis[j], j});
            }
        }
    }
}
void solve() {
    std::cin >> n;
    rep(int, i, 1, n) std::cin >> a[i];
    dij(0);
    std::cin >> k;
    rep(int, i, 1, k) {
        std::cin >> q;
        std::cout << (dis[q % a[1]] <= q ? "TAK\n" : "NIE\n");
    }
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