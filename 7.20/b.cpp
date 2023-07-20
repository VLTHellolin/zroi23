#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>

#ifndef HELLOLIN_RANDOM_NUMBER_HPP
#define HELLOLIN_RANDOM_NUMBER_HPP 1
#include <ctime>
#include <functional>
#include <random>

namespace hellolin {

class random_number {
private:
    std::mt19937 *gen;
    std::uniform_int_distribution<unsigned long long> dist;
    std::hash<unsigned long long> hs;

public:
    explicit random_number(unsigned long long sd = 4731636727ll) {
        static std::mt19937 r(time(0) ^ sd);
        gen = &r;
    }
    unsigned long long operator()() {
        return hs(1ll * (time(0) ^ dist(*gen)));
    }
    unsigned long long operator()(unsigned long long l, unsigned long long r) {
        return hs(1ll * (time(0) ^ dist(*gen))) % r + l;
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
constexpr static ull mod_1e97 = 1e9 + 7, mod_998 = 998244353, mod_1e18 = 1e18, inf = LONG_LONG_MAX;
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
    long long Ts;
    std::cin >> Ts;
    while (Ts--)
        hellolin::solve();
#else
    hellolin::solve();
#endif

    return 0;
}

namespace hellolin {

namespace tree {

constexpr static ll N = 114514;
random_number rnd;
ll roo;
class node final {
public:
    ll ls, rs;
    ll val, lz;
    ll pri, sz;
    explicit node(ll _val = 0, ll _pri = 0, ll _sz = 0)
        : val(_val)
        , pri(_pri)
        , sz(_sz) {}
    bool operator<(const node &x) const {
        return pri < x.pri;
    }
};
// vec<node> tr(1);
array<node, N> tr;
ll top;
ll create_node(ll v) {
    // tr.pb(v, rnd());
    // dbg(tr[tr.size()-1].pri);
    tr[++top] = node(v, rnd(), 1);
    return top;
}
void update(ll x) {
    tr[x].sz = tr[tr[x].ls].sz + tr[tr[x].rs].sz + 1;
}
void push_down(ll x) {
    if (tr[x].lz) {
        swap(tr[x].ls, tr[x].rs);
        tr[tr[x].ls].lz ^= 1;
        tr[tr[x].rs].lz ^= 1;
        tr[x].lz = 0;
    }
}
void query_base(ll rooo) {
    if (!rooo) return;
    push_down(rooo);
    query_base(tr[rooo].ls);
    cout << tr[rooo].val << ' ';
    query_base(tr[rooo].rs);
}
void query() {
    query_base(roo);
    cout << endl;
}
void split(ll p, ll x, ll &ans1, ll &ans2) {
    if (!p) {
        ans1 = ans2 = 0;
        return;
    }
    // dbg(p), dbg(x);
    push_down(p);

    if (tr[tr[p].ls].sz >= x) {
        ans2 = p;
        split(tr[p].ls, x, ans1, tr[p].ls);
    } else {
        ans1 = p;
        split(tr[p].rs, x - tr[tr[p].ls].sz - 1, tr[p].rs, ans2);
    }

    update(p);
}
ll merge(ll a, ll b) {
    if (!a) return b;
    if (!b) return a;
    // dbg(a), dbg(b);
    if (tr[a] < tr[b]) {
        push_down(a);
        tr[a].rs = merge(tr[a].rs, b);
        update(a);
        return a;
    } else {
        push_down(b);
        tr[b].ls = merge(a, tr[b].ls);
        update(b);
        return b;
    }
}
void rotate(ll l, ll r) {
    ll a1, a2, b;
    split(roo, r, a1, a2);
    split(a1, --l, a1, b);
    tr[b].lz ^= 1;
    roo = merge(merge(a1, b), a2);
    // dbg(a1), dbg(a2), dbg(b), dbg(roo);
}
void insert(ll x) {
    ll nx = create_node(x);
    dbg(x), dbg(nx), dbg(roo), cerr << endl;
    roo = merge(roo, nx);
    // dbg(nx), dbg(roo), cerr<<endl;
}

} // namespace tree

ll n, q, l, r;
void solve() {
    cin >> n >> q;
    for (ll i = 1; i <= n; i++) {
        tree::insert(i);
    }
    for (; q--;) {
        cin >> l >> r;
        tree::rotate(l, r);
    }
    tree::query();
}
} // namespace hellolin