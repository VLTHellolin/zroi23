#ifndef HELLOLIN_EXTENSIONS_HPP
#define HELLOLIN_EXTENSIONS_HPP 1
#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>

namespace hellolin {
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
using ll = long long;
using ull = unsigned long long;
using lll = __int128;
using db = double;
using ld = long double;
template <class T>
using min_pq = __gnu_pbds::priority_queue<T, greater<T>, pairing_heap_tag>;
template <class T>
using max_pq = __gnu_pbds::priority_queue<T, less<T>, pairing_heap_tag>;
template <class T>
using vec = vector<T>;
using vecll = vector<ll>;
template <class T>
using vvec = vec<vec<T>>;

constexpr static ull mod_1e97 = 1e9 + 7;
constexpr static ull mod_998 = 998244353;
constexpr static ull mod_1e18 = 1e18;

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
#define fiio(x)                   \
    freopen(x ".in", "r", stdin); \
    freopen(x ".out", "w", stdout)
#define fios                      \
    std::ios::sync_with_stdio(0); \
    std::cin.tie(nullptr);        \
    std::cout.tie(nullptr)

template <class T, class U>
void chmax(T &x, U y) { x = max(x, y); }
template <class T, class U>
void chmin(T &x, U y) { x = min(x, y); }
template <class T>
T gcd(T x, T y) { return y ? gcd(y, x % y) : x; }
template <class T>
T lcm(T x, T y) { return x * y / gcd(x, y); }
template <class T>
T pow(T x, ll y) {
    T z = 1;
    while (y) {
        if (y & 1) z *= x;
        x *= x;
        y >>= 1;
    }
    return z;
}
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
template <int M>
void _yesno(bool x) {
    string y[3] = {"yes", "Yes", "YES"}, n[3] = {"no", "No", "NO"};
    cout << (x ? y[M] : n[M]) << endl;
}
#define yesno _yesno<0>
#define YesNo _yesno<1>
#define YESNO _yesno<2>
void solve();
} // namespace hellolin

#endif

int main() {
    // fiio("task");
    fios;

    // int Ts; std::cin>>Ts; while(Ts--)
    hellolin::solve();

    return 0;
}

namespace hellolin {
constexpr static ll N = 5e4+114;
ll n, sn, op, l, r, c;
array<ll,N> a, sum, lz, id;

void modify(ll l, ll r, ll v) {
    ll lid = id[l], rid = id[r];
    if(lid == rid) {
        for(ll i=l; i<=r; i++) {
            a[i] += v;
            sum[lid] += v;
        }
        return;
    }
    for(ll i=l; id[i] == lid; i++) {
        a[i] += v;
        sum[lid] += v;
    }
    for(ll i=lid+1; i<rid; i++) {
        sum[i] += sn * v;
        lz[i] += v;
    }
    for(ll i=r; id[i] == rid; i++) {
        a[i] += v;
        sum[rid] += v;
    }
}
ll query(ll x) {
    return a[x];
}

void solve() {
    cin >> n;
    sn = sqrt(n);
    for(ll i=1; i<=n; i++) {
        cin >> a[i];
        id[i] = (i-1) / sn + 1;
        sum[id[i]] += a[i];
    }
    for(ll i=1; i<=n; i++) {
        cin >> op >> l >> r >> c;
        if(!op) {
            modify(l,r,c);
        } else {
            cout<<query(r)<<endl;
        }
    }
}
} // namespace hellolin