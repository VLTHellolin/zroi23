// * HELLOLIN'S CP CODE TEMPLATE v2.0.1
#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>
#include <functional>

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

constexpr static int N = 3e5 + 114;
int t, n, q, a[N], l, r, l1, l2, r1, r2;
ll ans;

template <class T>
int modify(int x, T fun) {
    ll num = 0;
    if(a[x] > a[x-1] && a[x] > a[x+1]) num = 1;
    else if(a[x] < a[x-1] && a[x] < a[x+1]) num = -1;
    return ans = fun(ans, a[x] * num);
}

void solve() {
    std::cin >> t;
    while(t--) {
        ans = 0;
        std::cin >> n >> q;
        memset(a, 0, sizeof(a));
        for(int i=1; i<=n; i++) std::cin >> a[i];
        for(int i=1; i<=n; i++) modify(i, std::plus<>());
        std::cout << ans << '\n';
        while(q--) {
            std::cin >> l >> r;
            l1 = std::max(l-1, 1), l2 = l+1;
            r1 = std::max(l+2, r-1), r2 = std::min(r+1, n);
            for(int i=l1; i<=l2; i++) modify(i, std::minus<>());
            for(int i=r1; i<=r2; i++) modify(i, std::minus<>());
            // std::swap(l, r);
            std::swap(a[l], a[r]);
            for(int i=l1; i<=l2; i++) modify(i, std::plus<>());
            for(int i=r1; i<=r2; i++) modify(i, std::plus<>());
            std::cout << ans << '\n';
        }
    }
}
} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin), freopen(".out", "w", stdout);
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    hellolin::solve();
    return 0;
}