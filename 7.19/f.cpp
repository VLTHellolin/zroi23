#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>

#ifndef HELLOLIN_MODINT_HPP
#define HELLOLIN_MODINT_HPP 1

namespace hellolin {

template <unsigned long long M = 998244353>
class modint {
private:
    long long val;
    unsigned long long m;

    void mod() {
        while (val < 0)
            val += m;
        val %= m;
    }

public:
    modint(long long _v = 0)
        : val(_v)
        , m(M) { mod(); }

    template <class T>
    operator T() const { return val; }
    void set_mod(unsigned long long _m) { m = _m; }

    modint operator+() const { return *this; }
    modint operator-() const { return modint() - *this; }

    modint operator++() {
        ++val;
        mod();
    }
    modint operator--() {
        --val;
        mod();
    }
    modint& operator++(int) {
        modint r = *this;
        ++val;
        mod();
        return r;
    }
    modint& operator--(int) {
        modint r = *this;
        --val;
        mod();
        return r;
    }

    modint operator+(const modint& t) const {
        modint r(val + t.val);
        return r;
    }
    modint operator-(const modint& t) const {
        modint r(val - t.val);
        return r;
    }
    modint operator*(const modint& t) const {
        modint r(val * t.val);
        return r;
    }
    modint operator/(const modint& t) const {
        modint r(val / t.val);
        return r;
    }

    modint& operator+=(const modint& t) {
        val += t.val;
        mod();
        return *this;
    }
    modint& operator-=(const modint& t) {
        val -= t.val;
        mod();
        return *this;
    }
    modint& operator*=(const modint& t) {
        val *= t.val;
        mod();
        return *this;
    }
    modint& operator/=(const modint& t) {
        val /= t.val;
        mod();
        return *this;
    }
};

} // namespace hellolin

#endif

namespace hellolin {
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
using ll = long long;
using ull = unsigned long long;
using lll = __int128;
template <class T>
using min_pq = __gnu_pbds::priority_queue<T, greater<T>, pairing_heap_tag>;
template <class T>
using max_pq = __gnu_pbds::priority_queue<T, less<T>, pairing_heap_tag>;
template <class T>
using vec = vector<T>;
using vecll = vector<ll>;
template <class T>
using vvec = vec<vec<T>>;
using vvecll = vec<vec<ll>>;
constexpr static ull mod_1e97 = 1e9 + 7, mod_998 = 998244353, mod_1e18 = 1e18, inf=LONG_LONG_MAX;
#define _x first
#define _y second
#define allof(x) x.begin(), x.end()
#define alllof(x) x.begin() + 1, x.end()
#define pb emplace_back
#ifdef LOCAL
#define dbg(x) cerr << __LINE__ << ": " << #x << " = " << x << endl
#else
#define dbg(x) void(0)
#endif
template <class T>
T pow(T x, ll y, ull m) {
    T z = 1;
    while (y) {
        if (y & 1) z = (z * x) % m;
        x = (x * x) % m;
        y >>= 1;
    }
    return z;
}
template <class T>
void readarr(T st, T ed) {
    while (st != ed) {
        cin >> *st;
        ++st;
    }
}
template <class T>
void writearr(T st, T ed, char s = ' ', bool e = 1) {
    while (st != ed) {
        cout << *st << s;
        ++st;
    }
    if (e) cout << endl;
}
void solve();
} // namespace hellolin

#define FILEIO 0
#define FILENAME ""
#define FASTIO 1
#define MULTI 0

int main() {
#if FILEIO
    freopen(FILENAME ".in", "r", stdin), freopen(FILENAME ".out", "w", stdout);
#endif
#if FASTIO
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
#endif
#if MULTI
    long long Ts;std::cin >> Ts;while (Ts--)hellolin::solve();
#else
    hellolin::solve();
#endif

    return 0;
}

namespace hellolin {

constexpr static ll N = 1e5 + 114, Sn = 320, Pri = 1145141923;
ll n, m, q, len, cor, sum, tot_sum, rp;
pair<ll,ll> corr;
array<ll,N> a, p, s;
class myHash {
public:
    ll *pr;
    ll sz;
    myHash(ll _x = 0) {
        sz = 0;
        pr = new ll[_x+1];
        pr[0] = 0;
    }
    void push(ll x) {
        ++sz;
        pr[sz] = modint(pr[sz - 1] * Pri % mod_1e97) + modint(x);
    }
    void erase(ll x) { sz -= x; }
    ll operator()(ll x) {
        return modint(pr[sz]) + modint(mod_1e97 - pr[sz - x] * p[x] % mod_1e97);
    }
};
stack<myHash> hsh;
vecll tp;
array<ll,N> invs;
array<ll,Sn> sq, tt;

ll ha() {
    ll ret = 0;
    for(ll i : tp) {
        ret = modint(i) + modint(ret * Pri % mod_1e97);
    }
    return ret;
}


void solve() {
    
}
} // namespace hellolin