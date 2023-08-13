// * HELLOLIN'S CP CODE TEMPLATE v2.4.0
#ifndef ONLINE_JUDGE
#pragma GCC optimize(2, "inline", "unroll-loops", "no-stack-protector", "-ffast-math")
#endif
#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>
#include <bits/stdc++.h> // * FIX GCC 5.0
#ifdef LOCAL
#include <windows.h>
#include <psapi.h>
#endif

namespace hellolin {
namespace lib {
using ll = long long;
using ull = unsigned long long;
using lll = __int128;
using ulll = __uint128_t;
const static std::string yesno_str[2][3] = {{"no", "No", "NO"}, {"yes", "Yes", "YES"}};
inline std::string yesno(bool x, int y) { return yesno_str[x][y] + '\n'; }
template <class T> inline T fpow(T x, ull y, T mod) { T res = 1; for(; y; y >>= 1, x = x * x % mod) if(y & 1) res = res * x % mod; return res; }
template <class T, class U> inline bool chmax(T &x, U y) { return y > x ? (x = y, 1) : 0; }
template <class T, class U> inline bool chmin(T &x, U y) { return y < x ? (x = y, 1) : 0; }
#define rep(l, x, a, b) for (l x = a, x##END = b; x <= x##END; ++x)
#define per(l, x, a, b) for (l x = a, x##END = b; x >= x##END; --x)
#define y0 _y_0_
#define y1 _y_1_
#define fi first
#define se second
#define allof(x) x.begin(), x.end()
#define alof(x) x.begin() + 1, x.end()
#define allnof(x, n) x.begin(), x.begin() + n + 1
#define alnof(x, n) x.begin() + 1, x.begin() + n + 2
#define lowbit(x) (x & -x)
#define mp make_pair
#define pb emplace_back
#define nl '\n'
}
using namespace lib;

// * CORE CODE BEGIN * //
constexpr static int N = 2e3+11, M = N;
constexpr static ll Mod = 1e9+7;
int n, m;
ll dp[M][50], res[M], now, ans, ls, addi;
int q[N], inc[N], caddi[N];
void max_inc() {
    // ll res = 0;
    rep(int, i, 1, n) {
        // res += n / i;
        if(n / i != 1) {
            inc[i] = n / i;
        } else {
            inc[i] = n / i;
            if(!ls) ls = i;
        }
    }
    if(!ls) ls = n + 1;
    // return res;
}
void work_inc() {
    rep(int, i, 1, ls - 1) {
        rep(int, j, 1, i-1) {
            if(i % j == 0) {
                ++q[i];
            }
        }
    }
}
void solve() {
    std::cin >> n >> m;
    max_inc();
    work_inc();
    rep(int, i, 1, ls-1) {
        bool f = 0;
        int cnt = 0;
        for(int j=i; j<=n; j+=i) {
            if(j >= ls) f = 1;
            if(f) ++cnt;
        }
        caddi[i] = cnt;
        // std::cerr << caddi[i] << '\n';
    }

    rep(int, i, 1, ls-1) {
        dp[1][i] = 1;
    }
    rep(int, i, 2, m) {
        rep(int, j, 1, ls-1) {
            dp[i][j] = dp[i-1][j] + q[j];
            // fprintf(stderr, "%d %d: %d\n", i, j, dp[i][j]);
        }
    }
    addi = n - ls + 1;
    ans = n;
    // addi = n - ls + 1;
    // rep(int, j, 1, ls-1) {
    //     std::cerr << caddi[j] << '\n';
    // }
    rep(int, i, 2, m) {
        now = 0;
        rep(int, j, 1, ls-1) {
            now = (now + dp[i-1][j] * inc[j]) % Mod;
            // fprintf(stderr, "%d ",dp[i-1][j] * inc[j]);
        }
        // fprintf(stderr, "\n");
        // std::cerr << ans << '\n';
        ans = (ans + (now + addi)) % Mod;
        // std::cerr << now << ' ' << addi << '\n';
        rep(int, j, 1, ls-1) {
            addi = (addi + dp[i][j] * caddi[j]) % Mod;
        }
    }
    std::cout << ans << '\n';
}
// * CORE CODE END * //

} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    // freopen(".dbg", "w", stderr);
#ifdef LOCAL
    clock_t st = clock(), ed;
#endif
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    // std::cout << std::fixed << std::setprecision(6);
    std::cerr << std::fixed << std::setprecision(6);
    hellolin::solve();
#ifdef LOCAL
    ed = clock();
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    std::cerr << "---------- DEBUG INFO ----------\n";
    std::cerr << "Time: " << (long double)(ed - st) / CLOCKS_PER_SEC << "s.\n";
    std::cerr << "Memory: " << pmc.WorkingSetSize / 1000000 << "MB.\n";
#endif
    return 0;
}