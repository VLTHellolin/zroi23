// * HELLOLIN'S CP CODE TEMPLATE v2.2.2
#ifndef ONLINE_JUDGE
#pragma GCC optimize(2, "inline", "unroll-loops", "no-stack-protector", "-ffast-math")
#endif
#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>

#ifndef HELLOLIN_GRAPH_TWO_SAT_HPP
#define HELLOLIN_GRAPH_TWO_SAT_HPP 1
#include <algorithm>
#include <stack>
#include <vector>

namespace hellolin {

namespace graph {

class two_sat {
    using st = size_t;

private:
    bool ready;
    st n;
    int tot, scc;
    std::vector<bool> ans, vis;
    std::stack<int> q;
    std::vector<std::vector<int>> g;
    std::vector<int> low, dfn, topo;

public:
    explicit two_sat(st _n)
        : n(_n)
        , ready(0) {
        ans.resize(n + 1);
        g.resize((n << 1) + 2);
        low.resize((n << 1) + 2);
        dfn.resize((n << 1) + 2);
        topo.resize((n << 1) + 2);
        vis.resize((n << 1) + 2);
    }
    void add_clause(int x, bool xv, int y, bool yv) {
        ready = 0;
        g[x + n * (xv & 1)].push_back(y + n * (yv ^ 1));
        g[y + n * (yv & 1)].push_back(x + n * (xv ^ 1));
    }
    bool query() {
        ready = 1;
        auto tarjan = [&](auto fun, int x) -> void {
            low[x] = dfn[x] = ++tot;
            vis[x] = 1;
            q.push(x);
            for (int y : g[x]) {
                if (!dfn[y]) {
                    fun(fun, y);
                    low[x] = std::min(low[x], low[y]);
                } else if (vis[y]) {
                    low[x] = std::min(low[x], dfn[y]);
                }
            }
            if (low[x] == dfn[x]) {
                ++scc;
                do {
                    topo[x] = scc;
                    x = q.top(), q.pop();
                    vis[x] = 0;
                } while (low[x] != dfn[x]);
            }
        };
        for (int i = 1; i <= (n << 1); i++)
            if (!dfn[i]) tarjan(tarjan, i);
        for (int i = 1; i <= n; i++)
            if (topo[i] == topo[n + i]) return 0;
        for (int i = 1; i <= n; i++)
            ans[i] = topo[i] < topo[n + i];
        return 1;
    }
    std::vector<bool> get_ans() {
        if (!ready) query();
        return ans;
    }
};

} // namespace graph

} // namespace hellolin

#endif

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
template <class T> inline void yesno(bool x, int y, T u = std::cout) { u << yesno_str[x][y] << '\n'; }
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
int n, m;
int a, b, c, d;
bool ok;
void solve() {
    std::cin >> n >> m;
    graph::two_sat t(n);
    rep(int,i,1,m) {
        std::cin >> a >> b >> c >> d;
        t.add_clause(a, b, c, d);
    }
    ok = t.query();
    std::cout << (ok ? "POSSIBLE" : "IMPOSSIBLE") << '\n';
    if(ok) {
        auto y = t.get_ans();
        rep(int,i,1,n) std::cout << y[i] << " \n"[i==n];
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