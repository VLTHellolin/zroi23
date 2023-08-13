// * HELLOLIN'S CP CODE TEMPLATE v2.2.2
#ifndef ONLINE_JUDGE
#pragma GCC optimize(2, "inline", "unroll-loops", "no-stack-protector", "-ffast-math")
#endif
#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>

#ifndef HELLOLIN_GRAPH_BCC_HPP
#define HELLOLIN_GRAPH_BCC_HPP 1
#include <algorithm>
#include <stack>
#include <vector>

namespace hellolin {

namespace graph {

class v_bcc {
    using st = size_t;

private:
    st n;
    int tot = 0, bcc_tot = 0;
    std::vector<int> dfn, low, ind;
    std::vector<std::vector<int>> g, ans;
    std::stack<int> q;

public:
    explicit v_bcc(st _n)
        : n(_n) {
        dfn.resize(n + 1);
        low.resize(n + 1);
        ind.resize(n + 1);
        g.resize(n + 1);
        ans.resize(n + 1);
    }
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
        ++ind[u], ++ind[v];
    }
    std::pair<int, std::vector<std::vector<int>>> query() {
        auto tarjan = [&](auto fun, int x) -> void {
            low[x] = dfn[x] = ++tot;
            q.push(x);
            if (!ind[x]) {
                ans[++bcc_tot].push_back(x);
            }
            for (int y : g[x]) {
                if (!dfn[y]) {
                    fun(fun, y);
                    low[x] = std::min(low[x], low[y]);
                    if (low[y] >= dfn[x]) {
                        ++bcc_tot;
                        int tp = -1;
                        ans[bcc_tot].push_back(x);
                        do {
                            tp = q.top(), q.pop();
                            ans[bcc_tot].push_back(tp);
                        } while (tp != y);
                    }
                } else {
                    low[x] = std::min(low[x], dfn[y]);
                }
            }
        };

        for (int i = 1; i <= n; i++)
            if (!dfn[i]) tarjan(tarjan, i);
        for (int i = 1; i <= n; i++) {
            std::sort(ans[i].begin(), ans[i].end());
            ans[i].erase(std::unique(ans[i].begin(), ans[i].end()), ans[i].end());
        }
        return {bcc_tot, ans};
    }
};

class e_bcc {
    using st = size_t;

private:
    st n;
    int tot = 0, bcc_tot = 0, cnt = 1;
    std::vector<int> dfn, low;
    std::vector<std::vector<std::pair<int, int>>> g;
    std::vector<std::vector<int>> ans;
    std::stack<int> q;

public:
    explicit e_bcc(st _n)
        : n(_n) {
        dfn.resize((n << 1) + 2);
        low.resize((n << 1) + 2);
        g.resize((n << 1) + 2);
        ans.resize(n + 1);
    }
    void add_edge(int u, int v) {
        g[u].push_back({v, ++cnt});
    }
    std::pair<int, std::vector<std::vector<int>>> query() {
        auto tarjan = [&](auto fun, int x, int ed) -> void {
            low[x] = dfn[x] = ++tot;
            q.push(x);
            for (auto qwq : g[x]) {
                int y = qwq.first;
                if (!dfn[y]) {
                    fun(fun, y, qwq.second);
                    low[x] = std::min(low[x], low[y]);
                    if (low[y] > dfn[x]) {
                        ++bcc_tot;
                        int tp = -1;
                        do {
                            tp = q.top(), q.pop();
                            ans[bcc_tot].push_back(tp);
                        } while (tp != y);
                    }
                } else if (qwq.second != (ed ^ 1)) {
                    low[x] = std::min(low[x], dfn[y]);
                }
            }
        };

        for (int i = 1; i <= n; i++)
            if (!dfn[i]) {
                add_edge(i + n, i);
                tarjan(tarjan, i + n, 0);
            }
        for (int i = 1; i <= n; i++) {
            std::sort(ans[i].begin(), ans[i].end());
            ans[i].erase(std::unique(ans[i].begin(), ans[i].end()), ans[i].end());
        }
        return {bcc_tot, ans};
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
int n, m, u, v;
int all;
std::vector<std::vector<int>>ans;
void solve() {
    std::cin >> n >> m;
    graph::e_bcc b(n);
    rep(int, i, 1, m) {
        std::cin >> u >> v;
        if(u!=v) {
            b.add_edge(u,v);
            b.add_edge(v,u);
        }
    }
    std::tie(all, ans) = b.query();
    std::cout << all << '\n';
    for(int i=1; i<=all; i++) {
        std::cout << ans[i].size() << ' ';
        for(int j : ans[i]) {
            std::cout << j << ' ';
        }
        std::cout << '\n';
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