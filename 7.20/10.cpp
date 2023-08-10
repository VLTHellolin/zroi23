#include <optional>
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

namespace LCT {

constexpr static ll N = 1e5 + 114;

class node final {
public:
    bool lz;
    ll son[2], fa, val;
    ll sum;
};
array<node, N> tr;

#define ls(x) tr[x].son[0]
#define rs(x) tr[x].son[1]

bool is_root(ll x) { // * 父节点的孩子不是该节点，该节点为根节点
    return ls(tr[x].fa) != x && rs(tr[x].fa) != x;
}
void create_node(ll u, ll x) {
    tr[u].val = x;
}
void create_edge(ll x, ll y, bool q) {
    tr[y].fa = x;
    tr[x].son[q] = y;
}
void update(ll x) {
    tr[x].sum = tr[x].val ^ tr[ls(x)].sum ^ tr[rs(x)].sum;
}
void push_down(ll x) {
    if (tr[x].lz) {
        swap(ls(x), rs(x));
        tr[ls(x)].lz ^= 1;
        tr[rs(x)].lz ^= 1;
        tr[x].lz = 0;
    }
}
void push__down(ll x) {
    if (!is_root(x)) push__down(tr[x].fa);
    push_down(x);
}
void rotate(ll x) {
    ll fx = tr[x].fa, fy = tr[fx].fa;
    bool fl = x == rs(fx);
    if (!is_root(fx)) // * 有爷爷
        create_edge(fy, x, fx == rs(fy));
    tr[x].fa = fy;
    create_edge(fx, tr[x].son[fl ^ 1], fl);
    create_edge(x, fx, fl ^ 1);
    update(fx); /* update(fy); */
    update(x);
}
void splay(ll x) {
    push__down(x);
    while (!is_root(x)) {
        ll fx = tr[x].fa, fy = tr[fx].fa;
        if (!is_root(fx)) {
            bool lt = ls(fx) == x;
            lt ^= ls(fy) == fx;
            ll r = lt ? x : fx;
            rotate(r);
        }
        rotate(x);
    }
}
void access(ll x) {
    for (ll i = 0; x; i = x, x = tr[x].fa) {
        splay(x);
        rs(x) = i;
        update(x);
    }
}
void make_root(ll x) {
    access(x);
    splay(x);
    tr[x].lz ^= 1;
}
ll find_root(ll x) {
    access(x);
    splay(x);
    for (; ls(x); x = ls(x))
        push_down(x);
    splay(x);
    return x;
}
void do_link(ll x, ll y) {
    make_root(x);
    if (find_root(y) != x) tr[x].fa = y;
}
void split(ll x, ll y) {
    make_root(x);
    access(y);
    splay(y);
}
void do_cut(ll x, ll y) {
    split(x,y);
    if(ls(y) == x && rs(x) == 0) {
        ls(y) = 0;
        tr[x].fa = 0;
    }
    // make_root(x);
    // if (find_root(y) != x) {
    //     if (!ls(y) && tr[y].fa == x) {
    //         tr[y].fa = 0;
    //         rs(x) = 0;
    //         update(x);
    //     }
    // }
}
void modify(ll x, ll v) {
    splay(x);
    tr[x].val = v;
    update(x);
}
ll query(ll x, ll y) {
    split(x, y);
    return tr[y].sum;
}

} // namespace LCT
ll n, m;
ll tmp, op, x, y;
void solve() {
    cin >> n >> m;
    for (ll i = 1; i <= n; i++) {
        cin >> tmp;
        LCT::create_node(i, tmp);
    }
    for (ll i = 1; i <= m; i++) {
        cin >> op >> x >> y;
        if (op == 0) {
            cout << LCT::query(x, y) << endl;
        } else if (op == 1) {
            LCT::do_link(x, y);
        } else if (op == 2) {
            LCT::do_cut(x, y);
        } else {
            LCT::modify(x, y);
        }
    }
}
} // namespace hellolin