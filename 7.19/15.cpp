#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>

#ifndef HELLOLIN_DISTRIBUTION_HPP
#define HELLOLIN_DISTRIBUTION_HPP 1
#include <algorithm>
#include <vector>

namespace hellolin {

template <class T>
class dist {
private:
    bool ready;
    std::vector<T> d;
    void init() {
        std::sort(d.begin(), d.end());
        d.erase(std::unique(d.begin(), d.end()), d.end());
        ready = 1;
    }

public:
    explicit dist()
        : ready(0) {}
    void push(T x) {
        d.emplace_back(x);
        ready = 0;
    }
    T distribute(T x) {
        if (!ready) init();
        return std::lower_bound(d.begin(), d.end(), x) - d.begin() + 1;
    }
    T tribute(T x) {
        if (!ready) init();
        return d[x - 1];
    }
    unsigned long long size() {
        return d.size();
    }
    void clear() {
        d.clear();
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

constexpr static ll N = 4e4 + 114, M = 5e4 + 514, Sn = 514;

ll n, m, len, l, r, real_ans, count, ret;
array<ll, N> a, id, bt;
array<ll, Sn> qa, qb;
array<array<ll, Sn>, N> s;
array<array<ll, Sn>, Sn> f1, f2;
dist<ll> qwq;

void calc(ll& f, ll dx) {
    if(bt[dx] > bt[f]) f = dx;
    else if(bt[dx] == bt[f]) {
        if(f > dx) f =dx;
    }
}

ll query(ll l, ll r) {
    ll ans = 0;
    ll tmp, ttmp;
    if (id[l] + 2 >= id[r]) {
        for (ll i = l; i <= r; i++) {
            ++bt[a[i]];
            calc(ans,a[i]);
        }
        // fill(allof(bt), 0);
        for (ll i = l; i <= r; i++)
            bt[a[i]] = 0;
        return ans;
    }

    for (ll i = l; i <= qb[id[l]]; i++) {
        if (!bt[a[i]]) {
            bt[a[i]] += s[a[i]][id[r] - 1] - s[a[i]][id[l]];
        }
    }
    for (ll i = qa[id[r]]; i <= r; i++) {
        if (!bt[a[i]]) {
            bt[a[i]] += s[a[i]][id[r] - 1] - s[a[i]][id[l]];
        }
    }

    for (ll i = l; i <= qb[id[l]]; i++) {
        ++bt[a[i]];
        calc(ans,a[i]);
    }
    for (ll i = qa[id[r]]; i <= r; i++) {
        ++bt[a[i]];
        calc(ans,a[i]);
    }

    tmp = f1[id[l] + 1][id[r] - 1];
    ttmp = s[tmp][id[r] - 1] - s[tmp][id[l]];

    for (ll i = l; i <= qb[id[l]]; i++) {
        ttmp += a[i] == tmp;
    }
    for (ll i = qa[id[r]]; i <= r; i++) {
        ttmp += a[i] == tmp;
    }

    if (ttmp > bt[ans])
        ans = tmp;
    else if (ttmp == bt[ans]) {
        if (ans > tmp) ans = tmp;
    }

    for (ll i = l; i <= qb[id[l]]; i++)
        bt[a[i]] = 0;
    for (ll i = qa[id[r]]; i <= r; i++)
        bt[a[i]] = 0;
    return ans;
}

void solve() {
    cin >> n >> m;
    len = sqrt(n);
    fill(allof(qa), inf);
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
        qwq.push(a[i]);
        id[i] = (i - 1) / len + 1;
        qa[id[i]] = min(qa[id[i]], i);
        qb[id[i]] = max(qb[id[i]], i);
    }
    for (ll i = 1; i <= n; i++) {
        a[i] = qwq.distribute(a[i]);
    }

    for (ll i = 1; i <= n; i++) {
        for (ll j = id[i]; j <= id[n]; j++)
            ++s[a[i]][j];
    }

    for (ll i = 1; i <= id[n]; i++) {
        for (ll j = i; j <= id[n]; j++) {
            f1[i][j] = f1[i][j - 1];
            for (ll k = qa[j]; k <= qb[j]; k++) {
                ++bt[a[k]];

                calc(f1[i][j], a[k]);
            }
        }
        fill(allof(bt), 0);
    }

    for (ll i = 1; i <= m; i++) {
        cin >> l >> r;
        l = (l + real_ans - 1) % n + 1;
        r = (r + real_ans - 1) % n + 1;
        if (l > r) swap(l, r);
        real_ans = qwq.tribute(query(l, r));
        cout << real_ans << endl;
    }
}
} // namespace hellolin