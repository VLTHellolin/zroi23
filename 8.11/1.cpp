// * HELLOLIN'S CP CODE TEMPLATE v2.2.3
#ifndef ONLINE_JUDGE
#pragma GCC optimize(2, "inline", "unroll-loops", "no-stack-protector", "-ffast-math")
#endif
#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>

#ifndef HELLOLIN_GRAPH_EULER_HPP
#define HELLOLIN_GRAPH_EULER_HPP 1
#include <algorithm>
#include <vector>

namespace hellolin {

namespace graph {

class euler {
    using st = size_t;

private:
    st n, m, e_cnt = 0, e_tot = 0;
    bool directed, ready;
    int tp = 1;
    class verticle {
    public:
        int no = 0;
        int to = 0, nxt = 0;
        int T = 0;
    };
    std::vector<verticle> g;
    std::vector<bool> vis;
    std::vector<int> head, ans, ind, oud, cur;

public:
    explicit euler(st _n, st _m, bool _directed = 0)
        : n(_n)
        , m(_m)
        , directed(_directed)
        , ready(0) {
        g.resize((m<<1) + 2);
        head.resize(n + 1);
        vis.resize(m + 1);
        ans.resize(m + 1);
        ind.resize(n + 1);
        oud.resize(n + 1);
        cur.resize(n + 1);
    }
    void add_edge(int u, int v, int x) {
        ready = 0;
        tp = u;
        ++oud[u], ++ind[v];
        g[++e_cnt] = {x, v, head[u], 1};
        head[u] = e_cnt;
        if (!directed) {
            g[++e_cnt] = {x, u, head[v], -1};
            head[v] = e_cnt;
        }
    }
    bool query() {
        ready = 1;
        auto hierholzer = [&](auto fun, int x) -> void {
            for(int &i = cur[x]; i; i=g[i].nxt) {
                if(vis[g[i].no]) continue;
                vis[g[i].no] = 1;
                int _ans = g[i].T * g[i].no;
                fun(fun, g[i].to);
                ans[++e_tot] = _ans;
            }
        };

        for (int i = 1; i <= n; i++)
            if (directed) {
                if (ind[i] != oud[i])
                    return 0;
            } else {
                if ((ind[i] + oud[i]) & 1)
                    return 0;
            }

        for (int i = 1; i <= n; i++)
            cur[i] = head[i];
        hierholzer(hierholzer, tp);
        if (e_tot < m)
            return 0;
        
        std::reverse(ans.begin()+1, ans.begin()+1+m);
        return 1;
    }
    std::vector<int> &get_ans() {
        if(!ready) query();
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
int t, n, m, u, v;
bool res;
std::vector<int>q;
void solve() {
    std::cin >> t >> n >> m;
    graph::euler e(n, m, t == 2);
    rep(int, i, 1, m) {
        std::cin >> u >> v;
        e.add_edge(u, v, i);
    }
    res = e.query();
    std::cout << yesno(res, 2);
    if(res) {
        q = e.get_ans();
        rep(int, i, 1, m) {
            std::cout << q[i] << " \n"[i==m];
        }
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