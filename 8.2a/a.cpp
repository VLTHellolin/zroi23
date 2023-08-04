// * HELLOLIN'S CP CODE TEMPLATE v2.2.1
#ifndef ONLINE_JUDGE
#pragma GCC optimize(2, "inline", "unroll-loops", "no-stack-protector", "-ffast-math")
#endif
#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>
#include <bits/stdc++.h> // * FIX gcc 5.0

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

/*
1     1 
2     50 298 
3     267 
4     376 
5     20 
6     372 480 
7     133 917 973 
8     360 
9     315 
10     10 
*/
ll f[10010];
std::vector<int> giveup[12];
ll Ts, ans, k, l, r;

void solve() {
    giveup[1] = {1};
    giveup[2] = {50, 298};
    giveup[3] = {267};
    giveup[4] = {376};
    giveup[5] = {20};
    giveup[6] = {372, 480};
    giveup[7] = {133, 917, 973};
    giveup[8] = {360};
    giveup[9] = {315};
    giveup[10] = {10};
    for(std::cin>>Ts; Ts--; ) {
        std::cin >> k >> l >> r;
        if(k<=10) {
            for(int i:giveup[k]) {
                if(i>=l && i<=r) ++ans;
            }
            std::cout << ans << '\n';
            ans = 0;
            continue;
        }
        rep(ll, i, 1, r) {
            if(i<10) f[i] = i*i;
            else f[i] = f[i / 10] + (i % 10) * (i % 10);
        }
        rep(ll, i, l, r) {
            if(k * f[i] == i) {
                // std::cout << f[i] << " * " << (i / f[i]) << " = " << i << '\n';
                ++ans;
            }
        }
        std::cout << ans << '\n';
        ans = 0;
    }
}
// * CORE CODE END * //

} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin);
    // freopen("Table.out", "w", stdout);
    // freopen(".dbg", "w", stderr);
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    // std::cout << std::fixed << std::setprecision(6);
    hellolin::solve();
    return 0;
}