#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>

namespace hellolin {
using ll = long long;
using ull = unsigned long long;
using lll = __int128;
template <class T> using min_pq = __gnu_pbds::priority_queue<T, std::greater<T>, __gnu_pbds::pairing_heap_tag>;
template <class T> using max_pq = __gnu_pbds::priority_queue<T, std::less<T>, __gnu_pbds::pairing_heap_tag>;
template <class T> using vec = std::vector<T>;
using vecll = vec<ll>;
template <class T> using vvec = vec<vec<T>>;
using vvecll = vec<vec<ll>>;
constexpr static ull mod_1e97 = 1e9 + 7, mod_998 = 998244353, mod_1e18 = 1e18, inf = LONG_LONG_MAX;
template <class T, class U> bool chmax(T &x, U y) { bool f = y > x; if(f) x = y; return f; }
template <class T, class U> bool chmin(T &x, U y) { bool f = y < x; if(f) x = y; return f; }
#define _x first
#define _y second
#define allof(x) x.begin(), x.end()
#define alllof(x) x.begin() + 1, x.end()
#define pb emplace_back
#define dbg(x) std::cerr << __LINE__ << ": " << #x << " = " << x << '\n'

namespace vars {

constexpr static ll N = 1e5 + 11;

ll n, m, r, p, all;
vecll a;
ll u, v;
ll op, x, y, z;
std::array<ll,N> fa, sz, dep;
std::array<ll,N> ba, son_osz, tp;
vvecll g;

}

using namespace vars;

namespace HLD {

class BIT final {
private:
    ll n;
    vec<ll> aaa, aa;
    ll lowbit(ll x) { return x & -x; }
    ll query_base(ll x) {
        ll ans = 0;
        for(ll i=x; i>0; i-=lowbit(i)) {
            ans += x * (ll)aaa[i] % p - aa[i] % p + p;
            ans %= p;
        }
        return ans;
    }

public:
    explicit BIT(ll _n)
        : n(_n) {
        aaa.resize(N), aa.resize(N);
        // for(auto&i:aaa) i.set_mod(p);
        // for(auto&i:aa) i.set_mod(p);
    }
    void modify(ll l, ll r, ll x) {
        x %= p;
        ll le = (l-1) * x % p, ri = r * x % p;
        for(ll i=l; i<=n; i+=lowbit(i)) {
            aaa[i] =  (aaa[i] + x) % p;
            aa[i] = (aa[i] + le) % p;
        }
        for(ll i=r+1; i<=n; i+=lowbit(i)) {
            aaa[i] = (aaa[i] - x + p) % p;
            aa[i] = (aa[i] - ri + p) % p;
        }
    }
    ll query(ll l, ll r) {
        return (query_base(r) - query_base(l-1) + p) % p;
    }
};

static BIT bit(N);

void dfs1(ll p, ll f) {
    fa[p] = f;
    sz[p] = 1;
    dep[p] = dep[f] + 1;
    ll tmp=-114;
    for(ll &i : g[p]) {
        if(i != f) {
            dfs1(i,p);
            sz[p] += sz[i];
            if(chmax(tmp, sz[i])) son_osz[p] = i;
        }
    }
}

void dfs2(ll p, ll f) {
    // dbg(p), dbg(f);
    tp[p] = f;
    ba[p] = ++all;
    if(a[p]) {
        bit.modify(ba[p], ba[p], a[p]);
    }
    if(!son_osz[p]) return;
    // dfs2(son_osz[p],p);
    dfs2(son_osz[p],f);
    for(ll &i : g[p]) {
        if(i != son_osz[p] && i != fa[p]) dfs2(i,i);
    }
}

void add_edge(ll u, ll v, ll w) {
    w %= p;
    for(;tp[u] != tp[v];u=fa[tp[u]]) {
        if(dep[tp[u]] < dep[tp[v]]) std::swap(u,v);
        bit.modify(ba[tp[u]], ba[u], w);
    }
    if(dep[u] > dep[v]) std::swap(u, v);
    bit.modify(ba[u], ba[v], w);
}
ll find_edge(ll u, ll v) {
    ll ans = 0;
    for(;tp[u] != tp[v];u=fa[tp[u]]) {
        if(dep[tp[u]] < dep[tp[v]]) std::swap(u,v);
        ans = (ans + bit.query(ba[tp[u]], ba[u])) % p;
    }
    if(dep[u] > dep[v]) std::swap(u, v);
    ans = (ans + bit.query(ba[u], ba[v])) % p;
    return ans;
}
void add_son(ll u, ll w) {
    w %= p;
    bit.modify(ba[u], ba[u] - 1 + sz[u], w);
}
ll find_son(ll u) {
    return bit.query(ba[u], ba[u] - 1 + sz[u]);
}

}

void solve() {
    // freopen("C:/Users/lin/Downloads/P3384_4.in", "r", stdin);
    // freopen("C:/Users/lin/Downloads/P3384_4.1.out", "w", stdout);
    std::cin >> n >> m >> r >> p;
    a.resize(n+1);
    for(ll i=1; i<=n; i++) std::cin >> a[i];
    g.resize(N);
    for(ll i=1; i<n; i++) {
        std::cin >> u >> v;
        g[u].pb(v), g[v].pb(u);
    }
    HLD::dfs1(r, 0);
    HLD::dfs2(r, r);
    for(ll i=1; i<=m; i++) {
        std::cin >> op >> x;
        if(op!=4) std::cin >> y;
        if(op == 1) {
            std::cin >> z;
            HLD::add_edge(x,y,z);
        } else if(op==2) {
            std::cout << HLD::find_edge(x,y) << '\n';
        } else if(op==3) {
            HLD::add_son(x,y);
        } else {
            std::cout << HLD::find_son(x) << '\n';
        }
    }
}
} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin), freopen(".out", "w", stdout);
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    hellolin::solve();
    return 0;
}