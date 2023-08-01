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
constexpr static ll mod_1e97 = 1e9 + 7, mod_998 = 998244353, mod_1e18 = 1e18;
constexpr static ll inf = INT_MAX, INF = LLONG_MAX;
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

constexpr static ll N = 3e5 + 114, AnsMX = 8;
ll n, a[N];
ll f[N], bt[N], inv[N], tp[N];

void pre_work(ll n) {
    rep(ll, i, 0, 1) f[i] = inv[i] = 1;
    rep(ll, i, 2, n) {
        f[i] = f[i-1] * i % mod_1e97;
    }
    rep(ll, i, 2, n) {
        inv[i] = (-inv[mod_1e97 % i] * (mod_1e97 / i) % mod_1e97 + mod_1e97) % mod_1e97;
        // std::cerr << inv[mod_1e97 % i] << ' ' << mod_1e97 / i << '\n';
        // std::cerr << inv[i] << " \n"[i==n];
    }
    rep(ll, i, 2, n) {
        inv[i] = inv[i-1] * inv[i] % mod_1e97;
        // std::cerr << inv[i] << " \n"[i==n];
    }
}
ll C(ll n, ll m) {
    return f[n] * inv[n-m] % mod_1e97 * inv[m] % mod_1e97;
}
bool is_vaild(ll x) {
    per(ll, i, 3e5 + 1, 1) {
        tp[i] = C(bt[i], x);
        for(ll j=2; j*i<=3e5 + 1; j++) {
            tp[i] = ((tp[i] - tp[i*j]) % mod_1e97 + mod_1e97) % mod_1e97;
        }
    }
    // rep(ll, i, 1, 5) std::cerr << tp[i] << " \n"[i==5];
    return tp[1];
}
void solve() {
    pre_work(3e5 + 1);
    std::cin >> n;
    // rep(ll, i, 2, n) std::cerr << inv[i] << '\n';
    rep(ll, i, 1, n) {
        std::cin >> a[i];
        ++bt[a[i]];
    }
    rep(ll, i, 1, 3e5 + 1) {
        for(ll j=2; j*i<=3e5 + 1; j++) {
            bt[i] += bt[i*j];
        }
    }
    rep(ll, i, 1, AnsMX) {
        if(is_vaild(i)) {
            std::cout << i << '\n';
            return;
        }
    }
    std::cout << -1 << '\n';

}
} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin), freopen(".out", "w", stdout);
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    hellolin::solve();
    return 0;
}