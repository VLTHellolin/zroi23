// * HELLOLIN'S CP CODE TEMPLATE v2.0.1
#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>

#ifndef HELLOLIN_DISTRIBUTION_HPP
#define HELLOLIN_DISTRIBUTION_HPP 1
#include <algorithm>
#include <vector>

namespace hellolin {

template <class T>
class distribution {
    using st = size_t;

private:
    bool ready;
    std::vector<T> d;
    void init() {
        std::sort(d.begin(), d.end());
        d.erase(std::unique(d.begin(), d.end()), d.end());
        ready = 1;
    }

public:
    explicit distribution()
        : ready(0) {}
    void push(T x) {
        d.emplace_back(x);
        ready = 0;
    }
    st distribute(T x) {
        if (!ready) init();
        return std::lower_bound(d.begin(), d.end(), x) - d.begin() + 1;
    }
    T tribute(st x) {
        if (!ready) init();
        return d[x - 1];
    }
    st size() {
        return d.size();
    }
    void clear() {
        d.clear();
    }
};

} // namespace hellolin

#endif

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


namespace DS {
class block {
public:
    int a;
    ll l, r;
    explicit block(int _a = 0, ll _l = 0, ll _r = 0)
        : a(_a)
        , l(_l)
        , r(_r) {}
};
template <class T>
class matrix {
private:
    int sz;
    T **a;

public:
    explicit matrix(int _sz)
        : sz(_sz) {
        assert(sz >= 1);
        a = new T*[sz];
        for(int i=0; i<sz; i++) a[i] = new T[sz];

        clear();
    }
    void clear() {
        for(int i=0; i<sz; i++) for(int j=0; j<sz; j++) a[i][j] = 0;
    }
    int size() {
        return sz;
    }
    void set_1() {
        clear();
        for(int i=0; i<sz; i++) a[i][i] = 1;
    }
    void set_0() {
        clear();
        set_1();
        for(int i=1; i<sz; i++) {
            int j=i-1;
            a[i][j] = a[j][i] = 1;
        }
    }
    void clean_row(int x) {
        for(int i=0; i<sz; i++) a[x][i] = 0;
    }
    void clean_col(int x) {
        for(int i=0; i<sz; i++) a[i][x] = 0;
    }
    T *operator[](int x) const {
        return a[x];
    }
    matrix operator*(const matrix& m) const {
        matrix res(sz);
        for(int i=0; i<sz; i++) for(int j=0; j<sz; j++) for(int k=0; k<sz; k++)
            res[i][j] = (res[i][j] + a[i][k] * m[k][j] % mod_1e97) % mod_1e97;
        return res;
    }
    matrix &operator*=(const matrix& m) {
        return *this = *this * m;
    }
    matrix pow(ll x) {
        matrix res(sz), tmp(sz);
        res.set_1();
        tmp = *this;
        while(x) {
            if(x&1) res *= tmp;
            tmp *= tmp;
            x >>= 1;
        }
        return res;
    }
    void dbg() {
        for(int i=0; i<sz; i++) {
            for(int j=0; j<sz; j++) {
                std::cerr << a[i][j] << " \n"[j == sz-1];
            }
        }
        std::cerr << '\n';
    }

};
} // namespace DS

constexpr static int N = 11451, MATRIX_SIZE = 3;
ll n, m;
// std::pair<int, ll> wh {2, 1};
DS::block info[N];
DS::matrix<ll> res(MATRIX_SIZE), tp(MATRIX_SIZE);
distribution<ll> di;
ll dp[N << 1][MATRIX_SIZE], gr[MATRIX_SIZE];
void solve() {
    std::cin >> n >> m;
    di.push(1), di.push(m);
    for(ll i=1; i<=n; i++) {
        std::cin >> info[i].a >> info[i].l >> info[i].r;
        di.push(info[i].l - 1), di.push(info[i].r);
        --info[i].a;
    }
    for(ll i=1; i<=n; i++) {
        info[i].l = di.distribute(info[i].l);
        info[i].r = di.distribute(info[i].r);
        ++dp[info[i].l][info[i].a], --dp[info[i].r + 1][info[i].a];
        

    }
    res[1][0] = 1; // * 2, 1
    memset(gr, 0, sizeof(gr));
    for(ll i=2; i<=di.size(); i++) {
        tp.clear();
        tp.set_0();
        for(int j=0; j<MATRIX_SIZE; j++) {
            gr[j] += dp[i][j];
            if(gr[j] > 0) tp.clean_row(j);
        }
        tp = tp.pow(di.tribute(i) - di.tribute(i-1));
        res = tp * res;
    }
    std::cout << res[1][0] << '\n';

}
} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin), freopen(".out", "w", stdout);
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    hellolin::solve();
    return 0;
}