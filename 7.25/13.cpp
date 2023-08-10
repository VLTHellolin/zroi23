// * HELLOLIN'S CP CODE TEMPLATE v2.0.1
#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>

#ifndef HELLOLIN_DISTRIBUTION_HPP
#define HELLOLIN_DISTRIBUTION_HPP 1
#include <algorithm>
#include <vector>

namespace hellolin {

template <class T>
class distribution {
    using st = size_t;

private:
    bool ready;
    std::vector<T> d;
    void init() {
        std::sort(d.begin(), d.end());
        d.erase(std::unique(d.begin(), d.end()), d.end());
        ready = 1;
    }

public:
    explicit distribution()
        : ready(0) {}
    void push(T x) {
        d.emplace_back(x);
        ready = 0;
    }
    st distribute(T x) {
        if (!ready) init();
        return std::lower_bound(d.begin(), d.end(), x) - d.begin() + 1;
    }
    T tribute(st x) {
        if (!ready) init();
        return d[x - 1];
    }
    st size() {
        return d.size();
    }
    void clear() {
        d.clear();
    }
};

} // namespace hellolin

#endif

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

int Ts;
constexpr static int MOD = 2520, N = 30;
distribution<int> dist;
std::vector<int> f;
ll x, y, sz;
ll dp[N][N+51][MOD+114];

ll lcm(ll x, ll y) {
    return x * y / std::__gcd(x,y);
}

ll dfs(int pos, int zg, bool rgt, int l) {
    ll ans = zg % l == 0, tp = 9, tpzg = 0, tpl = 0;
    if(!(~pos)) return ans;
    bool tprgt = 0;
    // ll& now = dp[pos][dist.tribute(l)][zg];
    ll& now = dp[pos][dist.distribute(l)][zg];
    if(!rgt) {
        if(~now) return now;
    }   
    if(~pos) {
        ans = 0;
        if(rgt) tp = f[pos];
        for(int i=0; i<=tp; i++) {
            tpzg = (zg * 10 + i) % MOD;
            tpl = l;
            if(i) tpl = lcm(tpl, i);
            tprgt = rgt & (i == tp);
            ans += dfs(pos-1, tpzg, tprgt, tpl);
        }
        if(!rgt) now = ans;
    }
    return ans;
}
ll get_ans(ll pos) {
    f.clear();
    do {
        f.pb(pos % 10);
        pos /= 10;
    } while(pos);
    return dfs(f.size() - 1, 0, 1, 1);
}

void solve() {
    std::cin >> Ts;
    memset(dp, -1, sizeof(dp));
    for(int i=1; i<=MOD; i++) {
        if(MOD%i)continue;
        dist.push(i);
    }
    // sz = dist.size();
    while(Ts--) {
        std::cin >> x >> y;
        std::cout << get_ans(y) - get_ans(x-1) << '\n';
    }

}
} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin), freopen(".out", "w", stdout);
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    hellolin::solve();
    return 0;
}