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

constexpr static ll N = 1e7 + 114;

ll tp, ans;
bool vis[N];
std::vector<ll> pri;
ll Fmiu[N], preFmiu[N], prod[N];

void pre_work(ll n) {
    Fmiu[1] = 1;
    rep(ll, i, 2, n) {
        if(!vis[i]) {
            pri.pb(i), Fmiu[i] = -1;
        }
        for(ll j:pri) {
            tp = i * j;
            if(tp > n) break;
            vis[tp] = 1;
            Fmiu[tp] = -Fmiu[i];
            if(!(i % j)) {
                Fmiu[tp] = 0;
                break;
            }
        }
    }
    for(ll i:pri)
        for(ll j=1; i*j<=n; j++) {
            prod[i*j] += Fmiu[j];
        }
    rep(ll, i, 1, n)
        preFmiu[i] = preFmiu[i-1] + prod[i];
}

ll Ts;
ll a, b;

void solve() {
    pre_work(1e7+1);
    for (std::cin >> Ts; Ts--; ) {
        std::cin >> a >> b;
        tp = ans = 0;
        for(ll i=1; i<=std::min(a, b); i = ++tp) {
            tp = std::min(a / (a / i), b / (b / i));
            ans += (preFmiu[tp] - preFmiu[i-1]) * (a / i) * (b / i);
        }
        std::cout << ans << '\n';
    }
}
} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin), freopen(".out", "w", stdout);
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    hellolin::solve();
    return 0;
}