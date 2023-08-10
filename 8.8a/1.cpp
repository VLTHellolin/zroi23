// * HELLOLIN'S CP CODE TEMPLATE v2.2.2
#ifndef ONLINE_JUDGE
#pragma GCC optimize(2, "inline", "unroll-loops", "no-stack-protector", "-ffast-math")
#endif
// #define _EXT_CODECVT_SPECIALIZATIONS_H 0
// #define _EXT_ENC_FILEBUF_H 0
// * Boost
// #include <bits/extc++.h>
// #include <bits/stdc++.h> // * Fix GCC 5.0
#include <iostream>
#include <iomanip>
#include <algorithm>

// namespace hellolin {
// namespace lib { // * Boost
// using ll = long long;
// using ull = unsigned long long;
// using lll = __int128;
// using ulll = __uint128_t;
// using ld = long double;
// template <class T> using Pair = std::pair<T, T>;
// constexpr static ll mod_1e97 = 1e9 + 7, mod_998 = 998244353, mod_1e18 = 1e18;
// constexpr static ll inf = INT_MAX, INF = LLONG_MAX;
// const static std::string yesno_str[2][3] = {{"no", "No", "NO"}, {"yes", "Yes", "YES"}};
// template <class T> inline void yesno(bool x, int y, T u = std::cout) { u << yesno_str[x][y] << '\n'; }
// template <class T> inline T fpow(T x, ull y, T mod) { T res = 1; for(; y; y >>= 1, x = x * x % mod) if(y & 1) res = res * x % mod; return res; }
// template <class T, class U> inline bool chmax(T &x, U y) { return y > x ? (x = y, 1) : 0; }
// template <class T, class U> inline bool chmin(T &x, U y) { return y < x ? (x = y, 1) : 0; }
#define rep(l, x, a, b) for (l x = a, x##END = b; x <= x##END; ++x)
#define per(l, x, a, b) for (l x = a, x##END = b; x >= x##END; --x)
#define y0 _HOMO_114__514_
#define y1 _HOMO_1919_810_
#define fi first
#define se second
// #define allof(x) x.begin(), x.end()
// #define alof(x) x.begin() + 1, x.end()
// #define allnof(x, n) x.begin(), x.begin() + n + 1
// #define alnof(x, n) x.begin() + 1, x.begin() + n + 2
// #define lowbit(x) (x & -x)
// #define mp make_pair
// #define pb emplace_back
// }
// using namespace lib;

// * CORE CODE BEGIN * //

// * CORE CODE END * //

// } // namespace hellolin


const short N = 7145;
int n, m;
long long t;
int k;
// int v[N], s[N];
std::pair<int, int> a[N];
std::pair<long long, int> qwq[N];
// clock_t st, ed;
// * Boost
int main() { // ! remember to check if there is anything that needs `long long` 
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    // st = clock();
    std::cin >> n;
    rep(int,i,1,n) {
        std::cin >> a[i].fi >> a[i].se;
    }
    std::cin >> m;
    rep(int,i,1,m) {
        std::cin >> t >> k;
        rep(int,j,1,n) {
            qwq[j].se = j;
            qwq[j].fi = (t * (long long)a[j].fi) + a[j].se;
        }
        // std::sort(qwq+1, qwq+1+n, [&](const std::pair<int,int> &q, const std::pair<int,int> &t){ return (q.fi == t.fi) ? (q.se < t.se) : (q.fi > t.fi); });
        std::nth_element(qwq+1, qwq+k, qwq+1+n, [&](const std::pair<long long,int> &q, const std::pair<long long,int> &t){ return (q.fi == t.fi) ? (q.se < t.se) : (q.fi > t.fi); });
        std::cout << qwq[k].se << '\n';
    }
    // ed = clock();
    // std::cerr << std::fixed << std::setprecision(6);
    // std::cerr << (long double)(ed - st) / CLOCKS_PER_SEC << '\n';
}
// int main() {
//     // freopen(".dbg", "w", stderr);
//     // std::cout << std::fixed << std::setprecision(6);
//     // hellolin::solve();
//     return 0;
// }