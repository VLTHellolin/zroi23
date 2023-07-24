#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>
#include <bits/stdc++.h>

#ifndef HELLOLIN_FAST_IO_HPP
#define HELLOLIN_FAST_IO_HPP 1
#include <fstream>
#include <iostream>
#include <vector>

namespace hellolin {

constexpr static size_t FAST_IO_MAX_SIZE = (1 << 20) + 1;
constexpr static size_t FAST_OUT_STACK_SIZE = (1 << 8) + 1;

class fast_in {
private:
    FILE *fi;
    size_t sz;
    bool fail;
    char buf[FAST_IO_MAX_SIZE], *buf_head, *buf_tail;

    template <class T>
    void _read(T &x) {
        bool s = 0;
        char c = get();
        x = 0;
        while (!isdigit(c) && c) {
            s = c == '-';
            c = get();
        }
        while (isdigit(c)) {
            x = (x << 1) + (x << 3) + (c ^ '0');
            c = get();
        }
        if (s) x = ~x + 1;
    }
    void _read(long double &x) {
        bool s = false;
        char c = get();
        x = 0;
        while (!isdigit(c) && c) {
            s = c == '-';
            c = get();
        }
        while (isdigit(c)) {
            x = x * 10 + (c ^ '0');
            c = get();
        }
        if (c == '.') {
            c = get();
            long double t = 1;
            while (isdigit(c)) {
                t /= 10;
                x += t * (c ^ '0');
                c = get();
            }
        }
        if (s) x = -x;
    }
    void _read(double &x) {
        long double y;
        _read(y);
        x = y;
    }
    void _read(float &x) {
        long double y;
        _read(y);
        x = y;
    }
    void _read(char &x) {
        do { x = get(); } while (isspace(x));
    }
    void _read(char *x) {
        char c = get();
        while (isspace(c)) { c = get(); }
        while (!isspace(c) && c) {
            *x++ = c;
            c = get();
        }
        *x = '\0';
    }
    void _read(std::string &x) {
        char c = get();
        while (isspace(c)) { c = get(); }
        while (!isspace(c) && c) {
            x += c;
            c = get();
        }
    }
    template <class T, class U>
    void _read(std::pair<T, U> &x) {
        T a;
        U b;
        _read(a);
        _read(b);
        x = {a, b};
    }
    template <class T>
    void _read(std::vector<T> &x) {
        for (T &i : x) { _read(i); }
    }

public:
    explicit fast_in(FILE *_fi = stdin)
        : fi(_fi)
        , fail(0) {}
    explicit fast_in(const char *_fi)
        : fail(0) {
        FILE *__fi = fopen(_fi, "r");
        fi = __fi;
    }
    void reopen(FILE *_fi = stdin) {
        fclose(fi);
        fi = _fi;
    }
    operator bool() { return !fail; }
    void flush() {
        if (buf_head == buf_tail) {
            buf_head = buf;
            buf_tail = buf + fread(buf, 1, FAST_IO_MAX_SIZE, fi);
        }
    }
    char get() {
        flush();
        char c = -1;
        if (buf_head == buf_tail) fail = 1;
        else c = *buf_head++;
        return c;
    }
    char peek() {
        flush();
        char c = -1;
        if (buf_head == buf_tail) fail = 1;
        else c = *buf_head;
        return c;
    }
    template <class T>
    fast_in &operator>>(T &x) {
        _read(x);
        return *this;
    }
    template <class T>
    void operator()(T &x) {
        _read(x);
    }
    template <class T, class... Args>
    void operator()(T &x, Args &...args) {
        _read(x);
        operator()(args...);
    }
};

class fast_out_end_line {
public:
    char c;
    bool f;
    fast_out_end_line(char _c = '\n', bool _f = 1)
        : c(_c)
        , f(_f) {}
    ~fast_out_end_line() {}
} hendl('\n', 0), hendlf('\n', 1);

class fast_out {
private:
    FILE *fi;
    std::string buf;
    int cbuf[FAST_OUT_STACK_SIZE];
    int ctop = 0;
    int prec = 6;

