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

// constexpr static ll N = 1e5+11;

class segment_tree final {
public:
    class tree_node final {
    public:
        ll am, lm, rm, sum;
        explicit tree_node(ll x = 0) {
            am = lm = rm = sum = x;
        }
    };

private:
    ll n;
    vecll a;
    vec<tree_node> tr;

    void update(ll x=1) {
        tr[x].sum = tr[x<<1].sum + tr[x<<1|1].sum;
        tr[x].lm = max(tr[x<<1].lm, tr[x<<1].sum + tr[x<<1|1].lm);
        tr[x].rm = max(tr[x<<1|1].rm, tr[x<<1|1].sum + tr[x<<1].rm);
        tr[x].am = max({tr[x<<1].am, tr[x<<1|1].am, tr[x<<1].rm + tr[x<<1|1].lm});
    }
    void build_tree(ll l, ll r, ll x=1) {
        if(l==r) {
            tr[x] = tree_node(a[l]);
            return;
        }
        ll mid=(l+r)>>1;
        build_tree(l, mid, x<<1);
        build_tree(mid+1, r, x<<1|1);
        update(x);
    }

public:
    explicit segment_tree(ll _n, vecll _a)
        : n(_n) {
        tr.resize(_n<<2|1);
        a = _a;
        build_tree(1,n);
    }
    void modify(ll p, ll l, ll r, ll v, ll x=1) {
        if(l==r) {
            if(l==p) {
                tr[x] = tree_node(v);
            }
            return;
        }
        ll mid=(l+r)>>1;
        if(p<=mid) modify(p,l,mid,v,x<<1);
        if(mid<p) modify(p,mid+1,r,v,x<<1|1);
        update(x);
    }
    tree_node query(ll l, ll r, ll lx, ll rx, ll x=1) {
        // dbg(lx), dbg(rx);
        if(l<=lx&&rx<=r) {
            return tr[x];
        }
        tree_node ans;
        ll mid = (lx+rx)>>1;
        if(r<=mid) ans = query(l, r, lx, mid, x<<1);
        else if(mid<l) ans = query(l, r, mid+1, rx, x<<1|1);
        else {
            tree_node a1, a2;
            a1 = query(l, r, lx, mid, x<<1);
            a2 = query(l, r, mid+1, rx, x<<1|1);
            ans.sum = a1.sum + a2.sum;
            ans.lm = max(a1.lm, a1.sum + a2.lm);
            ans.rm = max(a2.rm, a2.sum + a1.rm);
            ans.am = max({a1.am, a2.am, a1.rm + a2.lm});
        }
        return ans;
    }
};
ll n, m;
ll k, x, y;
vecll a;
void solve() {
    // freopen("C:/Users/lin/Downloads/P4513_2.in", "r", stdin);
    cin >> n >> m;
    a.resize(n+1);
    readarr(a.begin()+1,a.end());
    segment_tree tr(n,a);
    for(ll i=1; i<=m; i++) {
        // dbg(i);
        cin >> k >> x >> y;
        if(k==2) {
            tr.modify(x, 1, n, y);
        } else {
            if(x>y) swap(x,y);
            cout << tr.query(x, y, 1, n).am << endl;
        }
    }
}
} // namespace hellolin