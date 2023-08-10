// * HELLOLIN'S CP CODE TEMPLATE v2.2.0
#ifndef ONLINE_JUDGE
#pragma GCC optimize(2, "inline", "unroll-loops", "no-stack-protector", "-ffast-math")
#endif
#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>

namespace hellolin {
namespace lib {
using ll = long long;
using ull = unsigned long long;
using lll = __int128;
using ulll = __uint128_t;
using ld = long double;
constexpr static ull mod_1e97 = 1e9 + 7, mod_998 = 998244353, mod_1e18 = 1e18;
constexpr static ull inf = INT_MAX, INF = LLONG_MAX;
const static std::string yesno_str[2][3] = {{"no", "No", "NO"}, {"yes", "Yes", "YES"}};
template <class T> inline void yesno(bool x, int y, T u = std::cout) { u << yesno_str[x][y] << '\n'; }
template <class T, class U> inline bool chmax(T &x, U y) { return y > x ? (x = y, 1) : 0; }
template <class T, class U> inline bool chmin(T &x, U y) { return y < x ? (x = y, 1) : 0; }
#define rep(l, x, a, b) for (l x = a, x##END = b; x <= x##END; ++x)
#define per(l, x, a, b) for (l x = a, x##END = b; x >= x##END; --x)
#define y0 _HOMO_114_514_
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

std::map<ll, ll> baby;
ll giant, tp;

ll fpow(ll a, ll b, ll md) {
    ll res = 1;
    for(; b; b>>=1, a=a*a%md) if(b&1) res=res*a%md;
    return res;
}
ll BSGS(ll a, ll b, ll md) {
    baby.clear();
    a %= md, b %= md;
    giant = ceil(sqrt(md));
    rep(ll, i, 0, giant - 1) {
        baby[fpow(a, i, md) * b % md] = i;
    }
    a = fpow(a, giant, md);
    if(!a) {
        if(!b) return 1;
        return -1;
    }
    ll res = -1;
    rep(ll, i, 1, giant) {
        tp = fpow(a, i, md);
        if(baby.count(tp)) {
            res = giant * i - baby[tp];
            if(res >= 0) return res;
        }
    }
    return -114514;
}

ll p, b, n, ans;
void solve() {
    std::cin >> p >> b >> n;
    ans = BSGS(b, n, p);
    if(ans<0) std::cout << "no solution\n";
    else std::cout << ans << '\n';
}
} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin), freopen(".out", "w", stdout);
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    hellolin::solve();
    return 0;
}