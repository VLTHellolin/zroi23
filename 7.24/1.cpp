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

constexpr static int N = 214;
int n;
ll a[N], dpmi[N][N], sum[N], dpmx[N][N];
ll ans1, ans2;
void solve() {
    std::cin >> n;
    for(int i=1; i<=n; i++) std::cin >> a[i];
    for(int i=n+1; i<=2*n; i++) a[i] = a[i-n];
    for(int i=1; i<=2*n; i++) {
        sum[i] = sum[i-1] + a[i];
    }
    for(int i=1; i<=2*n; i++) {
        for(int j=1; j<=2*n; j++) {
            if(i!=j) dpmi[i][j] = 514;
        }
    }
    for(int i=2; i<=n; i++) {
        for(int j=1; j<=2*n-i+1; j++) {
            int l = j, r = j+i-1;
            ll mi=INT_MAX, mx = 0;
            for(int k=l; k<r; k++) {
                chmin(mi, dpmi[l][k] + dpmi[k+1][r] + sum[r] - sum[l-1]);
                chmax(mx, dpmx[l][k] + dpmx[k+1][r] + sum[r] - sum[l-1]);
            }
            dpmi[l][r] = mi;
            dpmx[l][r] = mx;
        }
    }
    ans2 = INT_MAX;
    for(int i=1; i<=n; i++) {
        chmax(ans1, dpmx[i][i+n-1]);
        chmin(ans2, dpmi[i][i+n-1]);
    }
    std::cout << ans2 << '\n' << ans1 << '\n';

}
} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin), freopen(".out", "w", stdout);
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    hellolin::solve();
    return 0;
}