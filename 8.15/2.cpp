// * HELLOLIN'S CP CODE TEMPLATE v2.4.1
#ifndef ONLINE_JUDGE
#pragma GCC optimize(2, "inline", "unroll-loops", "no-stack-protector", "-ffast-math")
#endif
#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>
#include <bits/stdc++.h> // * FIX GCC 5.0
#ifdef LOCAL
#include <windows.h>
#include <psapi.h>
#endif

namespace hellolin {
namespace lib {
using ll = long long;
using ull = unsigned long long;
using lll = __int128;
using ulll = __uint128_t;
const static std::string yesno_str[2][3] = {{"no", "No", "NO"}, {"yes", "Yes", "YES"}};
inline std::string yesno(bool x, int y) { return yesno_str[x][y] + '\n'; }
template <class T> inline T fpow(T x, ull y, T mod) { T res = 1; for(; y; y >>= 1, x = x * x % mod) if(y & 1) res = res * x % mod; return res; }
template <class T, class U> inline bool chmax(T &x, U y) { return y > x ? (x = y, 1) : 0; }
template <class T, class U> inline bool chmin(T &x, U y) { return y < x ? (x = y, 1) : 0; }
#define rep(l, x, a, b) for (l x = a, x##END = b; x <= x##END; ++x)
#define per(l, x, a, b) for (l x = a, x##END = b; x >= x##END; --x)
#define fi first
#define se second
#define allof(x) x.begin(), x.end()
#define alof(x) x.begin() + 1, x.end()
#define allnof(x, n) x.begin(), x.begin() + n + 1
#define alnof(x, n) x.begin() + 1, x.begin() + n + 2
#define lowbit(x) (x & -x)
#define mp make_pair
#define pb emplace_back
#define nl '\n'
} // namespace lib
using namespace lib;

// * CORE CODE BEGIN * //

constexpr static int inf = 1e9, N = 11451;
// __gnu_pbds::priority_queue<std::pair<ll, int>, std::greater<std::pair<ll, int>>> pq;
std::queue<std::pair<int,ll>> q;
ll n, m, ans, now;
std::vector<std::vector<std::pair<int, ll>>> g;
ll dis[N];
bool vis[N]; 
char tp;
void bfs(int x) {
    std::fill(dis+1, dis+1+n, inf);
    std::fill(vis+1, vis+1+n, 0);
    dis[x] = 0;
    q.push({x, 0});
    while(q.size()) {
        auto p = q.front();
        q.pop();
        vis[p.fi] = 1;
        chmin(dis[p.fi], p.se);
        for(auto i : g[p.fi]) {
            if(!vis[i.fi]) {
                q.push({i.fi,p.se+1});
            }
        }
    }
}

int T;
void solve() {
    for(std::cin >> T; T--; ) {
        std::cin >> n;
        // m = 0;
        g.clear();
        g.resize(n+1);
        rep(int, i, 1, n) {
            rep(int, j, 1, n) {
                std::cin >> tp;
                if(tp == '1') {
                    // ++m;
                    g[i].pb(j, 1);
                }
            }
        }
        ans = (ll)inf * 100ll;
        rep(int, u, 1, n) {
            bfs(u);
            now = 0;
            rep(int, v, 1, n) {
                chmax(now, dis[v]);
                // std::cerr << dis[v] << ' ';
            }
            // std::cerr << '\n';
            chmin(ans, now);
        }
        std::cout << ans << '\n';
    }
}
// * CORE CODE END * //

} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    // freopen(".dbg", "w", stderr);
#ifdef LOCAL
    clock_t st = clock(), ed;
#endif
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    // std::cout << std::fixed << std::setprecision(6);
    std::cerr << std::fixed << std::setprecision(6);
    hellolin::solve();
#ifdef LOCAL
    ed = clock();
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    std::cerr << "---------- DEBUG INFO ----------\n";
    std::cerr << "Time: " << (long double)(ed - st) / CLOCKS_PER_SEC << "s.\n";
    std::cerr << "Memory: " << pmc.WorkingSetSize / 1000000 << "MB.\n";
#endif
    return 0;
}