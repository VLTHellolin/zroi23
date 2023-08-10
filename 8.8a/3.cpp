// * HELLOLIN'S CP CODE TEMPLATE v2.2.2
#ifndef ONLINE_JUDGE
#pragma GCC optimize(2, "inline", "unroll-loops", "no-stack-protector", "-ffast-math")
#endif
#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>
#include <bits/stdc++.h> // * Fix GCC 5.0

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
constexpr static int N = 3145;
int n, m, q, op, x1, x2, y1, y2, ans;
ll lastans;
int t[N][N];
void read_and_decry() {
    std::cin >> op >> x1 >> x2 >> y1 >> y2;
    x1 = ((ll)x1 + lastans) % n;
    x2 = ((ll)x2 + lastans) % n;
    y1 = ((ll)y1 + lastans) % n;
    y2 = ((ll)y2 + lastans) % n;
    if(x2 < x1) std::swap(x1, x2);
    if(y2 < y1) std::swap(y1, y2);
}
// clock_t st, ed;
void solve() {
    // st = clock();
    std::cin >> n >> m >> q;
    rep(int,i,1,m) {
        read_and_decry();
        // fprintf(stderr, "%d %d %d %d %d\n", op, x1, x2, y1, y2);
        ans = 0;
        rep(int,x,x1,x2) {
            rep(int,y,y1,y2) {
                if(op==1) ++t[x][y];
                else ans = (ans + t[x][y]) % q;
            }
        }
        if(op==2) {
            std::cout << ans % q << '\n';
            lastans += ans % q;
        }
    }
    // ed = clock();
    // std::cerr << std::fixed << std::setprecision(6);
    // std::cerr << (long double)(ed - st) / CLOCKS_PER_SEC << '\n';
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