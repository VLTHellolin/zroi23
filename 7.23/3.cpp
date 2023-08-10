#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>
#include <bits/stdc++.h>


namespace hellolin {
using ll = long long;
using ull = unsigned long long;
using lll = __int128;
template <class T> using min_pq = __gnu_pbds::priority_queue<T, std::greater<T>>;
template <class T> using max_pq = __gnu_pbds::priority_queue<T, std::less<T>>;
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
#define allnof(x, n) x.begin(), x.begin() + n + 1
#define alllnof(x, n) x.begin() + 1, x.begin() + n + 2
#define pb emplace_back
#define dbg(x) std::cerr << __LINE__ << ": " << #x << " = " << x << '\n'

void solve() {
    
}
} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin), freopen(".out", "w", stdout);
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    hellolin::solve();
    return 0;
}