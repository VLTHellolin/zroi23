// * HELLOLIN'S CP CODE TEMPLATE v2.1.1
#ifndef ONLINE_JUDGE
#pragma GCC optimize(2, "inline", "unroll-loops", "no-stack-protector", "-ffast-math")
#endif
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,mmx")
#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>

namespace hellolin {
namespace lib {
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
}
using namespace lib;
namespace DS {
template<class T>
class matrix {
private:
    T **a;
    int sz;
public:
    explicit matrix(int _sz)
        : sz(_sz) {
        assert(sz >= 1);
        a = new T*[sz];
        for(int i=0; i<sz; i++) a[i] = new T[sz];
    }
    T *operator[](int x) const {
        return a[x];
    }
    void clear() {
        for(int i=0; i<sz; i++) for(int j=0; j<sz; j++)a[i][j] = 0;
    }
    int size() const {
        return sz;
    }
    matrix operator*(const matrix &m) const {
        matrix res(sz);
        for(int i=0; i<sz; i++) for(int j=0; j<sz; j++) for(int k=0; k<sz; k++)
            res[i][j] = (res[i][j] + a[i][k] * m[k][j]) % mod_1e97;
        return res;
    }
    matrix &operator*=(const matrix &m) {
        return *this = *this * m;
    }
    matrix pow(matrix &res, ll x) const {
        matrix tp(sz);
        tp = *this;
        while(x) {
            if(x&1) res *= tp;
            tp *= tp;
            x >>= 1;
        }
        return res;
    }
};
}

DS::matrix<ll> ans(2), tp(2);
ll n;

void solve() {
    for(int i=0; i<2; i++) for(int j=0; j<2; j++) {
        ans[i][j] = tp[i][j] = 1;
    }
    ans[1][1] = ans[1][0] = 0;
    tp[1][1] = 0;
    
    std::cin >> n;
    if(n<3) {
        std::cout << 1 << '\n';
        return;
    }
    tp.pow(ans, n - 2);
    std::cout << ans[0][0] % mod_1e97 << '\n';
}
} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin), freopen(".out", "w", stdout);
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    hellolin::solve();
    return 0;
}