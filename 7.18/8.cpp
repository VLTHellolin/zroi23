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

class segment_tree {
private:
    ll n;
    vecll mx, sum;
    vecll a;
    void update(ll x=1) {
        mx[x] = max(mx[x<<1], mx[x<<1|1]);
        sum[x] = sum[x<<1] + sum[x<<1|1];
    }
    void build_tree(ll l, ll r, ll x=1) {
        if(l==r) {
            mx[x] = sum[x] = a[l];
            return;
        }
        ll mid=(l+r)>>1;
        build_tree(l, mid, x<<1);
        build_tree(mid+1, r, x<<1|1);
        update(x);
        return;
    }

public:
    segment_tree(ll _n, vecll _a)
        : n(_n)
        , a(_a) {
        mx.resize(n<<2|1), sum.resize(n<<2|1);
        build_tree(1, n);
    }
    ll query(ll l, ll r, ll lx, ll rx, ll x=1) {
        if(l<=lx&&rx<=r) {
            return sum[x];
        }
        ll mid = (lx+rx)>>1;
        if(r<=mid) return query(l,r,lx,mid,x<<1);
        else if(mid<l) return query(l,r,mid+1,rx,x<<1|1);
        else return query(l,r,lx,mid,x<<1) + query(l,r,mid+1,rx,x<<1|1);
    }
    void modify_mod(ll l, ll r, ll lx, ll rx, ll m, ll x=1) {
        if(l<=lx&&rx<=r&&mx[x]<m) return;
        
        // dbg(l), dbg(r), dbg(lx), dbg(rx), dbg(m); 
        // cerr<<endl;
        if(lx==rx) {
            mx[x] = sum[x] % m;
            sum[x] %= m;
            return;
        }
        ll mid=(lx+rx)>>1;
        if(l<=mid) modify_mod(l,r,lx,mid,m,x<<1);
        if(mid<r) modify_mod(l,r,mid+1,rx,m,x<<1|1);
        update(x);
    }
    void modify(ll lx, ll rx, ll m, ll v, ll x=1) {
        if(lx==rx) {
            mx[x] = sum[x] = v;
            return;
        }
        ll mid=(lx+rx)>>1;
        if(m<=mid) modify(lx,mid,m,v,x<<1);
        else modify(mid+1,rx,m,v,x<<1|1);
        update(x);
    }
    void debug() {
        // writearr(sum.begin(),sum.end());
    }

};
ll n, m;
vecll a;
ll t, l, r, x;
void solve() {
    cin >> n >> m;
    a.resize(n+1);
    readarr(a.begin()+1, a.end());
    segment_tree tr(n,a);
    for(ll i=1; i<=m; i++) {
        cin >> t >> l >> r;
        if(t==1) {
            cout << tr.query(l,r,1,n) << endl;
        } else if(t==2) {
            cin >> x;
            tr.modify_mod(l, r, 1, n, x);
        } else {
            // cin >> x;
            tr.modify(1,n,l,r);
        }
        tr.debug();
    }
}
} // namespace hellolin