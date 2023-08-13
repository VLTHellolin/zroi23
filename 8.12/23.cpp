// * HELLOLIN'S CP CODE TEMPLATE v2.4.0
#ifndef ONLINE_JUDGE
#pragma GCC optimize(2, "inline", "unroll-loops", "no-stack-protector", "-ffast-math")
#endif
#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>
#ifdef LOCAL
#include <windows.h>
#include <psapi.h>
#endif

#ifndef HELLOLIN_GRAPH_MIN_COST_FLOW_HPP
#define HELLOLIN_GRAPH_MIN_COST_FLOW_HPP
#include <algorithm>
#include <limits>
#include <queue>
#include <vector>

namespace hellolin {

namespace graph {

template <class T, class H>
class min_cost_flow {
private:
    int n, m;
    long long inf;
    std::vector<std::pair<int, int>> pr;
    class internal_edge {
    public:
        int to, p;
        T w;
        H cost;
    };
    std::vector<std::vector<internal_edge>> g;
    std::vector<bool> vis;
    class spfa_node {
    public:
        T flow;
        H dis;
        std::pair<int, int> p;
    };
    std::vector<spfa_node> s;
    T flow_res;
    H cost_res;
    std::queue<int> q;

    bool spfa(int fr, int to) {
        for (int i = 1; i <= n; i++) {
            s[i].dis = inf;
        }
        vis.clear();
        vis[fr] = 1;
        q = std::queue<int> ();
        q.push(fr);
        s[fr].dis = 0;
        s[fr].flow = inf;
        while (q.size()) {
            int tp = q.front();
            q.pop();
            vis[tp] = 0;
            int ind = -1;
            for (internal_edge &i : g[tp]) {
                ++ind;
                if (i.w > 0 && i.cost + s[tp].dis < s[i.to].dis) {
                    s[i.to].dis = i.cost + s[tp].dis;
                    s[i.to].flow = std::min(s[tp].flow, i.w);
                    s[i.to].p = {tp, ind};
                    if (!vis[i.to]) {
                        vis[i.to] = 1;
                        q.push(i.to);
                    }
                }
            }
        }
        return s[to].dis != inf;
    }
    void _upd(int fr, int to) {
        int tp1 = to, tp2 = -1, tp3 = -1;
        while (tp1 != fr) {
            tp2 = s[tp1].p.first;
            tp3 = s[tp1].p.second;
            g[tp2][tp3].w -= s[to].flow;
            g[tp1][g[tp2][tp3].p].w += s[to].flow;
            tp1 = tp2;
        }
        flow_res += s[to].flow;
        cost_res += s[to].flow * s[to].dis;
    }

public:
    class edge {
    public:
        int fr, to;
        T w, flow;
        H cost;
    };
    explicit min_cost_flow(int _n, long long _inf = 1e9)
        : n(_n)
        , inf(_inf) {
        g.resize(n + 1);
        vis.resize(n + 1);
        s.resize(n + 1);
    }
    void add_edge(int fr, int to, T w, H co) {
        m = pr.size();
        int _fr = g[fr].size(), _to = g[to].size();
        if (fr == to) ++_to;
        pr.push_back({fr, _fr});
        g[fr].push_back(internal_edge{to, _to, w, co});
        g[to].push_back(internal_edge{fr, _fr, 0, -co});
    }
    edge get_edge(int x) {
        m = pr.size();
        internal_edge e1, e2;
        e1 = g[pr[x].first][pr[x].second];
        e2 = g[e1.to][e1.p];
        return edge{pr[x].first, e1.to, e1.w + e2.w, e2.w, e1.cost + e2.cost};
    }
    std::vector<edge> get_edges() {
        m = pr.size();
        std::vector<edge> e;
        for (int i = 0; i < m; i++) {
            e.push_back(get_edge(i));
        }
        return e;
    }
    std::pair<T, H> get_flow_cost(int fr, int to, T flow_lim = std::numeric_limits<T>::max(), H cost_lim = std::numeric_limits<H>::max()) {
        flow_res = cost_res = 0;
        while (spfa(fr, to) && flow_res < flow_lim && cost_res < cost_lim)
            _upd(fr, to);
        return {flow_res, cost_res};
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
const static std::string yesno_str[2][3] = {{"no", "No", "NO"}, {"yes", "Yes", "YES"}};
inline std::string yesno(bool x, int y) { return yesno_str[x][y] + '\n'; }
template <class T> inline T fpow(T x, ull y, T mod) { T res = 1; for(; y; y >>= 1, x = x * x % mod) if(y & 1) res = res * x % mod; return res; }
template <class T, class U> inline bool chmax(T &x, U y) { return y > x ? (x = y, 1) : 0; }
template <class T, class U> inline bool chmin(T &x, U y) { return y < x ? (x = y, 1) : 0; }
#define rep(l, x, a, b) for (l x = a, x##END = b; x <= x##END; ++x)
#define per(l, x, a, b) for (l x = a, x##END = b; x >= x##END; --x)
#define y0 _y_0_
#define y1 _y_1_
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
}
using namespace lib;

// * CORE CODE BEGIN * //
int n, m, s, t;
ll u, v, w, c;
ll ans1, ans2;
void solve() {
    std::cin >> n >> m >> s >> t;
    graph::min_cost_flow<ll,ll> f(n);
    rep(int, i, 1, m) {
        std::cin >> u >> v >> w >> c;
        f.add_edge(u, v, w, c);
    }
    std::tie(ans1, ans2) = f.get_flow_cost(s, t);
    std::cout << ans1 << ' ' << ans2 << nl;
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