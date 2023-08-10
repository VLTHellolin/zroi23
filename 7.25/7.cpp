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

constexpr static int S = 10;
int n;
bool b[S];
std::set<int>ans;
bool chk(int x) {
    memset(b, 0, sizeof(b));
    do {
        b[x%10] = 1;
        x /= 10;
    } while(x);
    return std::accumulate(b, b+10, 0) <= 2;
}
void dfs(int now) {
    if(now<=0 || now>n) return;
    ans.insert(now);
    if(now>1e8) return;
    for(int i=0; i<=9; i++) {
        if(chk(now*10+i)) {
            dfs(now*10+i);
        }
    }
}
void solve() {
    std::cin >> n;
    for(int i=1; i<=9; i++) dfs(i);
    std::cout << ans.size() << '\n';
}
} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin), freopen(".out", "w", stdout);
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    hellolin::solve();
    return 0;
}