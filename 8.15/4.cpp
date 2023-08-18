// * HELLOLIN'S CP CODE TEMPLATE v2.4.1
#include <cstdlib>
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
constexpr static int N = 2e4 + 114;
constexpr static int inf = 1e9;
int n, q, u, v;
ll ans;
// __gnu_pbds::priority_queue<std::pair<int, int>, std::greater<std::pair<int, int>>> pq;
std::queue<std::pair<int,ll>> Q;
std::vector<std::vector<std::pair<int, ll>>> g;
int dis[N][N];
bool vis[N]; 
void bfs(int x) {
    std::fill(dis[x]+1, dis[x]+1+n, inf);
    std::fill(vis+1, vis+1+n, 0);
    dis[x][x] = 0;
    Q.push({x, 0});
    while(Q.size()) {
        auto p = Q.front();
        Q.pop();
        vis[p.fi] = 1;
        chmin(dis[x][p.fi], p.se);
        for(auto i : g[p.fi]) {
            if(!vis[i.fi]) {
                Q.push({i.fi,p.se+1});
            }
        }
    }
}
void solve() {
    std::cin >> n >> q;
    g.resize(n+1);
    rep(int, i, 1, n) {
        per(int, j, i-1, 1) {
            g[i].pb(j, 1);
        }
    }
    rep(int, _q, 1, q) {
        std::cin >> u >> v;
        auto qwq = [&]() {
            for(auto it = g[v].begin(); it != g[v].end(); it++) {
                if((*it).fi == u) {
                    g[v].erase(it);
                    g[u].pb(v, 1);
                    return 1;
                    break;
                }
            }
            return 0;
        };
        if(!qwq()) {
            std::swap(u, v);
            qwq();
        }

        ans = 0;
        rep(int, i, 1, n) {
            bfs(i);
        }
        // rep(int, i, 1, n) {
        //     rep(int, j, 1, n) {
        //         std::cerr << dis[i][j] << " \n"[j==n];
        //     }
        // }
        rep(int, i, 1, n) {
            rep(int, j, i+1, n) {
                if(dis[i][j] != inf && dis[j][i] != inf) ++ans;
            }
        }
        std::cout << ans << nl;

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