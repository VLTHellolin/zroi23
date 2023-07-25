// * HELLOLIN'S CP CODE TEMPLATE v2.0.1
#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>

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

constexpr static int S = 20, Len = 12;
ll dp[S][S];
void pre_work() {
    for(int i=0; i<=9; i++) dp[1][i] = 1;
    for(int i=2; i<=Len; i++) {
        for(int j=0; j<=9; j++) {
            for(int k=0; k<=9; k++) {
                if(abs(j-k) >= 2) dp[i][j] += dp[i-1][k];
            }
        }
    }
}
std::vector<int> ff;
ll get_ans(ll f) {
    ll ans = 0;
    ff.clear();
    ff.pb(-1);
    do {
        ff.pb(f%10);
        f /= 10;
    } while(f);
    ll len = ff.size() - 1;
    // std::cerr << ans << '\n';

    for(int i=1; i<*ff.rbegin(); i++) {
        ans += dp[len][i];
    }
    // std::cerr << ans << '\n';

    for(int i=1; i<len; i++) {
        for(int j=1; j<=9; j++) ans += dp[i][j];
    }

    // std::cerr << ans << '\n';

    // * 最高位相同
    for(int i=len-1; i; i--) {
        for(int j=ff[i]-1; j+1; j--) {
            if(abs(ff[i+1] - j) >= 2) ans += dp[i][j];
        }
        if(abs(ff[i] - ff[i+1]) < 2) return ans;
    }
    // std::cerr << ans << '\n';

    return ans;
}

ll a, b;
void solve() {
    pre_work();
    std::cin >> a >> b;
    // std::cout << get_ans(b) - get_ans(a-1) << '\n';
    std::cout << get_ans(b+1) - get_ans(a) << '\n';
}
} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin), freopen(".out", "w", stdout);
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    hellolin::solve();
    return 0;
}