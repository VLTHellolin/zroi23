// // * HELLOLIN'S CP CODE TEMPLATE v2.2.2
// #ifndef ONLINE_JUDGE
// #pragma GCC optimize(2, "inline", "unroll-loops", "no-stack-protector", "-ffast-math")
// #endif
// #define _EXT_CODECVT_SPECIALIZATIONS_H 0
// #define _EXT_ENC_FILEBUF_H 0
// #include <bits/extc++.h>

// int q[30000004];

// #ifndef HELLOLIN_STRING_MANACHER_HPP
// #define HELLOLIN_STRING_MANACHER_HPP 1
// #include <algorithm>
// #include <string>
// #include <vector>

// namespace hellolin {

// namespace string {

// // ! 约定下标从 1 开始
// class manacher {
// private:
//     int n;
//     std::string s, tp;

//     void init_tp() {
//         tp = " #";
//         for (int i = 1; i <= n; i++) {
//             tp += s[i-1];
//             tp += '#';
//         }
//         n = tp.length() - 1;
//     }
//     int calc_ans() {
//         q[1] = 1;
//         int r = 1;
//         for (int l = 2; l <= n; l++) {
//             if(l%10000 == 0) std::cerr << l << ' ';
//             if (l <= r) q[l] = std::min(r - l + 1, q[r - l + 1]);
//             while (tp[l - q[l]] == tp[l + q[l]])
//                 ++q[l];
//             if (q[l] + l > r) {
//                 r = l + q[l] - 1;
//             }
//         }
//         // return (*std::max_element(q.begin(), q.end())) - 1;
//         return (*std::max_element(q+1, q+1+n)) - 1;
//     }

// public:
//     manacher() {}
//     explicit manacher(std::string _s) {
//         set(_s);
//     }
//     void set(std::string _s) {
//         s = _s;
//         n = s.length();
//         // q.resize((n << 1) + 11, 0);
//     }
//     int query() {
//         init_tp();
//         return calc_ans();
//     }
// };

// } // namespace string

// } // namespace hellolin

// #endif

// namespace hellolin {
// namespace lib {
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
// #define rep(l, x, a, b) for (l x = a, x##END = b; x <= x##END; ++x)
// #define per(l, x, a, b) for (l x = a, x##END = b; x >= x##END; --x)
// #define y0 _HOMO_114__514_
// #define y1 _HOMO_1919_810_
// #define fi first
// #define se second
// #define allof(x) x.begin(), x.end()
// #define alof(x) x.begin() + 1, x.end()
// #define allnof(x, n) x.begin(), x.begin() + n + 1
// #define alnof(x, n) x.begin() + 1, x.begin() + n + 2
// #define lowbit(x) (x & -x)
// #define mp make_pair
// #define pb emplace_back
// }
// using namespace lib;

// // * CORE CODE BEGIN * //

// std::string s;
// string::manacher a;
// void solve() {
//     std::cin >> s;
//     a.set(s);
//     std::cout << a.query() << '\n';
// }
// // * CORE CODE END * //

// } // namespace hellolin

// int main() {
//     freopen("C:\\Users\\lin\\Downloads\\P3805_5.in", "r", stdin);
//     // freopen(".out", "w", stdout);
//     // freopen(".dbg", "w", stderr);
//     std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
//     // std::cout << std::fixed << std::setprecision(6);
//     hellolin::solve();
//     return 0;
// }

#include <bits/stdc++.h>

int n, q[30000004];
char a;
std::string s;
int main() {
    s = "##";
    n = 1;
    for (char c=getchar(); std::isalpha(c); c=getchar()) {
        s+=c,s+='#';
        n+=2;
    }
    for(int l=1, r=0, t=0; l<=n; l++) {
        if(l<=r) q[l] = std::min(r-l+1, q[(t<<1)-l]);
        while(s[l-q[l]] == s[l+q[l]]) ++q[l];

        if(q[l]+l>r) {
            t = l;
            r = q[l] + l - 1;
        }
    }
    printf("%d\n", (*std::max_element(q+1,q+1+n))-1);

}