    void _write(fast_out_end_line x) {
        put(x.c);
        if (x.f) flush();
    }
    template <class T>
    void _write(T x) {
        ctop = 0;
        if (x < 0) {
            put('-');
            x = ~x + 1;
        }
        while (x) {
            cbuf[++ctop] = x % 10;
            x /= 10;
        }
        if (!ctop) {
            put('0');
        }
        while (ctop) {
            put(cbuf[ctop--] ^ '0');
        }
    }
    bool _round(int x) {
        return x > 4;
    }
    void _write(long double x) {
        ctop = 0;
        if (x < 0) {
            put('-');
            x = -x;
        }
        int t = x;
        x -= t;
        ctop = 0;
        if (x) {
            do {
                cbuf[ctop++] = x * 10;
                x = x * 10 - cbuf[ctop - 1];
            } while (ctop < prec - 1);
            cbuf[ctop++] = (int) (x * 10 + _round((int) ((x * 10 - ((int) (x * 10))) * 10)));
            if (cbuf[ctop - 1] == 10) {
                int nt = ctop - 1;
                while (cbuf[nt] == 10 && nt) {
                    cbuf[nt] = 0;
                    cbuf[--nt] += 1;
                }
                if (!nt && cbuf[nt] == 10) {
                    cbuf[nt] = 0;
                    t += 1;
                }
            }
        }
        _write(t);
        put('.');
        for (int i = 0; i < ctop; i++) {
            put(cbuf[i] ^ '0');
        }
        for (int i = ctop; i < prec; i++) {
            put('0');
        }
    }
    void _write(double x) {
        _write((long double) x);
    }
    void _write(float x) {
        _write((long double) x);
    }
    void _write(const char x) {
        put(x);
    }
    void _write(char *x) {
        while (*x != '\0')
            put(*x++);
    }
    void _write(const char *x) {
        while (*x != '\0')
            put(*x++);
    }
    void _write(std::string x) {
        for (char i : x)
            put(i);
    }
    void _write(bool x) {
        if(x) _write(1);
        else _write(0);
    }
    template <class T>
    void _write(std::vector<T> x) {
        for (T i : x)
            _write(i);
    }

public:
    explicit fast_out(FILE *_fi = stdout)
        : fi(_fi) {}
    explicit fast_out(const char *_fi) {
        FILE *__fi = fopen(_fi, "w");
        fi = __fi;
    }
    ~fast_out() { flush(); }
    void reopen(FILE *_fi) {
        flush(1);
        fclose(fi);
        fi = _fi;
    }
    void precision(int x) {
        prec = x;
    }
    void flush(bool s = 0) {
        fwrite(buf.data(), 1, buf.size(), fi);
        buf.clear();
        if (s) fflush(fi);
    }
    void put(char x) {
        buf += x;
    }
    template <class T>
    fast_out &operator<<(T x) {
        _write(x);
        return *this;
    }
    template <class T>
    void operator()(T x) {
        _write(x);
    }
    template <class T, class... Args>
    void operator()(T x, Args &...args) {
        _write(x);
        operator()(args...);
    }
};

fast_in hin;
fast_out hout;

} // namespace hellolin

#endif

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

constexpr static ll N = 25 * 1e4 + 11, S = 1e6 + 11;

vec<int> g[N];
int n, q, s;
int u, v;
ll ans;
int now, a, b;
int que[S];
bool f;
// std::set<int>ss;
int bt[N];

inline void solve() {
    // * TESTCASE 1
    // ? PASSED
    // * TESTCASE 2
    // ? PASSED
    // freopen("C:/Users/lin/Downloads/problem_2596/ex_tree2.in", "r", stdin);
    // freopen("C:/Users/lin/Downloads/problem_2596/ex_tree2.testres", "w", stdout);
    // * TESTCASE 3
    // ? PASSED
    // freopen("C:/Users/lin/Downloads/problem_2596/ex_tree3.in", "r", stdin);
    // freopen("C:/Users/lin/Downloads/problem_2596/ex_tree3.testres", "w", stdout);
    hin >> n;
    for(int i=1; i<n; i++) {
        hin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    hin >> q;
    for(int i=1; i<=q; i++) {
        ans = 0;
        hin >> s;
        if(s==2 || s==-2) {
            hin >> a >> b;
            f = 0;
            if(b<a) std::swap(a,b);
            for(int k : g[a]) if(k==b) {
                f = 1; break;
            }
            hout << f << '\n';
            continue;
        }
        s = (s < 0) ? -s : s;
        // mp2.clear();
        memset(bt, 0, sizeof(bt));
        for(int j=1; j<=s; j++) {
            hin >> que[j];
        }
        std::sort(que+1, que+1+s);
        for(int j=1; j<=s; j++) {
            a = que[j];
            if(bt[a]) {
                ans += bt[a];
                bt[a] = 0;
            }
            for(int k : g[a])
                ++bt[k];
        }
        hout << ans << '\n';
    }
}
} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin), freopen(".out", "w", stdout);
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    hellolin::solve();
    return 0;
}