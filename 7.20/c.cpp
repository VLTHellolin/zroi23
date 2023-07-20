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

ll n, mi;

namespace tree {

constexpr static ll N = 114514;
random_number rnd;
ll roo;
class node final {
public:
    ll ls, rs;
    ll val;
    ll pri, sz;
    explicit node(ll _val = 0, ll _pri = 0, ll _sz = 0)
        : val(_val)
        , pri(_pri)
        , sz(_sz) {}
    bool operator<(const node &x) const {
        return pri < x.pri;
    }
};
array<node, N> tr;
ll top, lz;
ll leaved;
ll create_node(ll v) {
    tr[++top] = node(v, rnd(), 1);
    return top;
}
void update(ll x) {
    tr[x].sz = tr[tr[x].ls].sz + tr[tr[x].rs].sz + 1;
}
void split(ll p, ll v, ll &ans1, ll &ans2) {
    if (!p) {
        ans1 = ans2 = 0;
        return;
    }

    if (tr[p].val > v) {
        ans2 = p;
        split(tr[p].ls, v, ans1, tr[p].ls);
    } else {
        ans1 = p;
        split(tr[p].rs, v, tr[p].rs, ans2);
    }

    update(p);
}
ll merge(ll a, ll b) {
    if (!a) return b;
    if (!b) return a;
    if (tr[a] < tr[b]) {
        tr[a].rs = merge(tr[a].rs, b);
        update(a);
        return a;
    } else {
        tr[b].ls = merge(a, tr[b].ls);
        update(b);
        return b;
    }
}
ll order(ll x) {
    ll p = roo;
    for (;;) {
        if (x <= tr[tr[p].ls].sz)
            p = tr[p].ls;
        else if (x == tr[tr[p].ls].sz + 1)
            break;
        else
            x -= tr[tr[p].ls].sz + 1, p = tr[p].rs;
    }
    return p;
}
void insert(ll x) {
    if (x < mi) {
        // ++leaved;
        return;
    }
    ll a1, a2, b;
    x -= lz;
    split(roo, x, a1, a2);
    b = create_node(x);
    roo = merge(a1, merge(b, a2));
}
ll query(ll num) {
    if (tr[roo].sz < num) return -1;
    // return tr[++order(tr[roo].sz - num)].val + lz;
    return tr[order(tr[roo].sz - num + 1)].val + lz;
}
void inc(ll x) { lz += x; }
void dec(ll x) {
    lz -= x;
    ll a1, a2;
    split(roo, mi - 1 - lz, a1, a2);
    leaved += tr[a1].sz;
    roo = a2;
}

} // namespace tree

ll k;
char op;
void solve() {
    cin >> n >> mi;
    for (ll i = 1; i <= n; i++) {
        cin >> op >> k;
        if (op == 'I') {
            tree::insert(k);
        } else if (op == 'A') {
            tree::inc(k);
        } else if (op == 'S') {
            tree::dec(k);
        } else {
            cout << tree::query(k) << endl;
        }
        dbg(i);
    }
    cout << tree::leaved << endl;
}
} // namespace hellolin