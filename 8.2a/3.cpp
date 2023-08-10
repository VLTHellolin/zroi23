// * HELLOLIN'S CP CODE TEMPLATE v2.2.1
#include <algorithm>
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
namespace fib {

class matrix {
private:
    ll **a;
    int sz;
public:
    explicit matrix(int _sz)
        : sz(_sz) {
        assert(sz >= 1);
        a = new ll*[sz];
        rep(int, i, 0, sz-1) a[i] = new ll[sz];
    }
    void clear() {
        rep(int, i, 0, sz-1) rep(int, j, 0, sz-1) a[i][j] = 0;
    }
    ll *operator[](int x) const {
        return a[x];
    }
    matrix operator*(const matrix &m) const {
        matrix res(sz);
        rep(int, i, 0, sz-1) rep(int, j, 0, sz-1) rep(int, k, 0, sz-1)
            res[i][j] = (res[i][j] + a[i][k] * m[k][j]) % mod_1e97;
        return res;
    }
    matrix &operator*=(const matrix &m) {
        return *this = *this * m;
    }
    matrix pow(matrix &res, ll x) const {
        matrix tp(sz);
        tp = *this;
        for(; x; x>>=1, tp *= tp)
            if(x&1) res *= tp;
        return res;
    }
};

matrix tp(2), ans(2);
ll get(ll n) {
    ++n;
    rep(int, i, 0, 1) {
        rep(int, j, 0, 1) {
            tp[i][j] = ans[i][j] = 1;
        }
    }
    ans[1][1] = ans[1][0] = 0;
    tp[1][1] = 0;
    if(n<3) return 1;
    tp.pow(ans, n-2);
    return ans[0][0] % mod_1e97;
}
}
ll n, ans;
int k;
std::vector<ll> p;
bool chk() {
    rep(int, i, 1, n) {
        if(abs(i - p[i]) > k) return 0;
    }
    return 1;
}
void solve() {
    std::cin >> n >> k;
    if(!k) {
        std::cout << 1 << '\n';
        return;
    }
    if(k==1) {
        std::cout << fib::get(n) << '\n';
        return;
    }
    p.resize(n+1);
    rep(ll, i, 1, n) {
        p[i] = i;
    }
    do {
        ans += chk();
    } while (std::next_permutation(alof(p)));
    std::cout << ans << '\n';
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